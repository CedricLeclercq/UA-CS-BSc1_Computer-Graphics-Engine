//
// Created by Cédric Leclercq on 29/04/2021.
//

#ifndef README_MD_FIGUREDRAWER_H
#define README_MD_FIGUREDRAWER_H

class FigureDrawer {
public:
    // Draw figures
    static void drawCube(Figure * figure) {
        figure->figureClass = Cube;


        // Creating all the points
        auto * point1 = new Vector3D;
        auto * point2 = new Vector3D;
        auto * point3 = new Vector3D;
        auto * point4 = new Vector3D;
        auto * point5 = new Vector3D;
        auto * point6 = new Vector3D;
        auto * point7 = new Vector3D;
        auto * point8 = new Vector3D;

        point1->x = 1; point1->y = -1; point1->z = -1;
        point2->x = -1; point2->y = 1; point2->z = -1;
        point3->x = 1; point3->y = 1; point3->z = 1;
        point4->x = -1; point4->y = -1; point4->z = 1;
        point5->x = 1; point5->y = 1; point5->z = -1;
        point6->x = -1; point6->y = -1; point6->z = -1;
        point7->x = 1; point7->y = -1; point7->z = 1;
        point8->x = -1; point8->y = 1; point8->z = 1;

        figure->points.push_back(point1);
        figure->points.push_back(point2);
        figure->points.push_back(point3);
        figure->points.push_back(point4);
        figure->points.push_back(point5);
        figure->points.push_back(point6);
        figure->points.push_back(point7);
        figure->points.push_back(point8);



        // Creating all the faces
        auto * face1 = new Face({point1,point5,point3,point7});
        auto * face2 = new Face({point5,point2,point8,point3});
        auto * face3 = new Face({point2,point6,point4,point8});
        auto * face4 = new Face({point6,point1,point7,point4});
        auto * face5 = new Face({point7,point3,point8,point4});
        auto * face6 = new Face({point1,point6,point2,point5});


        // And pushing back to the faces vector
        figure->faces.push_back(face1);
        figure->faces.push_back(face2);
        figure->faces.push_back(face3);
        figure->faces.push_back(face4);
        figure->faces.push_back(face5);
        figure->faces.push_back(face6);


        for (auto face: figure->faces) {
            figure->lines.emplace_back(face->point_indexes[0],face->point_indexes[1]);
            figure->lines.emplace_back(face->point_indexes[1],face->point_indexes[2]);
            figure->lines.emplace_back(face->point_indexes[2],face->point_indexes[3]);
            figure->lines.emplace_back(face->point_indexes[3],face->point_indexes[0]);
        }
    }
    static void drawTetrahedron(Figure * figure) {
        figure->figureClass = Tetrahedron;

        // Creating the points
        auto * point1 = new Vector3D;
        auto * point2 = new Vector3D;
        auto * point3 = new Vector3D;
        auto * point4 = new Vector3D;

        point1->x = 1; point1->y = -1; point1->z = -1;
        point2->x = -1; point2->y = 1; point2->z = -1;
        point3->x = 1; point3->y = 1; point3->z = 1;
        point4->x = -1; point4->y = -1; point4->z = 1;

        figure->points.push_back(point1);
        figure->points.push_back(point2);
        figure->points.push_back(point3);
        figure->points.push_back(point4);

        // Creating the faces
        auto * face1 = new Face({point1,point2,point3});
        auto * face2 = new Face({point2,point4,point3});
        auto * face3 = new Face({point1,point4,point2});
        auto * face4 = new Face({point1,point3,point4});

        figure->faces.push_back(face1);
        figure->faces.push_back(face2);
        figure->faces.push_back(face3);
        figure->faces.push_back(face4);

        for (auto face: figure->faces) {
            figure->lines.emplace_back(face->point_indexes[0],face->point_indexes[1]);
            figure->lines.emplace_back(face->point_indexes[1],face->point_indexes[2]);
            figure->lines.emplace_back(face->point_indexes[2],face->point_indexes[0]);
        }


    }
    static void drawOctahedron(Figure * figure) {
        figure->figureClass = Octahedron;

        // Creating all the points
        auto * point1 = new Vector3D;
        auto * point2 = new Vector3D;
        auto * point3 = new Vector3D;
        auto * point4 = new Vector3D;
        auto * point5 = new Vector3D;
        auto * point6 = new Vector3D;

        point1->x = 1; point1->y = 0; point1->z = 0;
        point2->x = 0; point2->y = 1; point2->z = 0;
        point3->x = -1; point3->y = 0; point3->z = 0;
        point4->x = 0; point4->y = -1; point4->z = 0;
        point5->x = 0; point5->y = 0; point5->z = -1;
        point6->x = 0; point6->y = 0; point6->z = 1;

        figure->points.push_back(point1);
        figure->points.push_back(point2);
        figure->points.push_back(point3);
        figure->points.push_back(point4);
        figure->points.push_back(point5);
        figure->points.push_back(point6);

        // Creating all the faces
        auto * face1 = new Face({point1,point2,point6});
        auto * face2 = new Face({point2,point3,point6});
        auto * face3 = new Face({point3,point4,point6});
        auto * face4 = new Face({point4,point1,point6});
        auto * face5 = new Face({point2,point1,point5});
        auto * face6 = new Face({point3,point2,point5});
        auto * face7 = new Face({point4,point3,point5});
        auto * face8 = new Face({point1,point4,point5});

        figure->faces.push_back(face1);
        figure->faces.push_back(face2);
        figure->faces.push_back(face3);
        figure->faces.push_back(face4);
        figure->faces.push_back(face5);
        figure->faces.push_back(face6);
        figure->faces.push_back(face7);
        figure->faces.push_back(face8);

        for (auto &face: figure->faces) {
            figure->lines.emplace_back(face->point_indexes[0],face->point_indexes[1]);
            figure->lines.emplace_back(face->point_indexes[1],face->point_indexes[2]);
            figure->lines.emplace_back(face->point_indexes[2],face->point_indexes[0]);
            //figure->lines.emplace_back(face->point_indexes[3],face->point_indexes[0]);
        }
    }
    static void drawIcosahedron(Figure * figure) {
        figure->figureClass = Icosahedron;

        // Creating first point
        auto * point1 = new Vector3D;
        auto * point2 = new Vector3D;
        auto * point3 = new Vector3D;
        auto * point4 = new Vector3D;
        auto * point5 = new Vector3D;
        auto * point6 = new Vector3D;
        auto * point7 = new Vector3D;
        auto * point8 = new Vector3D;
        auto * point9 = new Vector3D;
        auto * point10 = new Vector3D;
        auto * point11 = new Vector3D;
        auto * point12 = new Vector3D;

        point1->x = 0; point1->y = 0; point1->z = (sqrt(5)/2);
        point2->x = cos(0); point2->y = sin(0); point2->z = 0.5;
        point3->x = cos(2 * M_PI / 5); point3->y = sin(2 * M_PI / 5); point3->z = 0.5;
        point4->x = cos(4 * M_PI / 5); point4->y = sin(4 * M_PI / 5); point4->z = 0.5;
        point5->x = cos(6 * M_PI / 5); point5->y = sin(6 * M_PI / 5); point5->z = 0.5;
        point6->x = cos(8 * M_PI / 5); point6->y = sin(8 * M_PI / 5); point6->z = 0.5;
        point7->x = cos(M_PI / 5); point7->y = sin(M_PI / 5); point7->z = -0.5;
        point8->x = cos(M_PI / 5 + 2 * M_PI / 5); point8->y = sin(M_PI / 5 + 2 * M_PI / 5); point8->z = -0.5;
        point9->x = cos(M_PI / 5 + 4 * M_PI / 5); point9->y = sin(M_PI / 5 + 4 * M_PI / 5); point9->z = -0.5;
        point10->x = cos(M_PI / 5 + 6 * M_PI / 5); point10->y = sin(M_PI / 5 + 6 * M_PI / 5); point10->z = -0.5;
        point11->x = cos(M_PI / 5 + 8 * M_PI / 5); point11->y = sin(M_PI / 5 + 8 * M_PI / 5); point11->z = -0.5;
        point12->x = 0; point12->y = 0; point12->z = -sqrt(5)/2;

        figure->points.push_back(point1);
        figure->points.push_back(point2);
        figure->points.push_back(point3);
        figure->points.push_back(point4);
        figure->points.push_back(point5);
        figure->points.push_back(point6);
        figure->points.push_back(point7);
        figure->points.push_back(point8);
        figure->points.push_back(point9);
        figure->points.push_back(point10);
        figure->points.push_back(point11);
        figure->points.push_back(point12);

        auto * face1 = new Face({point1,point2,point3});
        auto * face2 = new Face({point1,point3,point4});
        auto * face3 = new Face({point1,point4,point5});
        auto * face4 = new Face({point1,point5,point6});
        auto * face5 = new Face({point1,point6,point2});
        auto * face6 = new Face({point2,point7,point3});
        auto * face7 = new Face({point3,point7,point8});
        auto * face8 = new Face({point3,point8,point4});
        auto * face9 = new Face({point4,point8,point9});
        auto * face10 = new Face({point4,point9,point5});
        auto * face11 = new Face({point5,point9,point10});
        auto * face12 = new Face({point5,point10,point6});
        auto * face13 = new Face({point6,point10,point11});
        auto * face14 = new Face({point6,point11,point2});
        auto * face15 = new Face({point2,point11,point7});
        auto * face16 = new Face({point12,point8,point7});
        auto * face17 = new Face({point12,point9,point8});
        auto * face18 = new Face({point12,point10,point9});
        auto * face19 = new Face({point12,point11,point10});
        auto * face20 = new Face({point12,point7,point11});

        figure->faces.push_back(face1);
        figure->faces.push_back(face2);
        figure->faces.push_back(face3);
        figure->faces.push_back(face4);
        figure->faces.push_back(face5);
        figure->faces.push_back(face6);
        figure->faces.push_back(face7);
        figure->faces.push_back(face8);
        figure->faces.push_back(face9);
        figure->faces.push_back(face10);
        figure->faces.push_back(face11);
        figure->faces.push_back(face12);
        figure->faces.push_back(face13);
        figure->faces.push_back(face14);
        figure->faces.push_back(face15);
        figure->faces.push_back(face16);
        figure->faces.push_back(face17);
        figure->faces.push_back(face18);
        figure->faces.push_back(face19);
        figure->faces.push_back(face20);

        for (auto face: figure->faces) {
            figure->lines.emplace_back(face->point_indexes[0],face->point_indexes[1]);
            figure->lines.emplace_back(face->point_indexes[1],face->point_indexes[2]);
            figure->lines.emplace_back(face->point_indexes[2],face->point_indexes[0]);
        }
    }
    static void drawDodecahedron(Figure * figure) {
        figure->figureClass = Dodecahedron;

        // Creating iso points
        auto * pointI1 = new Vector3D;
        auto * pointI2 = new Vector3D;
        auto * pointI3 = new Vector3D;
        auto * pointI4 = new Vector3D;
        auto * pointI5 = new Vector3D;
        auto * pointI6 = new Vector3D;
        auto * pointI7 = new Vector3D;
        auto * pointI8 = new Vector3D;
        auto * pointI9 = new Vector3D;
        auto * pointI10 = new Vector3D;
        auto * pointI11 = new Vector3D;
        auto * pointI12 = new Vector3D;

        pointI1->x = 0; pointI1->y = 0; pointI1->z = (sqrt(5)/2);
        pointI2->x = cos(0); pointI2->y = sin(0); pointI2->z = 0.5;
        pointI3->x = cos(2 * M_PI / 5); pointI3->y = sin(2 * M_PI / 5); pointI3->z = 0.5;
        pointI4->x = cos(4 * M_PI / 5); pointI4->y = sin(4 * M_PI / 5); pointI4->z = 0.5;
        pointI5->x = cos(6 * M_PI / 5); pointI5->y = sin(6 * M_PI / 5); pointI5->z = 0.5;
        pointI6->x = cos(8 * M_PI / 5); pointI6->y = sin(8 * M_PI / 5); pointI6->z = 0.5;
        pointI7->x = cos(M_PI / 5); pointI7->y = sin(M_PI / 5); pointI7->z = -0.5;
        pointI8->x = cos(M_PI / 5 + 2 * M_PI / 5); pointI8->y = sin(M_PI / 5 + 2 * M_PI / 5); pointI8->z = -0.5;
        pointI9->x = cos(M_PI / 5 + 4 * M_PI / 5); pointI9->y = sin(M_PI / 5 + 4 * M_PI / 5); pointI9->z = -0.5;
        pointI10->x = cos(M_PI / 5 + 6 * M_PI / 5); pointI10->y = sin(M_PI / 5 + 6 * M_PI / 5); pointI10->z = -0.5;
        pointI11->x = cos(M_PI / 5 + 8 * M_PI / 5); pointI11->y = sin(M_PI / 5 + 8 * M_PI / 5); pointI11->z = -0.5;
        pointI12->x = 0; pointI12->y = 0; pointI12->z = -sqrt(5)/2;

        // Declaring the points
        auto * point1 = new Vector3D;
        auto * point2 = new Vector3D;
        auto * point3 = new Vector3D;
        auto * point4 = new Vector3D;
        auto * point5 = new Vector3D;
        auto * point6 = new Vector3D;
        auto * point7 = new Vector3D;
        auto * point8 = new Vector3D;
        auto * point9 = new Vector3D;
        auto * point10 = new Vector3D;
        auto * point11 = new Vector3D;
        auto * point12 = new Vector3D;
        auto * point13 = new Vector3D;
        auto * point14 = new Vector3D;
        auto * point15 = new Vector3D;
        auto * point16 = new Vector3D;
        auto * point17 = new Vector3D;
        auto * point18 = new Vector3D;
        auto * point19 = new Vector3D;
        auto * point20 = new Vector3D;




        point1->x = (pointI1->x + pointI2->x + pointI3->x) / 3; point1->y = (pointI1->y + pointI2->y + pointI3->y) / 3; point1->z = (pointI1->z + pointI2->z + pointI3->z) / 3;
        point2->x = (pointI1->x + pointI3->x + pointI4->x) / 3; point2->y = (pointI1->y + pointI3->y + pointI4->y) / 3; point2->z = (pointI1->z + pointI3->z + pointI4->z) / 3;
        point3->x = (pointI1->x + pointI4->x + pointI5->x) / 3; point3->y = (pointI1->y + pointI4->y + pointI5->y) / 3; point3->z = (pointI1->z + pointI4->z + pointI5->z) / 3;
        point4->x = (pointI1->x + pointI5->x + pointI6->x) / 3; point4->y = (pointI1->y + pointI5->y + pointI6->y) / 3; point4->z = (pointI1->z + pointI5->z + pointI6->z) / 3;
        point5->x = (pointI1->x + pointI6->x + pointI2->x) / 3; point5->y = (pointI1->y + pointI6->y + pointI2->y) / 3; point5->z = (pointI1->z + pointI6->z + pointI2->z) / 3;
        point6->x = (pointI2->x + pointI7->x + pointI3->x) / 3; point6->y = (pointI2->y + pointI7->y + pointI3->y) / 3; point6->z = (pointI2->z + pointI7->z + pointI3->z) / 3;
        point7->x = (pointI3->x + pointI7->x + pointI8->x) / 3; point7->y = (pointI3->y + pointI7->y + pointI8->y) / 3; point7->z = (pointI3->z + pointI7->z + pointI8->z) / 3;
        point8->x = (pointI3->x + pointI8->x + pointI4->x) / 3; point8->y = (pointI3->y + pointI8->y + pointI4->y) / 3; point8->z = (pointI3->z + pointI8->z + pointI4->z) / 3;
        point9->x = (pointI4->x + pointI8->x + pointI9->x) / 3; point9->y = (pointI4->y + pointI8->y + pointI9->y) / 3; point9->z = (pointI4->z + pointI8->z + pointI9->z) / 3;
        point10->x = (pointI4->x + pointI9->x + pointI5->x) / 3; point10->y = (pointI4->y + pointI9->y + pointI5->y) / 3; point10->z = (pointI4->z + pointI9->z + pointI5->z) / 3;
        point11->x = (pointI5->x + pointI9->x + pointI10->x) / 3; point11->y = (pointI5->y + pointI9->y + pointI10->y) / 3; point11->z = (pointI5->z + pointI9->z + pointI10->z) / 3;
        point12->x = (pointI5->x + pointI6->x + pointI10->x) / 3; point12->y = (pointI5->y + pointI6->y + pointI10->y) / 3; point12->z = (pointI5->z + pointI6->z + pointI10->z) / 3;
        point13->x = (pointI6->x + pointI10->x + pointI11->x) / 3; point13->y = (pointI6->y + pointI10->y + pointI11->y) / 3; point13->z = (pointI6->z + pointI10->z + pointI11->z) / 3;
        point14->x = (pointI6->x + pointI11->x + pointI2->x) / 3; point14->y = (pointI6->y + pointI11->y + pointI2->y) / 3; point14->z = (pointI6->z + pointI11->z + pointI2->z) / 3;
        point15->x = (pointI2->x + pointI11->x + pointI7->x) / 3; point15->y = (pointI2->y + pointI11->y + pointI7->y) / 3; point15->z = (pointI2->z + pointI11->z + pointI7->z) / 3;
        point16->x = (pointI12->x + pointI7->x + pointI8->x) / 3; point16->y = (pointI12->y + pointI7->y + pointI8->y) / 3; point16->z = (pointI12->z + pointI7->z + pointI8->z) / 3;
        point17->x = (pointI12->x + pointI9->x + pointI8->x) / 3; point17->y = (pointI12->y + pointI9->y + pointI8->y) / 3; point17->z = (pointI12->z + pointI9->z + pointI8->z) / 3;
        point18->x = (pointI12->x + pointI10->x + pointI9->x) / 3; point18->y = (pointI12->y + pointI10->y + pointI9->y) / 3; point18->z = (pointI12->z + pointI10->z + pointI9->z) / 3;
        point19->x = (pointI12->x + pointI11->x + pointI10->x) / 3; point19->y = (pointI12->y + pointI11->y + pointI10->y) / 3; point19->z = (pointI12->z + pointI11->z + pointI10->z) / 3;
        point20->x = (pointI12->x + pointI7->x + pointI11->x) / 3; point20->y = (pointI12->y + pointI7->y + pointI11->y) / 3; point20->z = (pointI12->z + pointI7->z + pointI11->z) / 3;

        figure->points.push_back(point1);
        figure->points.push_back(point2);
        figure->points.push_back(point3);
        figure->points.push_back(point4);
        figure->points.push_back(point5);
        figure->points.push_back(point6);
        figure->points.push_back(point7);
        figure->points.push_back(point8);
        figure->points.push_back(point9);
        figure->points.push_back(point10);
        figure->points.push_back(point11);
        figure->points.push_back(point12);
        figure->points.push_back(point13);
        figure->points.push_back(point14);
        figure->points.push_back(point15);
        figure->points.push_back(point16);
        figure->points.push_back(point17);
        figure->points.push_back(point18);
        figure->points.push_back(point19);
        figure->points.push_back(point20);

        delete pointI1;
        delete pointI2;
        delete pointI3;
        delete pointI4;
        delete pointI5;
        delete pointI6;
        delete pointI7;
        delete pointI8;
        delete pointI9;
        delete pointI10;
        delete pointI11;
        delete pointI12;

        auto * face1 = new Face({point1,point2,point3,point4,point5});
        auto * face2 = new Face({point1,point6,point7,point8,point2});
        auto * face3 = new Face({point2,point8,point9,point10,point3});
        auto * face4 = new Face({point3,point10,point11,point12,point4});
        auto * face5 = new Face({point4,point12,point13,point14,point5});
        auto * face6 = new Face({point5,point14,point15,point6,point1});
        auto * face7 = new Face({point20,point19,point18,point17,point16});
        auto * face8 = new Face({point20,point15,point14,point13,point19});
        auto * face9 = new Face({point19,point13,point12,point11,point18});
        auto * face10 = new Face({point18,point11,point10,point9,point17});
        auto * face11 = new Face({point17,point9,point8,point7,point16});
        auto * face12 = new Face({point16,point7,point6,point15,point20});

        figure->faces.push_back(face1);
        figure->faces.push_back(face2);
        figure->faces.push_back(face3);
        figure->faces.push_back(face1);
        figure->faces.push_back(face4);
        figure->faces.push_back(face5);
        figure->faces.push_back(face6);
        figure->faces.push_back(face7);
        figure->faces.push_back(face8);
        figure->faces.push_back(face9);
        figure->faces.push_back(face10);
        figure->faces.push_back(face11);
        figure->faces.push_back(face12);

        for (auto face: figure->faces) {
            figure->lines.emplace_back(face->point_indexes[0],face->point_indexes[1]);
            figure->lines.emplace_back(face->point_indexes[1],face->point_indexes[2]);
            figure->lines.emplace_back(face->point_indexes[2],face->point_indexes[3]);
            figure->lines.emplace_back(face->point_indexes[3],face->point_indexes[4]);
            figure->lines.emplace_back(face->point_indexes[4],face->point_indexes[0]);
        }
        /*
        point1->x = (cos(0) + cos(2 * M_PI / 5))/3; point1->y = (sin(0) + sin(2 * M_PI / 5)) /3; point1->z = ((sqrt(5)/2) + 0.5 + 0.5) /3;
        point2->x = (cos(2 * M_PI / 5) + cos(4 * M_PI / 5)) / 3; point2->y = (sin(2 * M_PI / 5)+sin(4 * M_PI / 5))/3; point2->z = ((sqrt(5)/2) + 0.5 + 0.5) /3;
        point3->x = (cos(4 * M_PI / 5) + cos(6 * M_PI / 5)) /3; point3->y = (sin(4 * M_PI / 5) + sin(6 * M_PI / 5)) /3; point3->z = ((sqrt(5)/2) + 0.5 + 0.5) /3;
        point4->x = (cos(6 * M_PI / 5) + cos((8 * M_PI / 5))) /3; point4->y = (sin(6 * M_PI / 5) + sin(8 * M_PI / 5)) /3; point4->z = ((sqrt(5)/2) + 0.5 + 0.5) /3;
        point5->x = (cos(8 * M_PI / 5) + cos(0)) /3; point5->y = (sin(8 * M_PI / 5) + sin(0)) /3; point5->z = ((sqrt(5)/2) + 0.5 + 0.5) /3;
        point6->x = (cos(0) + cos(M_PI / 5) + cos(2 * M_PI / 5)) /3; point6->y = (sin(0) + sin(M_PI / 5) + sin(2 * M_PI / 5)) /3; point6->z = (0.5 + 0.5 - 0.5) /3;

        point7->x = (cos(2 * M_PI / 5) + cos(M_PI / 5) + cos(M_PI / 5 + 2 * M_PI / 5)) /3; point7->y = (sin(2 * M_PI / 5) + sin(M_PI / 5) + sin(M_PI / 5 + 2 * M_PI / 5)) /3; point7->z = (0.5 + 0.5 + 0.5) /3;
        point8->x = (cos(2 * M_PI / 5) + cos(M_PI / 5 + 2 * M_PI / 5) + cos(4 * M_PI / 5)) /3; point8->y = (sin(2 * M_PI / 5) + sin(M_PI / 5 + 2 * M_PI / 5) + sin(4 * M_PI / 5)) /3; point8->z = (0.5 + 0.5 + 0.5) /3;
        point9->x = (cos(4 * M_PI / 5) + cos(M_PI / 5 + 2 * M_PI / 5) + cos(M_PI / 5 + 4 * M_PI / 5)) /3; point9->y = (sin(4 * M_PI / 5) + sin(M_PI / 5 + 2 * M_PI / 5) + sin(M_PI / 5 + 4 * M_PI / 5)) /3; point9->z = (0.5 + 0.5 + 0.5) /3;
        point10->x = (cos(1 * M_PI / 5) + cos(1 * M_PI / 5) + cos(1 * M_PI / 5)) /3; point10->y = (sin(1 + M_PI / 5) + sin(1 + M_PI / 5) + sin(1 + M_PI / 5)) /3; point10->z = (0.5 + 0.5 + 0.5) /3;
        point11->x = (cos(1 * M_PI / 5) + cos(1 * M_PI / 5) + cos(1 * M_PI / 5)) /3; point11->y = (sin(1 + M_PI / 5) + sin(1 + M_PI / 5) + sin(1 + M_PI / 5)) /3; point11->z = (0.5 + 0.5 + 0.5) /3;
        point12->x = (cos(1 * M_PI / 5) + cos(1 * M_PI / 5) + cos(1 * M_PI / 5)) /3; point12->y = (sin(1 + M_PI / 5) + sin(1 + M_PI / 5) + sin(1 + M_PI / 5)) /3; point12->z = (0.5 + 0.5 + 0.5) /3;
        point13->x = (cos(1 * M_PI / 5) + cos(1 * M_PI / 5) + cos(1 * M_PI / 5)) /3; point13->y = (sin(1 + M_PI / 5) + sin(1 + M_PI / 5) + sin(1 + M_PI / 5)) /3; point13->z = (0.5 + 0.5 + 0.5) /3;
        point14->x = (cos(1 * M_PI / 5) + cos(1 * M_PI / 5) + cos(1 * M_PI / 5)) /3; point14->y = (sin(1 + M_PI / 5) + sin(1 + M_PI / 5) + sin(1 + M_PI / 5)) /3; point14->z = (0.5 + 0.5 + 0.5) /3;
        point15->x = (cos(1 * M_PI / 5) + cos(1 * M_PI / 5) + cos(1 * M_PI / 5)) /3; point15->y = (sin(1 + M_PI / 5) + sin(1 + M_PI / 5) + sin(1 + M_PI / 5)) /3; point15->z = (0.5 + 0.5 + 0.5) /3;
        point16->x = (cos(1 * M_PI / 5) + cos(1 * M_PI / 5) + cos(1 * M_PI / 5)) /3; point16->y = (sin(1 + M_PI / 5) + sin(1 + M_PI / 5) + sin(1 + M_PI / 5)) /3; point16->z = (0.5 + 0.5 + 0.5) /3;
        point17->x = (cos(1 * M_PI / 5) + cos(1 * M_PI / 5) + cos(1 * M_PI / 5)) /3; point17->y = (sin(1 + M_PI / 5) + sin(1 + M_PI / 5) + sin(1 + M_PI / 5)) /3; point17->z = (0.5 + 0.5 + 0.5) /3;
        point18->x = (cos(1 * M_PI / 5) + cos(1 * M_PI / 5) + cos(1 * M_PI / 5)) /3; point18->y = (sin(1 + M_PI / 5) + sin(1 + M_PI / 5) + sin(1 + M_PI / 5)) /3; point18->z = (0.5 + 0.5 + 0.5) /3;
        point19->x = (cos(1 * M_PI / 5) + cos(1 * M_PI / 5) + cos(1 * M_PI / 5)) /3; point19->y = (sin(1 + M_PI / 5) + sin(1 + M_PI / 5) + sin(1 + M_PI / 5)) /3; point19->z = (0.5 + 0.5 + 0.5) /3;
        point20->x = (cos(1 * M_PI / 5) + cos(1 * M_PI / 5) + cos(1 * M_PI / 5)) /3; point20->y = (sin(1 + M_PI / 5) + sin(1 + M_PI / 5) + sin(1 + M_PI / 5)) /3; point20->z = (0.5 + 0.5 + 0.5) /3;
         */
    }
    static void drawCone(Figure * figure, const int n, const double h) {
        figure->figureClass = Cone;

        auto * topPoint = new Vector3D;
        topPoint->x = 0; topPoint->y = 0; topPoint->z = h;
        figure->points.push_back(topPoint);
        Vector3D * previousPoint = nullptr;
        Vector3D * firstPoint = nullptr;

        for (int i = 0; i < n; i++) {
            auto * newPoint = new Vector3D;
            if ( i == 0) {
                firstPoint = newPoint;
                newPoint->x = cos(0); newPoint->y = sin(0); newPoint->z = 0;
            } else {
                newPoint->x = cos((2*i*M_PI) / n); newPoint->y = sin((2*i*M_PI) / n); newPoint->z = 0;
                auto * newFace = new Face({previousPoint,newPoint,topPoint});
                figure->faces.push_back(newFace);
            }

            figure->points.push_back(newPoint);
            previousPoint = newPoint;
        }


        auto * newFace = new Face({previousPoint,firstPoint,topPoint});
        figure->faces.push_back(newFace);

        for (auto face: figure->faces) {
            figure->lines.emplace_back(face->point_indexes[0],face->point_indexes[1]);
            figure->lines.emplace_back(face->point_indexes[1],face->point_indexes[2]);
            figure->lines.emplace_back(face->point_indexes[2],face->point_indexes[0]);
        }


    }
    static void drawCylinder(Figure * figure, const int n, const double h) {
        figure->figureClass = Cylinder;

        Vector3D * previousPointDown = nullptr;
        Vector3D * previousPointUp = nullptr;
        Vector3D * firstPointDown = nullptr;
        Vector3D * firstPointUp = nullptr;

        vector<Vector3D*> upperPoints;
        vector<Vector3D*> downPoints;
        //auto * faceTop = new Face({});
        //auto * faceBottom = new Face({});
        for (int i = 0; i < n; i++) {
            auto * newPointDown = new Vector3D;
            auto * newPointUp = new Vector3D;
            if ( i == 0) {
                newPointDown->x = cos(0); newPointDown->y = sin(0); newPointDown->z = 0;
                newPointUp->x = cos(0); newPointUp->y = sin(0); newPointUp->z = h;
                firstPointDown = newPointDown;
                firstPointUp = newPointUp;
            } else {
                newPointDown->x = cos((2*i*M_PI) / n); newPointDown->y = sin((2*i*M_PI) / n); newPointDown->z = 0;
                newPointUp->x = cos((2*i*M_PI) / n); newPointUp->y = sin((2*i*M_PI) / n); newPointUp->z = h;
                auto * newFace = new Face({newPointDown,newPointUp,previousPointUp,previousPointDown});
                figure->faces.push_back(newFace);
            }

            upperPoints.push_back(newPointUp);
            downPoints.push_back(newPointDown);
            figure->points.push_back(newPointUp);
            figure->points.push_back(newPointDown);
            previousPointUp = newPointUp;
            previousPointDown = newPointDown;

            //faceTop->point_indexes.push_back(newPointUp);
            //faceBottom->point_indexes.push_back(newPointDown);
        }

        auto * newFace = new Face({firstPointDown,firstPointUp,previousPointUp,previousPointDown});
        auto * upperFace = new Face(upperPoints);
        auto * lowerFace = new Face(downPoints);
        figure->faces.push_back(newFace);
        figure->faces.push_back(upperFace);
        figure->faces.push_back(lowerFace);

        for (auto face: figure->faces) {
            figure->lines.emplace_back(face->point_indexes[0],face->point_indexes[1]);
            figure->lines.emplace_back(face->point_indexes[1],face->point_indexes[2]);
            figure->lines.emplace_back(face->point_indexes[2],face->point_indexes[3]);
            figure->lines.emplace_back(face->point_indexes[3],face->point_indexes[0]);
        }
    }
    static void drawSphere(Figure * figure, const int n) {

        figure->drawIcosahedron();
        figure->figureClass = Sphere;

        if (n != 0) {
            figure->lines.clear();
        }

        vector<Face*> newFaces;
        for (int i = 0; i < n; i++) {
            for (auto face: figure->faces) {

                auto * point1 = new Vector3D;
                point1->x = ((face->point_indexes[0]->x + face->point_indexes[1]->x) / 2);
                point1->y = ((face->point_indexes[0]->y + face->point_indexes[1]->y) / 2);
                point1->z = ((face->point_indexes[0]->z + face->point_indexes[1]->z) / 2);

                auto * point2 = new Vector3D;
                point2->x = ((face->point_indexes[0]->x + face->point_indexes[2]->x) / 2);
                point2->y = ((face->point_indexes[0]->y + face->point_indexes[2]->y) / 2);
                point2->z = ((face->point_indexes[0]->z + face->point_indexes[2]->z) / 2);

                auto * point3 = new Vector3D;
                point3->x = ((face->point_indexes[1]->x + face->point_indexes[2]->x) / 2);
                point3->y = ((face->point_indexes[1]->y + face->point_indexes[2]->y) / 2);
                point3->z = ((face->point_indexes[1]->z + face->point_indexes[2]->z) / 2);

                auto * newFace1 = new Face({face->point_indexes[0],point1,point2});
                auto * newFace2 = new Face({face->point_indexes[1],point3,point1});
                auto * newFace3 = new Face({face->point_indexes[2],point2,point3});
                auto * newFace4 = new Face({point1,point3,point2});
                figure->points.push_back(point1);
                figure->points.push_back(point2);
                figure->points.push_back(point3);
                newFaces.push_back(newFace1);
                newFaces.push_back(newFace2);
                newFaces.push_back(newFace3);
                newFaces.push_back(newFace4);
            }

            figure->faces.clear();

            for (auto face: newFaces) {
                figure->faces.push_back(face);
            } newFaces.clear();
        }

        // Scaling all the points
        for (auto & point: figure->points) {
            double r = sqrt(pow(point->x, 2) + pow(point->y,2) + pow(point->z,2));
            point->x = point->x / r;
            point->y = point->y / r;
            point->z = point->z / r;
        }

        for (auto face: figure->faces) {
            figure->lines.emplace_back(face->point_indexes[0],face->point_indexes[1]);
            figure->lines.emplace_back(face->point_indexes[1],face->point_indexes[2]);
            figure->lines.emplace_back(face->point_indexes[2],face->point_indexes[0]);
        }
    }
    static void drawTorus(Figure * figure, const double r, const double R, const int n, const int m) {
        figure->figureClass = Torus;

        //vector<pair<Vector3D*,pair<int,int>>> pointTracker = {}; // Vector that keeps all the points and the i and j they are linked to
        vector<pair<Vector3D*,pair<int,int>>> firstCircle = {}; // All pairs that have i = 0;
        vector<pair<Vector3D*,pair<int,int>>> lastCircle = {}; // All pairs that have i = n;
        vector<pair<Vector3D*,pair<int,int>>> underCircle = {}; // All pairs that have j = 0;
        vector<pair<Vector3D*,pair<int,int>>> upperCircle = {}; // All pairs that have j = m;

        vector<vector<Vector3D*>> pointTracker = {};

        for (int i = 0; i < n; i++) {
            vector<Vector3D*> currentIPonts;
            for (int j = 0; j < m; j++) {
                auto *newPoint = new Vector3D;
                if (j == 0 and i == 0) {
                    newPoint->x = (R + r * cos(0)) * cos(0);
                    newPoint->y = (R + r * cos(0)) * sin(0);
                    newPoint->z = r * sin(0);


                } else if (i == 0 and j != 0) {
                    newPoint->x = (R + r * cos((2*j*M_PI) / m)) * cos(0);
                    newPoint->y = (R + r * cos((2*j*M_PI) / m)) * sin(0);
                    newPoint->z = r * sin((2*j*M_PI) / m);

                } else if (j == 0 and i != 0) {
                    newPoint->x = (R + r * cos(0)) * cos((2*i*M_PI) / n);
                    newPoint->y = (R + r * cos(0)) * sin((2*i*M_PI) / n);
                    newPoint->z = r * sin(0);

                } else {
                    newPoint->x = (R + r * cos((2*j*M_PI) /m)) * cos((2*i*M_PI) / n);
                    newPoint->y = (R + r * cos((2*j*M_PI) /m)) * sin((2*i*M_PI) / n);
                    newPoint->z = r * sin((2*j*M_PI) / m);
                }

                if (i == 0) {
                    // Collecting all the points on the first circle
                    firstCircle.emplace_back(newPoint,make_pair(i,j));
                }
                if (i == n - 1) {
                    // Collecting all the points on the last circle
                    lastCircle.emplace_back(newPoint,make_pair(i,j));
                }
                if (j == 0) {
                    underCircle.emplace_back(newPoint,make_pair(i,j));
                }
                if (j == m - 1) {
                    upperCircle.emplace_back(newPoint,make_pair(i,j));
                }
                currentIPonts.push_back(newPoint);
                figure->points.push_back(newPoint);
            }
            pointTracker.push_back(currentIPonts);
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                auto * newFace = new Face({pointTracker[i][j],pointTracker[(i+1) % n][j],pointTracker[(i+1) % n][(j+1) % m],pointTracker[i][(j+1) % m]});
                figure->faces.push_back(newFace);
            }
        }



        for (auto face: figure->faces) {
            figure->lines.emplace_back(face->point_indexes[0],face->point_indexes[1]);
            figure->lines.emplace_back(face->point_indexes[1],face->point_indexes[2]);
            figure->lines.emplace_back(face->point_indexes[2],face->point_indexes[3]);
            figure->lines.emplace_back(face->point_indexes[3],face->point_indexes[0]);
        }
    }
};

#endif //README_MD_FIGUREDRAWER_H

