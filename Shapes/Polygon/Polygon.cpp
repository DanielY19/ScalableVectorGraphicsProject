#include "Polygon.h"
#include <iostream>
#include <stdexcept>

float resultX(const Point &a) {
    return a.getX();
}

float resultY(const Point &a) {
    return a.getY();
}

bool compareXMin(const Point &a, const Point &b) {
    return a.getX() < b.getX();
}

bool compareXMax(const Point &a, const Point &b) {
    return a.getX() > b.getX();
}

bool compareYMin(const Point &a, const Point &b) {
    return a.getY() < b.getY();
}

bool compareYMax(const Point &a, const Point &b) {
    return a.getY() > b.getY();
}


float getExtremum(const Point *points, unsigned pointsSize, bool (*compare)(const Point &a, const Point &b),
                  float (*result)(const Point &a)) {
    if (points == nullptr || pointsSize == 0)
        throw std::invalid_argument("Invalid points!");

    unsigned index = 0;

    for (unsigned i = 1; i < pointsSize; i++)
        if (compare(points[index], points[i]))
            index = i;

    return result(points[index]);
}

float getXMin(const Point *points, unsigned int pointsSize) {
    return getExtremum(points, pointsSize, compareXMax, resultX);
}

float getXMax(const Point *points, unsigned int pointsSize) {
    return getExtremum(points, pointsSize, compareXMin, resultX);
}

float getYMin(const Point *points, unsigned int pointsSize) {
    return getExtremum(points, pointsSize, compareYMax, resultY);
}

float getYMax(const Point *points, unsigned int pointsSize) {
    return getExtremum(points, pointsSize, compareYMin, resultY);
}


Polygon::Polygon(const Point *points, unsigned int pointsSize, const char *fill,
                 const char *stroke)
        : Shape(stroke, fill, Point(getXMin(points, pointsSize), getYMax(points, pointsSize)),
                Point(getXMax(points, pointsSize),
                      getYMin(points, pointsSize))) {

    for (unsigned i = 0; i < pointsSize; i++)
        this->points.push_back(points[i]);
}

void Polygon::print() const {
    std::cout << "polygon ";
    this->Shape::print();
    std::cout << this->stroke << ' ' << this->fill << "\n\n";
}

void Polygon::scale(float verticalScl, float horizontalScl) {
    unsigned size = this->points.size();

    for (unsigned i = 1; i < size; i++)
        scaleForLineAndPolygon(this->points[Polygon::FIRST], this->points[i], verticalScl, horizontalScl);

    this->changeTL(getXMin(this->points.data(), this->points.size()),
                   getYMax(this->points.data(), this->points.size()));

    this->changeBR(getXMax(this->points.data(), this->points.size()),
                   getYMin(this->points.data(), this->points.size()));
}

Shape *PolygonCreator::userCreateShape(std::istream &input) const {
    return nullptr;
}

Shape *PolygonCreator::svgCreateShape(std::ifstream &file) const {
    return nullptr;
}