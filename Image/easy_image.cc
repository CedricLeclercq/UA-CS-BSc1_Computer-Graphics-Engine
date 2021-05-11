/*
 * easy_image.cc
 * Copyright (C) 2011  Daniel van den Akker
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "easy_image.h"
#include <algorithm>
#include <assert.h>
#include <math.h>
#include <iostream>
#include <list>
#include "../ExtraFeatures/InfPointLight.h"




using namespace std;
using Lines2D = std::list<Line2D>;
//typedef std::vector<Light*> Lights3D; // Vector with light pointers

inline int roundToInt(double d) { return static_cast<int>(round(d)); }


#ifndef le32toh
#define le32toh(x) (x)
#endif

namespace
{
	//structs borrowed from wikipedia's article on the BMP file format
	struct bmpfile_magic
	{
			uint8_t magic[2];
	};

	struct bmpfile_header
	{
			uint32_t file_size;
			uint16_t reserved_1;
			uint16_t reserved_2;
			uint32_t bmp_offset;
	};
	struct bmp_header
	{
			uint32_t header_size;
			int32_t width;
			int32_t height;
			uint16_t nplanes;
			uint16_t bits_per_pixel;
			uint32_t compress_type;
			uint32_t pixel_size;
			int32_t hres;
			int32_t vres;
			uint32_t ncolors;
			uint32_t nimpcolors;
	};
	//copy-pasted from lparser.cc to allow these classes to be used independently from each other
	class enable_exceptions
	{
		private:
			std::ios& ios;
			std::ios::iostate state;
		public:
			enable_exceptions(std::ios& an_ios, std::ios::iostate exceptions) :
				ios(an_ios)
			{
				state = ios.exceptions();
				ios.exceptions(exceptions);
			}
			~enable_exceptions()
			{
				ios.exceptions(state);
			}
	};
	//helper function to convert a number (char, int, ...) to little endian
	//regardless of the endiannes of the system
	//more efficient machine-dependent functions exist, but this one is more portable
	template<typename T> T to_little_endian(T value)
	{
		//yes, unions must be used with caution, but this is a case in which a union is needed
		union
		{
				T t;
				uint8_t bytes[sizeof(T)];
		} temp_storage;

		for (uint8_t i = 0; i < sizeof(T); i++)
		{
			temp_storage.bytes[i] = value & 0xFF;
			value >>= 8;
		}
		return temp_storage.t;
	}

	template<typename T> T from_little_endian(T value)
	{
		//yes, unions must be used with caution, but this is a case in which a union is needed
		union
		{
				T t;
				uint8_t bytes[sizeof(T)];
		} temp_storage;
		temp_storage.t = value;
		T retVal = 0;

		for (uint8_t i = 0; i < sizeof(T); i++)
		{
			retVal = (retVal << 8) | temp_storage.bytes[sizeof(T) - i - 1];
		}
		return retVal;
	}

}
img::Color::Color() :
	blue(0), green(0), red(0)
{
}
img::Color::Color(uint8_t r, uint8_t g, uint8_t b) :
	blue(b), green(g), red(r)
{
}
img::Color::~Color()
{
}

img::UnsupportedFileTypeException::UnsupportedFileTypeException(std::string const& msg) :
	message(msg)
{
}
img::UnsupportedFileTypeException::UnsupportedFileTypeException(const UnsupportedFileTypeException &original)
: std::exception(original)
, message(original.message)
{
}
img::UnsupportedFileTypeException::~UnsupportedFileTypeException() throw ()
{
}
img::UnsupportedFileTypeException& img::UnsupportedFileTypeException::operator=(UnsupportedFileTypeException const& original)
{
	this->message = original.message;
	return *this;
}
const char* img::UnsupportedFileTypeException::what() const throw ()
{
	return message.c_str();
}

img::EasyImage::EasyImage() :
	width(0), height(0), bitmap()
{
}

img::EasyImage::EasyImage(unsigned int _width, unsigned int _height, Color color) :
	width(_width), height(_height), bitmap(width * height, color)
{
}

img::EasyImage::EasyImage(EasyImage const& img) :
	width(img.width), height(img.height), bitmap(img.bitmap)
{
}

img::EasyImage::~EasyImage()
{
	bitmap.clear();
}

img::EasyImage& img::EasyImage::operator=(img::EasyImage const& img)
{
	width = img.width;
	height = img.height;
	bitmap.assign(img.bitmap.begin(),img.bitmap.end());
	return (*this);
}

unsigned int img::EasyImage::get_width() const
{
	return width;
}

unsigned int img::EasyImage::get_height() const
{
	return height;
}

void img::EasyImage::clear(Color color)
{
	for (std::vector<Color>::iterator i = bitmap.begin(); i != bitmap.end(); i++)
	{
		*i = color;
	}
}

img::Color& img::EasyImage::operator()(unsigned int x, unsigned int y)
{
	assert(x < this->width);
	assert(y < this->height);
	return bitmap.at(x * height + y);
}

img::Color const& img::EasyImage::operator()(unsigned int x, unsigned int y) const
{
	assert(x < this->width);
	assert(y < this->height);
	return bitmap.at(x * height + y);
}

void img::EasyImage::draw_line(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, Color color)
{
	assert(x0 < this->width && y0 < this->height);
	assert(x1 < this->width && y1 < this->height);
	if (x0 == x1)
	{
		//special case for x0 == x1
		for (unsigned int i = std::min(y0, y1); i <= std::max(y0, y1); i++)
		{
			(*this)(x0, i) = color;
		}
	}
	else if (y0 == y1)
	{
		//special case for y0 == y1
		for (unsigned int i = std::min(x0, x1); i <= std::max(x0, x1); i++)
		{
			(*this)(i, y0) = color;
		}
	}
	else
	{
		if (x0 > x1)
		{
			//flip points if x1>x0: we want x0 to have the lowest value
			std::swap(x0, x1);
			std::swap(y0, y1);
		}
		double m = ((double) y1 - (double) y0) / ((double) x1 - (double) x0);
		if (-1.0 <= m && m <= 1.0)
		{
			for (unsigned int i = 0; i <= (x1 - x0); i++)
			{
				(*this)(x0 + i, (unsigned int) round(y0 + m * i)) = color;
			}
		}
		else if (m > 1.0)
		{
			for (unsigned int i = 0; i <= (y1 - y0); i++)
			{
				(*this)((unsigned int) round(x0 + (i / m)), y0 + i) = color;
			}
		}
		else if (m < -1.0)
		{
			for (unsigned int i = 0; i <= (y0 - y1); i++)
			{
				(*this)((unsigned int) round(x0 - (i / m)), y0 - i) = color;
			}
		}
	}
}

void img::EasyImage::draw_zbuf_line(ZBuffer & zBuffer, double x0, double y0, double z0, double x1, double y1, double z1, const Color& color)
{
    assert(x0 < this->width && y0 < this->height);
    assert(x1 < this->width && y1 < this->height);


    if (x0 == x1)
    {
        //special case for x0 == x1
        for (unsigned int i = std::min(y0, y1); i <= std::max(y0, y1); i++)
        {
            double oneOverZ = 1;
            if ((max(y0,y1) - i != 0 and (max(y0,y1) - min(y0,y1)) != 0)) {
                oneOverZ = ((max(y0,y1) - i) / (max(y0,y1) - min(y0,y1))) / z0 + (1 - ((max(y0,y1) - i) / (max(y0,y1) - min(y0,y1)))) / z1;
            } else if ((max(y0,y1) - i != 0 and (max(y0,y1) - min(y0,y1)) == 0)) {
                oneOverZ = ((max(y0,y1) - i) + (1 - max(y0,y1) - i));
            }
            if (oneOverZ < zBuffer[roundToInt(x0)][i]) {
                (*this)((unsigned int) x0, i) = color;
                zBuffer[(unsigned int) x0][i] = oneOverZ;
            }
        }
    }
    else if (y0 == y1)
    {
        //special case for y0 == y1
        for (unsigned int i = std::min(x0, x1); i <= std::max(x0, x1); i++)
        {
            //double oneOverZ = (i - min(x0,x1) / ((max(x0,x1) - min(x0,x1)))/z0 + (1-( i - min(x0,x1)/(max(x0,x1) - min(x0,x1)))/z1));
            double oneOverZ = 1;
            if (max(x0,x1) - i != 0 and (max(x0,x1) - min(x0,x1)) != 0) {
                oneOverZ = (((max(x0, x1) - i) / (max(x0, x1) - min(x0, x1))) / z0) + ((1 - ((max(x0, x1) - i) / (max(x0, x1) - min(x0, x1)))) / z1);
            } else if (max(x0,x1) - i != 0 and (max(x0,x1) - min(x0,x1)) == 0) {
                oneOverZ = ((max(x0,x1) - i) + (1 - max(x0,x1) - i));
            }
            //double oneOverZ = 0;
            if (oneOverZ < zBuffer[i][roundToInt(y0)]) {
                (*this)(i, (unsigned int) y0) = color;
                zBuffer[i][(unsigned int)y0] = oneOverZ;
            }
        }
    }
    else
    {
        if (x0 > x1)
        {
            //flip points if x1>x0: we want x0 to have the lowest value
            std::swap(x0, x1);
            std::swap(y0, y1);
            std::swap(z0,z1);
        }
        double m = ((double) y1 - (double) y0) / ((double) x1 - (double) x0);
        if (-1.0 <= m && m <= 1.0)
        {
            for (unsigned int i = 0; i <= (x1 - x0); i++)
            {
                double oneOverZ = 1;
                if (x1 - x0 - i != 0 and (x1 - x0) != 0) {
                    oneOverZ = (((x1 - x0 - i) / (x1 - x0)) / z0) + (1 - ((x1 - x0 - i) / (x1 - x0))) / z1;
                }cout << oneOverZ << endl;
                if (oneOverZ < zBuffer[x0+i][(unsigned int) round(y0 + m * i)]) {
                    (*this)((unsigned int) x0 + i, (unsigned int) round(y0 + m * i)) = color;
                    zBuffer[x0 + i][(unsigned int) round(y0 + m * i)] = oneOverZ;
                }
            }
        }
        else if (m > 1.0)
        {
            for (unsigned int i = 0; i <= (y1 - y0); i++)
            {
                //double oneOverZ = ((y1 - y0)/z0 + (1-(y1 - y0)/z1));
                double oneOverZ = 1;
                if (y1 - y0 - i != 0 and (y1 - y0) != 0) {
                    oneOverZ = (((y1 - y0 - i) / (y1 - y0)) / z0) + (1 - ((y1 - y0 - i) / (y1 - y0))) / z1;
                }cout << oneOverZ << endl;
                if (oneOverZ < zBuffer[(unsigned int) round(x0 + (i / m))][(unsigned int) y0 + i]) {
                    (*this)((unsigned int) round(x0 + (i / m)), (unsigned int) y0 + i) = color;
                    zBuffer[(unsigned int) round(x0 + (i / m))][(unsigned int) y0 + i] = oneOverZ;
                }
            }
        }
        else if (m < -1.0)
        {
            for (unsigned int i = 0; i <= (y0 - y1); i++)
            {
                //double oneOverZ = ((y0 - y1)/z0 + (1-(y0 - y1)/z1));
                double oneOverZ = 1;
                if (y0 - y1 - i != 0 and (y0 - y1) != 0) {
                    oneOverZ = (((y0 - y1 - i) / (y0 - y1)) / z0) + (1 - ((y0 - y1 - i) / (y0 - y1))) / z1;
                }cout << oneOverZ << endl;
                if (oneOverZ < zBuffer[(unsigned int) round(x0 - (i / m))][y0 - i]) {
                    (*this)((unsigned int) round(x0 - (i / m)), (unsigned int)y0 - i) = color;
                    zBuffer[(unsigned int) round(x0 - (i / m))][(unsigned int)y0 - i] = oneOverZ;
                }
            }
        }
    }
}
void img::EasyImage::draw_zbuf_triag(ZBuffer & zBuffer,Vector3D const * A,Vector3D const * B,Vector3D const * C,
                                     double d,double dx,double dy,const vector<double>& ambientLightReflection,
                                     const vector<double>& diffuseReflection,const vector<double>& specularReflection, const double reflectionCo,
                                     Lights3D& lights, bool shadowEnabled, double shadowMask) {

    // Some assertions apply
    assert(A->x < this->width && A->y < this->height);
    assert(B->x < this->width && B->y < this->height);
    assert(C->x < this->width && C->y < this->height);

    // Step 1: Projection of the triangle
    Point2D projectedA(((d * A->x) / -A->z) + dx, ((d * A->y) / -A->z) + dy);
    Point2D projectedB(((d * B->x) / -B->z) + dx, ((d * B->y) / -B->z) + dy);
    Point2D projectedC(((d * C->x) / -C->z) + dx, ((d * C->y) / -C->z) + dy);

    // Step 2: calculating the 1/z values
    double Xg = (projectedA.x + projectedB.x + projectedC.x) / 3;
    double Yg = (projectedA.y + projectedB.y + projectedC.y) / 3;
    double oneOverZg = (1 / (3*A->z)) + (1 / (3*B->z)) + (1 / (3*C->z));


        // Calculating u and v
    Vector3D u, v;
    u.x = B->x - A->x; u.y = B->y - A->y; u.z = B->z - A->z;
    v.x = C->x - A->x; v.y = C->y - A->y; v.z = C->z - A->z;

    // Calculating w
    auto x = u.y * v.z - u.z * v.y;
    auto y = u.z * v.x - u.x * v.z;
    auto z = u.x * v.y - u.y * v.x;
    Vector3D w = Vector3D::vector(x,y,z);

    vector<double> finalColor = {0,0,0};

    if (lights.empty()) {
        finalColor[0] = ambientLightReflection[0];
        finalColor[1] = ambientLightReflection[1];
        finalColor[2] = ambientLightReflection[2];
    }

    // Applying light
    for (auto &light: lights) {
        // Ambient light should always be applied, regardless of the shadow state
        // Applying ambient light
        finalColor[0] += light->ambientLight.red * ambientLightReflection[0]; // ... to red
        finalColor[1] += light->ambientLight.green * ambientLightReflection[1]; // ... to green
        finalColor[2] += light->ambientLight.blue * ambientLightReflection[2]; // ... to blue

    }
    for (auto &light: lights) {
        if (light->lightClass == Infinity) {
            auto * inftyLight = static_cast<InfLight*>(light); // Casting to access derivative class member variables

            // First applying the diffuse light
            Vector3D lOld = inftyLight->ldVector; // Creating l vector
            lOld.x = -lOld.x; lOld.y = -lOld.y; lOld.z = -lOld.z; // Creating l with the right values
            Vector3D n = Vector3D::normalise(w); // Normalising
            Vector3D l = Vector3D::normalise(lOld);
            //double divValue = sqrt(pow(w.x,2) + pow(w.y,2) + pow(w.z,2)); // Manually normalisation
            //n.x = n.x / divValue; n.y = n.y / divValue; n.z = n.z / divValue; // Manual normalisation
            double cosAlpha = n.x * l.x + n.y * l.y + n.z * l.z; // Calculating cosAlpha
            if (cosAlpha > 0) {
                // Else no diffuse light :(, but if cosAlpha > 0 we :), applying diffuse light
                finalColor[0] +=  inftyLight->diffuseLight.red * diffuseReflection[0] * cosAlpha; // ... to red
                finalColor[1] += inftyLight->diffuseLight.green * diffuseReflection[1] * cosAlpha; // ... to green
                finalColor[2] +=  inftyLight->diffuseLight.blue * diffuseReflection[2] * cosAlpha; // ... to blue
            }

                // Now applying specular light
            // Defining vector r
            Vector3D r = Vector3D::vector(2 * cosAlpha * n.x - l.x,
                                          2 * cosAlpha * n.y - l.y,
                                          2 * cosAlpha * n.z - l.z);

            //double cosBeta = 3; // TODO victor's idea for infty specular points
            //double cosBetaMS = pow(cosBeta,reflectionCo); // Doing the cosine of beta to the power of M_s
            //if (cosBetaMS > 0) {
                //finalColor[0] += inftyLight->specularLight.red * specularReflection[0] * cosBetaMS;
                //finalColor[1] += inftyLight->specularLight.green * specularReflection[1] * cosBetaMS;
                //finalColor[2] += inftyLight->specularLight.blue * specularReflection[2] * cosBetaMS;
            //} // TODO turn this on again


        }  // If the light is not a point or infinity, leave it out, this light came into this engine ILLEGALLY
    }
    // Calculating k
    double k = w.x * A->x + w.y * A->y + w.z * A->z;
        // Combining previous calculations to DzDx and DzDy
    double DzDx = w.x / (-d * k);
    double DzDy = w.y / (-d * k);
    // Step 3: Calculating yMin and yMax for the iteration later
    int yMin = roundToInt(min(projectedA.y,min(projectedB.y,projectedC.y)) -0.5);
    int yMax = roundToInt(max(projectedA.y,max(projectedB.y,projectedC.y)) +0.5);
    // Step 4: looping
    for (int y = yMin; y < yMax + 1; y++) {
            //Initialise all the Xl and Xr
        double Xl_AB = numeric_limits<double>::infinity(), Xl_AC = numeric_limits<double>::infinity(), Xl_BC = numeric_limits<double>::infinity();
        double Xr_AB = -numeric_limits<double>::infinity(), Xr_AC = -numeric_limits<double>::infinity(), Xr_BC = -numeric_limits<double>::infinity();
        if ((y - projectedA.y)*(y - projectedB.y) <= 0 and projectedA.y != projectedB.y) {
            // AB
            double Xi = (projectedB.x + (projectedA.x - projectedB.x) * ((double)y - projectedB.y)/(projectedA.y - projectedB.y));
            Xl_AB = Xi;
            Xr_AB = Xi;
        }
        if ((y - projectedB.y)*(y - projectedC.y) <= 0 and projectedB.y != projectedC.y) {
            // BC
            double Xi = (projectedC.x + (projectedB.x - projectedC.x) * ((double)y - projectedC.y)/(projectedB.y - projectedC.y));
            Xl_BC = Xi;
            Xr_BC = Xi;
        }
        if ((y - projectedA.y)*(y - projectedC.y) <= 0 and projectedA.y != projectedC.y) {
            // AC
            double Xi = (projectedC.x + (projectedA.x - projectedC.x) * ((double)y - projectedC.y)/(projectedA.y - projectedC.y));
            Xl_AC = Xi;
            Xr_AC = Xi;
        }
        int Xl = roundToInt(min(Xl_AB,min(Xl_AC,Xl_BC)) + 0.5);
        int Xr = roundToInt(max(Xr_AB,max(Xr_AC,Xr_BC)) - 0.5);
        if (Xl >= 0 and Xr >= 0) {
            for (int x = Xl; x < Xr + 1; x++) {
                double oneOverZ = 1.0001 * oneOverZg + ((double) x - Xg) * DzDx + ((double) y - Yg) * DzDy;
                if (zBuffer[x][y] > oneOverZ) {
                    zBuffer[x][y] = oneOverZ;
                    vector<double> saveColor = finalColor;
                    // Adjusting color for point lights
                        for (auto &light: lights) {
                            if (light->lightClass == Point) {
                                auto *pointLight = static_cast<PointLight*>(light);
                                auto lX = ((x - dx) * -(1 / oneOverZ)) / d;
                                auto lY = ((y - dy) * -(1 / oneOverZ)) / d;
                                auto lZ = 1 / oneOverZ;
                                Vector3D ld = Vector3D::vector(pointLight->location.x,pointLight->location.y,pointLight->location.z);
                                ld.x -= lX;
                                ld.y -= lY;
                                ld.z -= lZ;
                                ld = Vector3D::normalise(ld);
                                Vector3D n = Vector3D::normalise(w);
                                double cosAlpha = ld.x * n.x + ld.y * n.y + ld.z * n.z;
                                if (cosAlpha > 0 and cosAlpha > cos(pointLight->spotAngle)) {
                                    //double final = (1 - (1 - cosAlpha) / (1 - cos(pointLight->spotAngle)));
                                    double final = (cosAlpha - cos(pointLight->spotAngle))/(1-cos(pointLight->spotAngle));
                                    finalColor[0] += pointLight->diffuseLight.red * diffuseReflection[0] * final;
                                    finalColor[1] += pointLight->diffuseLight.green * diffuseReflection[1] * final;
                                    finalColor[2] += pointLight->diffuseLight.blue * diffuseReflection[2] * final;
                                }
                                Vector3D rOld = Vector3D::vector(2 * cosAlpha * n.x - ld.x,
                                                                 2 * cosAlpha * n.y - ld.y,
                                                                 2 * cosAlpha * n.z - ld.z);
                                Vector3D r = Vector3D::normalise(rOld);
                                Vector3D m = Vector3D::vector(-lX,-lY,-lZ);
                                m = Vector3D::normalise(m);
                                double cosBeta = r.x * m.x + r.y * m.y + r.z * m.z;
                                // Doing the cosine of beta to the power of M_s
                                double cosBetaMS = pow(cosBeta,reflectionCo);
                                if (cosBeta > 0) {
                                    finalColor[0] += pointLight->specularLight.red * specularReflection[0] * cosBetaMS;
                                    finalColor[1] += pointLight->specularLight.green * specularReflection[1] * cosBetaMS;
                                    finalColor[2] += pointLight->specularLight.blue * specularReflection[2] * cosBetaMS;
                                }

                            }
                            // This part in comments below was my old code, this was all a mess so I rewrote the code above
                            /*
                            if (light->lightClass == Point) {
                                auto *pointLight = static_cast<PointLight *>(light);
                                Vector3D location = pointLight->location;
                                Vector3D n = Vector3D::normalise(w);
                                location.x = -location.x;
                                location.y = -location.y;
                                location.z = -location.z;
                                auto lX = ((x - dx) * -(1 / oneOverZ)) / d;
                                auto lY = ((y - dy) * -(1 / oneOverZ)) / d;
                                auto lZ = 1 / oneOverZ;
                                location = Vector3D::normalise(location);
                                location = Vector3D::cross(location, n);
                                //location.x = location.x * n.x;
                                //location.y = location.y * n.y;
                                //location.z = location.z * n.z;
                                Vector3D lOld = Vector3D::vector(lX, lY, lZ);
                                Vector3D l = Vector3D::normalise(lOld);
                                //Vector3D l = lOld;
                                double cosAlpha = location.x * l.x + location.y * l.y + location.z * l.z;
                                if (cosAlpha > 0) {
                                    finalColor[0] += pointLight->diffuseLight.red * diffuseReflection[0] * cosAlpha;
                                    finalColor[1] += pointLight->diffuseLight.green * diffuseReflection[1] * cosAlpha;
                                    finalColor[2] += pointLight->diffuseLight.blue * diffuseReflection[2] * cosAlpha;
                                }

                                //else if (cosAlpha > 0 and pointLight->spotAngle != 0) {
                                  //  finalColor[0] += pointLight->diffuseLight.red * diffuseReflection[0]
                                    //                 * (1 -
                                      //                  (1 - cosAlpha) / (1 - cos(pointLight->spotAngle * M_PI / 180)));
                                    //finalColor[1] += pointLight->diffuseLight.green * diffuseReflection[1]
                                      //               * (1 -
                                      //                  (1 - cosAlpha) / (1 - cos(pointLight->spotAngle * M_PI / 180)));
                                    //finalColor[2] += pointLight->diffuseLight.blue * diffuseReflection[2]
                                      //               * (1 -
                                        //                (1 - cosAlpha) / (1 - cos(pointLight->spotAngle * M_PI / 180)));
                                //}

                                // Defining vector r
                                Vector3D rOld = Vector3D::vector(2 * cosAlpha * n.x - l.x,
                                                                 2 * cosAlpha * n.y - l.y,
                                                                 2 * cosAlpha * n.z - l.z);

                                Vector3D r = Vector3D::normalise(rOld);
                                // Defining vector m
                                //Vector3D m = Vector3D::normalise(Vector3D::vector(lX, lY, lZ)); // TODO calculate, how?
                                Vector3D m = Vector3D::vector(0,0,0);
                                // Now applying specular light
                                double cosBeta = r.x * m.x + r.y * m.y + r.z * m.z;
                                double cosBetaMS = pow(cosBeta,
                                                       reflectionCo); // Doing the cosine of beta to the power of M_s
                                if (cosBetaMS > 0) {
                                    // TODO turn on again
                                    //finalColor[0] += pointLight->specularLight.red * specularReflection[0] * cosBetaMS;
                                    //finalColor[1] +=
                                            //pointLight->specularLight.green * specularReflection[1] * cosBetaMS;
                                    //finalColor[2] += pointLight->specularLight.blue * specularReflection[2] * cosBetaMS;
                                }
                            }
                            */
                        }
                    // Now creating the color we need - and setting it on this picture
                    (*this)(x, y) = Color(roundToInt(finalColor[0] * 255),
                                          roundToInt(finalColor[1] * 255),
                                          roundToInt(finalColor[2] * 255));
                    finalColor = saveColor; // Resetting the final color, else each pixel will start of where the previous one ended
                }
            }
        }
    }
}

