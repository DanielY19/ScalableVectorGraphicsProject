#include "Line.h"
#include <iostream>


Line::Line(float x1, float y1, float x2, float y2, const char *stroke)
        : Shape(stroke, stroke, Point(x1, y1), Point(x2, y2)), first(0), second(1) {
    this->points.push_back(this->getTL());
    this->points.push_back(this->getBR());
}

void Line::print() const {
    std::cout << "line ";
    this->Shape::print();
    std::cout << this->stroke << "\n\n";
}

void Line::translate(float verticalTrl, float horizontalTrl) {
    this->points[this->first].translate(verticalTrl, horizontalTrl);
    this->points[this->second].translate(verticalTrl, horizontalTrl);
    this->changeSurroundingRectangle(this->points[this->first], this->points[this->second]);
}

void Line::scale(float verticalScl, float horizontalScl) {
    scaleForLineAndPolygon(this->points[this->first], this->points[this->second], verticalScl, horizontalScl);


    if (this->points[this->second] <= this->points[this->first]) {
        unsigned temp = this->first;
        this->first = this->second;
        this->second = temp;
    }

    this->changeSurroundingRectangle(this->points[this->first], this->points[this->second]);
}

void Line::saveToFormat(std::ofstream &file) const {
    file << "line ";
    file << this->points[this->first].getX() << ' ';
    file << this->points[this->first].getY() << ' ';
    file << this->points[this->second].getX() << ' ';
    file << this->points[this->second].getY() << ' ';
    file << this->stroke << '\n';
}

void Line::saveToSvgFile(std::ofstream &file) const {
    file << "<line ";
    file << "x1 = \"" << this->points[this->first].getX() << "\" ";
    file << "y1 = \"" << this->points[this->first].getY() << "\" ";
    file << "x2 = \"" << this->points[this->second].getX() << "\" ";
    file << "y2 = \"" << this->points[this->second].getY() << "\" ";
    file << "stroke = \"" << this->stroke << "\" ";
    file << "/>\n";
}


Element *LineCreator::userCreateShape(std::istream &input) const {
    float x1, y1, x2, y2;
    std::string stroke;

    input >> x1 >> y1 >> x2 >> y2 >> stroke;

    return new Line(x1, y1, x2, y2, stroke.c_str());
}

Element *LineCreator::formatCreateShape(std::ifstream &file) const {
    return this->userCreateShape(file);
}

Element *LineCreator::svgCreateShape(std::ifstream &file) const {
    float x1, y1, x2, y2;

    x1 = findNumericAttribute(file, "x1");
    y1 = findNumericAttribute(file, "y1");
    x2 = findNumericAttribute(file, "x2");
    y2 = findNumericAttribute(file, "y2");
    const char *stroke = findTextAttribute(file, "stroke");

    Element *obj = new Line(x1, y1, x2, y2, stroke);
    delete[] stroke;

    return obj;
}
