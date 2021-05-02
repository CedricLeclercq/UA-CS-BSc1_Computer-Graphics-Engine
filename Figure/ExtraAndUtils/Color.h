//
// Created by Cédric Leclercq on 22/02/2021.
//

#ifndef ENGINE_COLOR_H
#define ENGINE_COLOR_H


class Color {
public:
    double red,green,blue; // Colors of the figure in RGB format

    /**
     * \brief default constructor
     */
    Color()=default;
    /**
     * Constructor that initialises all the member variables
     * @param red
     * @param green
     * @param blue
     */
    Color(double red, double green, double blue) {
        this->red = red;
        this->green = green;
        this->blue = blue;
    }

};


#endif //ENGINE_COLOR_H
