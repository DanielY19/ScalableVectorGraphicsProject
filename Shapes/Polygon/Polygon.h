#ifndef SCALABLEVECTORGRAPHICS_POLYGON_H
#define SCALABLEVECTORGRAPHICS_POLYGON_H

#include "../../Shape/Shape.h"

class Polygon : public Shape {
public:
    Polygon(const Point *points, unsigned pointsSize, const char *stroke, const char *fill);

    void print() const override;

    void translate(float verticalTrl, float horizontalTrl) override;

    void scale(float verticalScl, float horizontalScl) override;

    void saveToSvgFile(std::ofstream& file) const override;

    ~Polygon() override = default;

private:
    const static unsigned FIRST = 0;

    void calculateSurroundingRectangle();
};


class PolygonCreator : public ShapeCreator {
public:
    PolygonCreator() : ShapeCreator("polygon") {};

    Element *userCreateShape(std::istream &input) const override;

    Element *svgCreateShape(std::ifstream &file) const override;
};


#endif //SCALABLEVECTORGRAPHICS_POLYGON_H
