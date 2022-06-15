#ifndef SCALABLEVECTORGRAPHICS_SHAPE_H
#define SCALABLEVECTORGRAPHICS_SHAPE_H

#include <fstream>
#include <string>
#include <vector>
#include "Point/Point.h"

class Shape {
public:
    Shape(const char *stroke, const char *fill, const Point &TL, const Point &BR);

    Shape(const Shape &other) = delete;

    virtual void print() const;

    void bringForward(unsigned layers);

    void sendBackwards(unsigned layers);

    void translate(float verticalTrl, float horizontalTrl);

    virtual void scale(float verticalScl, float horizontalScl) = 0;

    //void rotate(int angle);//for later

    virtual bool isContained(float tlX, float tlY, float brX, float brY) const;

    virtual void saveToSvgFile(std::ofstream& file) const = 0;

    Shape &operator=(const Shape &other) = delete;

    unsigned getID() const;

    virtual ~Shape() = default;

protected:
    std::vector<Point> points;
    std::string stroke;
    std::string fill;

    Point getCenterOfSurroundingRect() const;

    void changeTL(float x, float y);

    void changeBR(float x, float y);

    const Point &getTL() const;

    const Point &getBR() const;

private:
    static unsigned idGenerator;

    unsigned id;

    //Surrounding rectangle
    Point TL;
    Point BR;
};


class ShapeCreator {
public:
    ShapeCreator(const char *targetedShape);

    ShapeCreator(const ShapeCreator &other) = delete;

    //additionalFunctionForTheOtherFormat();

    virtual Shape *svgCreateShape(std::ifstream &file) const = 0;

    virtual Shape *userCreateShape(std::istream &input) const = 0;

    const char *getTargetedShape() const;

    ShapeCreator &operator=(const ShapeCreator &other) = delete;

    virtual ~ShapeCreator() = default;

protected:
    std::string shape;
};

void scaleForLineAndPolygon(const Point &first, Point &second, float verticalScl, float horizontalScl);

float findNumericAttribute(std::ifstream &file, const char *searchedAttribute);

const char *findTextAttribute(std::ifstream &file, const char *searchedAttribute);

bool findSource(char *buffer, const char *source, std::ifstream &file);

float parseToNumber(std::ifstream &file, unsigned currentIndex);

const char *parseToText(std::ifstream& file,unsigned currentIndex);

#endif //SCALABLEVECTORGRAPHICS_SHAPE_H
