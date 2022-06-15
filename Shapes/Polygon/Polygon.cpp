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


Polygon::Polygon(const Point *points, unsigned int pointsSize, const char *stroke,
                 const char *fill)
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

bool isNumeric(const char *data) {
    while (*data != '\0') {
        if (((*data < '0' || *data > '9') && *data != '.' && *data != '-'))
            return false;
        data++;
    }
    return true;
}

float parseDataToNumber(const char *data) {
    float actualNumber = 0;
    float fractions = 1;
    bool foundFractions = false;
    int sign = 1;

    while (*data != '\0') {
        if (*data == '-')
            sign = -1;
        else if (*data == '.')
            foundFractions = true;
        else if (!foundFractions)
            actualNumber = actualNumber * 10 + (*data - '0');
        else
            actualNumber = (*data - '0') / fractions;

        fractions *= (foundFractions) ? (10) : (1);
        data++;
    }
    return actualNumber * sign;
}

Shape *PolygonCreator::userCreateShape(std::istream &input) const {
    std::string data, fill;
    std::vector<Point> points;
    unsigned counter = 0;
    float coord1 = 0;
    float coord2 = 0;

    while (input >> data && isNumeric(data.c_str())) {
        if (counter == 0) {
            coord1 = parseDataToNumber(data.c_str());
            counter++;
        } else {
            coord2 = parseDataToNumber(data.c_str());
            points.emplace_back(coord1, coord2);
            counter = 0;
        }
    }

    input >> fill;

    if (counter)
        return nullptr;

    return new Polygon(points.data(), points.size(), data.c_str(), fill.c_str());
}

std::vector<Point> findPoints(std::ifstream &file, unsigned currentIndex) {
    //equals check
    std::vector<Point> points;
    float coord1 = 0;
    float coord2 = 0;

    char symbol = 0;

    unsigned apostropheCount = 0;

    bool foundEquals = false;
    bool foundFractions = false;

    float fractions = 1;
    int sign = 1;
    unsigned signCoord = 0;

    unsigned counter = 0;

    while (file.get(symbol) && apostropheCount != 2 && symbol != '>') {
        if (symbol == '=')
            foundEquals = true;
        else if (symbol == '\"')
            apostropheCount++;
        else if (symbol == '.')
            foundFractions = true;
        else if (symbol == ',')
            counter++;
        else if (symbol == '-') {
            sign *= -1;
            signCoord = counter;
        } else if (symbol >= '0' && symbol <= '9' && !foundFractions) {
            if (counter == 0)
                coord1 = coord1 * 10 + (symbol - '0');
            else {
                coord2 = coord2 * 10 + (symbol - '0');

                if (signCoord == 0)
                    coord1 *= sign;
                else coord2 *= sign;

                points.emplace_back(coord1, coord2);
                coord1 = 0;
                coord2 = 0;
                counter = 0;
                foundFractions = false;
            }
        } else if (symbol >= '0' && symbol <= '9') {
            fractions *= 10;
            if (counter == 0)
                coord1 = coord1 * 10 + (symbol - '0');
            else {
                coord2 = coord2 * 10 + (symbol - '0');

                if (signCoord == 0)
                    coord1 *= sign;
                else coord2 *= sign;

                points.emplace_back(coord1, coord2);
                counter = 0;
                coord1 = 0;
                coord2 = 0;
                foundFractions = false;
            }
        }
    }


    file.seekg(currentIndex);
    return points;
}

Shape *PolygonCreator::svgCreateShape(std::ifstream &file) const {
    unsigned currentIndex = file.tellg();
    char buffer[7];

    if (findSource(buffer, "points", file)) {
        std::vector<Point> points(findPoints(file, currentIndex));
        const char *stroke = findTextAttribute(file, "stroke");
        const char *fill = findTextAttribute(file, "fill");

        return new Polygon(points.data(), points.size(), stroke, fill);
    }

    file.seekg(currentIndex);
    return nullptr;
}