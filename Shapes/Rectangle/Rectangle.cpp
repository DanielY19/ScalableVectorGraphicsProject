#include "Rectangle.h"
#include <iostream>
#include <stdexcept>


Rectangle::Rectangle(float x, float y, float width, float height, const char *stroke, const char *fill)
        : Shape(stroke, fill, Point(x, y), Point(x + width, y + height)), width(width), height(height),topLeft(0),bottomRight(1) {
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
    this->points[this->topLeft].translate(verticalTrl, horizontalTrl);
    this->points[this->bottomRight].translate(verticalTrl, horizontalTrl);
    this->changeSurroundingRectangle(this->points[this->topLeft], this->points[this->bottomRight]);
}

void Rectangle::scale(float verticalScl, float horizontalScl) {
    this->height *= verticalScl;
    this->width *= horizontalScl;
    this->points[this->bottomRight].change(this->points[this->topLeft].getX() + width,
                                           this->points[this->topLeft].getY() + height);

    if (this->height < 0)
        this->height *= -1;

    if (this->width < 0)
        this->width *= -1;


    if (this->points[this->bottomRight] <= this->points[this->topLeft]) {
        unsigned temp = this->topLeft;
        this->topLeft = this->bottomRight;
        this->bottomRight = temp;
    }

    this->changeSurroundingRectangle(this->points[this->topLeft], this->points[this->bottomRight]);
}

void Rectangle::saveToFormat(std::ofstream &file) const {
    file << "rect ";
    file << this->points[this->topLeft].getX() << ' ';
    file << this->points[this->topLeft].getY() << ' ';
    file << this->width << ' ';
    file << this->height << ' ';
    file << this->stroke << ' ';
    file << this->fill << '\n';
}

void Rectangle::saveToSvgFile(std::ofstream &file) const {
    file << "<rect ";
    file << "x = \"" << this->points[this->topLeft].getX() << "\" ";
    file << "y = \"" << this->points[this->topLeft].getY() << "\" ";
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


