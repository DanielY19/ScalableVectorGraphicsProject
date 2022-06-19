#ifndef SCALABLEVECTORGRAPHICS_SHAPE_H
#define SCALABLEVECTORGRAPHICS_SHAPE_H
#include "../Element/Element.h"
#include <string>
#include <vector>


class Shape :public Element{
public:
    Shape(const char *stroke, const char *fill, const Point &TL, const Point &BR);

    Shape(const Shape &other) = delete;

    virtual void print() const override;

    void bringForward(unsigned layers) override;

    void sendBackwards(unsigned layers) override;

    void translate(float verticalTrl, float horizontalTrl) override;

    virtual void scale(float verticalScl, float horizontalScl) = 0;

    //virtual void rotate(int angle) = 0;//for later

    virtual void saveToSvgFile(std::ofstream& file) const = 0;

    Shape &operator=(const Shape &other) = delete;

    unsigned getID() const override;

    ~Shape() override = default;

protected:
    std::vector<Point> points;
    std::string stroke;
    std::string fill;

    static unsigned shapeIDGenerator;

};


class ShapeCreator {
public:
    ShapeCreator(const char *targetedShape);

    ShapeCreator(const ShapeCreator &other) = delete;

    //additionalFunctionForTheOtherFormat();

    virtual Element *svgCreateShape(std::ifstream &file) const = 0;

    virtual Element *userCreateShape(std::istream &input) const = 0;

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
