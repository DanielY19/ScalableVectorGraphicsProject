#ifndef SCALABLEVECTORGRAPHICS_CIRCLE_H
#define SCALABLEVECTORGRAPHICS_CIRCLE_H

#include "../../Shape/Shape.h"

class Circle : public Shape {
public:
    Circle(float x, float y, float radius, const char *stroke, const char *fill);

    void print() const override;

    void scale(float verticalScl, float horizontalScl) override;

    void saveToSvgFile(std::ofstream& file) const override;

    ~Circle() override = default;

private:
    const static unsigned CENTER = 0;

    float radius;
};

class CircleCreator : public ShapeCreator {
public:
    CircleCreator() : ShapeCreator("circle") {}

    Element *userCreateShape(std::istream &input) const override;

    Element *svgCreateShape(std::ifstream& file) const override;
};


#endif //SCALABLEVECTORGRAPHICS_CIRCLE_H
