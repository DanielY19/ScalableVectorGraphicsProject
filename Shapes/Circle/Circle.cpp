#include "Circle.h"
#include <stdexcept>
#include <iostream>

Circle::Circle(float x, float y, float radius, const char *stroke, const char *fill)
        : Shape(stroke, fill, Point(x - radius, y + radius), Point(x + radius, y - radius)), radius(radius) {
    if (radius < 0)
        throw std::invalid_argument("Radius cannot be negative!");

    //emplace back constructs the object and passes it to the vector
    this->points.emplace_back(x, y);
}

void Circle::print() const {
    std::cout << "circle r:" << this->radius << ' ';
    this->Shape::print();
    std::cout << this->stroke << ' ' << this->fill << "\n\n";
}

void Circle::translate(float verticalTrl, float horizontalTrl) {
    this->points[Circle::CENTER].translate(verticalTrl, horizontalTrl);
    this->calculateSurroundingRectangle();
}

void Circle::scale(float verticalScl, float horizontalScl) {
    if (verticalScl < 0)
        throw std::invalid_argument("Radius cannot be scaled negatively!");

    this->radius *= verticalScl;

    this->calculateSurroundingRectangle();
}

void Circle::saveToSvgFile(std::ofstream &file) const {
    file << "<circle ";
    file << "cx = \"" << this->points[Circle::CENTER].getX() << "\" ";
    file << "cy = \"" << this->points[Circle::CENTER].getY() << "\" ";
    file << "r = \"" << this->radius << "\" ";
    file << "stroke = \"" << this->stroke << "\" ";
    file << "fill = \"" << this->fill << "\" ";
    file << "/>\n";
}

void Circle::calculateSurroundingRectangle() {
    this->changeTL(this->points[Circle::CENTER].getX() - this->radius,
                   this->points[Circle::CENTER].getY() + this->radius);

    this->changeBR(this->points[Circle::CENTER].getX() + this->radius,
                   this->points[Circle::CENTER].getY() - this->radius);
}

Element *CircleCreator::userCreateShape(std::istream &input) const {
    float cx, cy, radius;
    std::string stroke, fill;

    input >> cx >> cy >> radius >> stroke >> fill;

    return new Circle(cx, cy, radius, stroke.c_str(), fill.c_str());
}

Element *CircleCreator::svgCreateShape(std::ifstream &file) const {
    float cx, cy, radius;

    cx = findNumericAttribute(file, "cx");
    cy = findNumericAttribute(file, "cy");
    radius = findNumericAttribute(file, "r");
    const char *stroke = findTextAttribute(file, "stroke");
    const char *fill = findTextAttribute(file, "fill");

    Element *obj = new Circle(cx, cy, radius, stroke, fill);
    delete[] stroke, fill;

    return obj;
}

