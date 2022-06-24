#include "Rectangle.h"
#include <iostream>
#include <stdexcept>

unsigned Rectangle::TOPLEFT = 0;
unsigned Rectangle::BOTTOMRIGHT = 1;

Rectangle::Rectangle(float x, float y, float width, float height, const char *stroke, const char *fill)
        : Shape(stroke, fill, Point(x, y), Point(x + width, y + height)), width(width), height(height) {
    if (width < 0 || height < 0)
        throw std::invalid_argument("Height or width cannot be negative!");

    this->points.push_back(this->getTL());
    this->points.push_back(this->getBR());
}

void Rectangle::print() const {
    std::cout << "rectangle w:" << width << " h:" << this->height << ' ';
    this->Shape::print();
    std::cout << this->stroke << ' ' << this->fill << "\n\n";
}

void Rectangle::translate(float verticalTrl, float horizontalTrl) {
    this->points[Rectangle::TOPLEFT].translate(verticalTrl, horizontalTrl);
    this->points[Rectangle::BOTTOMRIGHT].translate(verticalTrl, horizontalTrl);
    this->changeSurroundingRectangle(this->points[Rectangle::TOPLEFT], this->points[Rectangle::BOTTOMRIGHT]);
}

void Rectangle::scale(float verticalScl, float horizontalScl) {
    this->height *= verticalScl;
    this->width *= horizontalScl;
    this->points[Rectangle::BOTTOMRIGHT].change(this->points[Rectangle::TOPLEFT].getX() + width,
                                                this->points[Rectangle::TOPLEFT].getY() + height);

    if (this->height < 0)
        this->height *= -1;

    if (this->width < 0)
        this->width *= -1;


    if (this->points[Rectangle::BOTTOMRIGHT] <= this->points[Rectangle::TOPLEFT]) {
        unsigned temp = Rectangle::TOPLEFT;
        Rectangle::TOPLEFT = Rectangle::BOTTOMRIGHT;
        Rectangle::BOTTOMRIGHT = temp;
    }

    this->changeSurroundingRectangle(this->points[Rectangle::TOPLEFT], this->points[Rectangle::BOTTOMRIGHT]);
}

void Rectangle::saveToFormat(std::ofstream &file) const {
    file << "rect ";
    file << this->points[Rectangle::TOPLEFT].getX() << ' ';
    file << this->points[Rectangle::TOPLEFT].getY() << ' ';
    file << this->width << ' ';
    file << this->height << ' ';
    file << this->stroke << ' ';
    file << this->fill << '\n';
}

void Rectangle::saveToSvgFile(std::ofstream &file) const {
    file << "<rect ";
    file << "x = \"" << this->points[Rectangle::TOPLEFT].getX() << "\" ";
    file << "y = \"" << this->points[Rectangle::TOPLEFT].getY() << "\" ";
    file << "width = \"" << this->width << "\" ";
    file << "height = \"" << this->height << "\" ";
    file << "stroke = \"" << this->stroke << "\" ";
    file << "fill = \"" << this->fill << "\" ";
    file << "/>\n";
}

Element *RectangleCreator::userCreateShape(std::istream &input) const {
    float x, y, width, height;
    std::string stroke, fill;

    input >> x >> y >> width >> height >> stroke >> fill;

    return new Rectangle(x, y, width, height, stroke.c_str(), fill.c_str());
}

Element *RectangleCreator::formatCreateShape(std::ifstream &file) const {
    return this->userCreateShape(file);
}

Element *RectangleCreator::svgCreateShape(std::ifstream &file) const {
    float x, y, width, height;

    x = findNumericAttribute(file, "x");
    y = findNumericAttribute(file, "y");
    width = findNumericAttribute(file, "width");
    height = findNumericAttribute(file, "height");
    const char *stroke = findTextAttribute(file, "stroke");
    const char *fill = findTextAttribute(file, "fill");

    Element *obj = new Rectangle(x, y, width, height, stroke, fill);
    delete[] stroke;
    delete[] fill;

    return obj;
}


