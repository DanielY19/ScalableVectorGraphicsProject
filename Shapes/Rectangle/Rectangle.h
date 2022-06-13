#ifndef SCALABLEVECTORGRAPHICS_RECTANGLE_H
#define SCALABLEVECTORGRAPHICS_RECTANGLE_H

#include "../../Shape/Shape.h"

class Rectangle : public Shape {
public:
    Rectangle(float x, float y, float width, float height, const char *stroke, const char *fill);

    void print() const override;

    void scale(float verticalScl, float horizontalScl) override;

    ~Rectangle() override = default;

private:
    float width;
    float height;

    static unsigned TOPLEFT;
    static unsigned BOTTOMRIGHT;
};

class RectangleCreator : public ShapeCreator {
public:
    RectangleCreator() : ShapeCreator("rect") {}

    Shape *userCreateShape(std::istream &input) const override;

    Shape *svgCreateShape(std::ifstream& file) const override;
};


#endif //SCALABLEVECTORGRAPHICS_RECTANGLE_H
