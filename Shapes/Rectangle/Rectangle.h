#ifndef SCALABLEVECTORGRAPHICS_RECTANGLE_H
#define SCALABLEVECTORGRAPHICS_RECTANGLE_H

#include "../../Shape/Shape.h"

class Rectangle : public Shape {
public:
    Rectangle(float x, float y, float width, float height, const char *stroke, const char *fill);

    void print() const override;

    void translate(float verticalTrl, float horizontalTrl) override;

    void scale(float verticalScl, float horizontalScl) override;

    void saveToFormat(std::ofstream &file) const override;

    void saveToSvgFile(std::ofstream &file) const override;

    ~Rectangle() override = default;

private:
    float width;
    float height;

    unsigned topLeft;
    unsigned bottomRight;
};

class RectangleCreator : public ShapeCreator {
public:
    RectangleCreator() : ShapeCreator("rect") {}

    Element *userCreateShape(std::istream &input) const override;

    Element *formatCreateShape(std::ifstream &file) const override;

    Element *svgCreateShape(std::ifstream &file) const override;
};


#endif //SCALABLEVECTORGRAPHICS_RECTANGLE_H
