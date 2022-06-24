#ifndef SCALABLEVECTORGRAPHICS_LINE_H
#define SCALABLEVECTORGRAPHICS_LINE_H

#include "../../Shape/Shape.h"

class Line : public Shape {
public:
    Line(float x1, float y1, float x2, float y2, const char *stroke);

    void print() const override;

    void translate(float verticalTrl, float horizontalTrl) override;

    void scale(float verticalScl, float horizontalScl) override;

    void saveToFormat(std::ofstream &file) const override;

    void saveToSvgFile(std::ofstream& file) const override;

    ~Line() override = default;

private:
    unsigned first;
    unsigned second;
};

class LineCreator : public ShapeCreator {
public:
    LineCreator() : ShapeCreator("line") {}

    Element *userCreateShape(std::istream& input) const override;

    Element *formatCreateShape(std::ifstream &file) const override;

    Element *svgCreateShape(std::ifstream& file) const override;
};

#endif //SCALABLEVECTORGRAPHICS_LINE_H