std::ostream& img::operator<<(std::ostream& out, EasyImage const& image)
{

	//temporaryily enable exceptions on output stream
	enable_exceptions(out, std::ios::badbit | std::ios::failbit);
	//declare some struct-vars we're going to need:
	bmpfile_magic magic;
	bmpfile_header file_header;
	bmp_header header;
	uint8_t padding[] =
	{ 0, 0, 0, 0 };
	//calculate the total size of the pixel data
	unsigned int line_width = image.get_width() * 3; //3 bytes per pixel
	unsigned int line_padding = 0;
	if (line_width % 4 != 0)
	{
		line_padding = 4 - (line_width % 4);
	}
	//lines must be aligned to a multiple of 4 bytes
	line_width += line_padding;
	unsigned int pixel_size = image.get_height() * line_width;

	//start filling the headers
	magic.magic[0] = 'B';
	magic.magic[1] = 'M';

	file_header.file_size = to_little_endian(pixel_size + sizeof(file_header) + sizeof(header) + sizeof(magic));
	file_header.bmp_offset = to_little_endian(sizeof(file_header) + sizeof(header) + sizeof(magic));
	file_header.reserved_1 = 0;
	file_header.reserved_2 = 0;
	header.header_size = to_little_endian(sizeof(header));
	header.width = to_little_endian(image.get_width());
	header.height = to_little_endian(image.get_height());
	header.nplanes = to_little_endian(1);
	header.bits_per_pixel = to_little_endian(24);//3bytes or 24 bits per pixel
	header.compress_type = 0; //no compression
	header.pixel_size = pixel_size;
	header.hres = to_little_endian(11811); //11811 pixels/meter or 300dpi
	header.vres = to_little_endian(11811); //11811 pixels/meter or 300dpi
	header.ncolors = 0; //no color palette
	header.nimpcolors = 0;//no important colors

	//okay that should be all the header stuff: let's write it to the stream
	out.write((char*) &magic, sizeof(magic));
	out.write((char*) &file_header, sizeof(file_header));
	out.write((char*) &header, sizeof(header));

	//okay let's write the pixels themselves:
	//they are arranged left->right, bottom->top, b,g,r
	for (unsigned int i = 0; i < image.get_height(); i++)
	{
		//loop over all lines
		for (unsigned int j = 0; j < image.get_width(); j++)
		{
			//loop over all pixels in a line
			//we cast &color to char*. since the color fields are ordered blue,green,red they should be written automatically
			//in the right order
			out.write((char*) &image(j, i), 3 * sizeof(uint8_t));
		}
		if (line_padding > 0)
			out.write((char*) padding, line_padding);
	}
	//okay we should be done
	return out;
}
std::istream& img::operator>>(std::istream& in, EasyImage & image)
{
	enable_exceptions(in, std::ios::badbit | std::ios::failbit);
	//declare some struct-vars we're going to need
	bmpfile_magic magic;
	bmpfile_header file_header;
	bmp_header header;
	//a temp buffer for reading the padding at the end of each line
	uint8_t padding[] =
	{ 0, 0, 0, 0 };

	//read the headers && do some sanity checks
	in.read((char*) &magic, sizeof(magic));
	if (magic.magic[0] != 'B' || magic.magic[1] != 'M')
		throw UnsupportedFileTypeException("Could not parse BMP File: invalid magic header");
	in.read((char*) &file_header, sizeof(file_header));
	in.read((char*) &header, sizeof(header));
	if (le32toh(header.pixel_size) + le32toh(file_header.bmp_offset) != le32toh(file_header.file_size))
		throw UnsupportedFileTypeException("Could not parse BMP File: file size mismatch");
	if (le32toh(header.header_size) != sizeof(header))
		throw UnsupportedFileTypeException("Could not parse BMP File: Unsupported BITMAPV5HEADER size");
	if (le32toh(header.compress_type) != 0)
		throw UnsupportedFileTypeException("Could not parse BMP File: Only uncompressed BMP files can be parsed");
	if (le32toh(header.nplanes) != 1)
		throw UnsupportedFileTypeException("Could not parse BMP File: Only one plane should exist in the BMP file");
	if (le32toh(header.bits_per_pixel) != 24)
		throw UnsupportedFileTypeException("Could not parse BMP File: Only 24bit/pixel BMP's are supported");
	//if height<0 -> read top to bottom instead of bottom to top
	bool invertedLines = from_little_endian(header.height) < 0;
	image.height = std::abs(from_little_endian(header.height));
	image.width = std::abs(from_little_endian(header.width));
	unsigned int line_padding = from_little_endian(header.pixel_size) / image.height - (3 * image.width);
	//re-initialize the image bitmap
	image.bitmap.clear();
	image.bitmap.assign(image.height * image.width, Color());
	//okay let's read the pixels themselves:
	//they are arranged left->right., bottom->top if height>0, top->bottom if height<0, b,g,r
	for (unsigned int i = 0; i < image.get_height(); i++)
	{
		//loop over all lines
		for (unsigned int j = 0; j < image.get_width(); j++)
		{
			//loop over all pixels in a line
			//we cast &color to char*. since the color fields are ordered blue,green,red, the data read should be written in the right variables
			if (invertedLines)
			{
				//store top-to-bottom
				in.read((char*) &image(j, image.height - 1 - i), 3 * sizeof(uint8_t));
			}
			else
			{
				//store bottom-to-top
				in.read((char*) &image(j, i), 3 * sizeof(uint8_t));
			}
		}
		if (line_padding > 0)
		{
			in.read((char*) padding, line_padding);
		}
	}
	//okay we're done
	return in;
}