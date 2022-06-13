#ifndef SCALABLEVECTORGRAPHICS_LINE_H
#define SCALABLEVECTORGRAPHICS_LINE_H

#include "../../Shape/Shape.h"

class Line : public Shape {
public:
    Line(float x1, float y1, float x2, float y2, const char *stroke);

    void print() const override;

    void scale(float verticalScl, float horizontalScl) override;

    bool isContained(float tlX, float tlY, float brX, float brY) const override;

    ~Line() override = default;

private:
    const static unsigned FIRST = 0;
    const static unsigned SECOND = 1;
};

class LineCreator : public ShapeCreator {
public:
    LineCreator() : ShapeCreator("line") {}

    Shape *userCreateShape(std::istream& input) const override;

    Shape *svgCreateShape(std::ifstream& file) const override;
};

#endif //SCALABLEVECTORGRAPHICS_LINE_H
