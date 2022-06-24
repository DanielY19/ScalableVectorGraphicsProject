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
        : Shape(stroke, fill, Point(getXMin(points, pointsSize), getYMin(points, pointsSize)),
                Point(getXMax(points, pointsSize),
                      getYMax(points, pointsSize))) {

    for (unsigned i = 0; i < pointsSize; i++)
        this->points.push_back(points[i]);
}

void Polygon::print() const {
    std::cout << "polygon ";
    this->Shape::print();
    std::cout << this->stroke << ' ' << this->fill << "\n\n";
}

void Polygon::translate(float verticalTrl, float horizontalTrl) {
    unsigned size = this->points.size();

    for (unsigned i = 0; i < size; i++)
        this->points[i].translate(verticalTrl, horizontalTrl);

    this->calculateSurroundingRectangle();
}

void Polygon::scale(float verticalScl, float horizontalScl) {
    unsigned size = this->points.size();
    std::vector<Point> copyPoints(this->points);

    for (unsigned i = 0; i < size - 1; i++)
        scaleForLineAndPolygon(copyPoints[i], this->points[i + 1], verticalScl, horizontalScl);

    scaleForLineAndPolygon(copyPoints[size - 1], this->points[0], verticalScl, horizontalScl);

    this->calculateSurroundingRectangle();
}

void Polygon::saveToFormat(std::ofstream &file) const {
    unsigned size = this->points.size();

    file << "polygon ";
    for (unsigned i = 0; i < size; i++)
        file << this->points[i].getX() << ' ' << this->points[i].getY() << ' ';
    file << this->stroke << ' ';
    file << this->fill << '\n';
}

void Polygon::saveToSvgFile(std::ofstream &file) const {
    file << "<polygon ";
    file << "points = \"";

    unsigned size = this->points.size();

    for (unsigned i = 0; i < size; i++)
        file << this->points[i].getX() << ',' << this->points[i].getY() << ' ';

    file << "\" ";

    file << "stroke = \"" << this->stroke << "\" ";
    file << "fill = \"" << this->fill << "\" ";
    file << "/>\n";
}

void Polygon::calculateSurroundingRectangle() {
    this->changeTL(getXMin(this->points.data(), this->points.size()),
                   getYMin(this->points.data(), this->points.size()));

    this->changeBR(getXMax(this->points.data(), this->points.size()),
                   getYMax(this->points.data(), this->points.size()));
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
            actualNumber += (*data - '0') / fractions;

        fractions *= (foundFractions) ? (10) : (1);
        data++;
    }
    return actualNumber * sign;
}

Element *PolygonCreator::userCreateShape(std::istream &input) const {
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

Element *PolygonCreator::formatCreateShape(std::ifstream &file) const {
    return this->userCreateShape(file);
}

std::vector<Point> findPoints(std::ifstream &file, unsigned currentIndex) {
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

        else if (symbol == '.')
            foundFractions = true;

        else if (symbol == ',') {
            counter++;
            foundFractions = false;
            coord1 *= sign;
            sign = 1;
            fractions = 1;

        } else if (symbol == '-') {
            sign *= -1;

        } else if (symbol >= '0' && symbol <= '9' && !foundFractions)
            if (counter == 0)
                coord1 = coord1 * 10 + (symbol - '0');

            else
                coord2 = coord2 * 10 + (symbol - '0');

        else if (symbol >= '0' && symbol <= '9') {
            fractions *= 10;

            if (counter == 0)
                coord1 += (symbol - '0') / fractions;

            else
                coord2 += (symbol - '0') / fractions;

        }


        if ((symbol == ' ' || symbol == '\"') && apostropheCount) {

            bool end = false;

            if (symbol == ' ') {
                unsigned currentIndex = file.tellg();

                file.get(symbol);

                if (symbol == '\"')
                    end = true;

                else file.seekg(currentIndex);
            }

            coord2 *= sign;

            points.emplace_back(coord1, coord2);
            coord1 = 0;
            coord2 = 0;
            counter = 0;
            foundFractions = false;
            fractions = 1;

            if (end)
                break;
        }

        if (symbol == '\"')
            apostropheCount++;
    }

    if (!foundEquals) {
        file.seekg(currentIndex);
        std::vector<Point> zeroPoint;
        zeroPoint.emplace_back(0, 0);
        return zeroPoint;
    }


    file.seekg(currentIndex);
    return points;
}

Element *PolygonCreator::svgCreateShape(std::ifstream &file) const {
    unsigned currentIndex = file.tellg();
    char buffer[7];

    if (findSource(buffer, "points", file)) {
        std::vector<Point> points(findPoints(file, currentIndex));
        const char *stroke = findTextAttribute(file, "stroke");
        const char *fill = findTextAttribute(file, "fill");

        Element *obj = new Polygon(points.data(), points.size(), stroke, fill);
        delete[] stroke;
        delete[] fill;

        return obj;
    }

    file.seekg(currentIndex);
    return nullptr;
}