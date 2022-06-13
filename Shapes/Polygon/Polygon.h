#ifndef SCALABLEVECTORGRAPHICS_POLYGON_H
#define SCALABLEVECTORGRAPHICS_POLYGON_H

#include "../../Shape/Shape.h"

class Polygon : public Shape {
public:
    Polygon(const Point *points, unsigned pointsSize, const char *stroke, const char *fill);

    void print() const override;

    void scale(float verticalScl, float horizontalScl) override;

    ~Polygon() override = default;

private:
    const static unsigned FIRST = 0;
};


class PolygonCreator : public ShapeCreator {
public:
    PolygonCreator() : ShapeCreator("polygon") {};

    Shape *userCreateShape(std::istream &input) const override;

    Shape *svgCreateShape(std::ifstream &file) const override;
};


#endif //SCALABLEVECTORGRAPHICS_POLYGON_H
