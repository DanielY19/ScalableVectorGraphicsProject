#include "Line.h"
#include <iostream>

unsigned Line::FIRST = 0;
unsigned Line::SECOND = 1;

Line::Line(float x1, float y1, float x2, float y2, const char *stroke)
        : Shape(stroke, stroke, Point(x1, y1), Point(x2, y2)) {
    this->points.push_back(this->getTL());
    this->points.push_back(this->getBR());
}

void Line::print() const {
    std::cout << "line ";
    this->Shape::print();
    std::cout << this->stroke << "\n\n";
}

void Line::translate(float verticalTrl, float horizontalTrl) {
    this->points[Line::FIRST].translate(verticalTrl,horizontalTrl);
    this->points[Line::SECOND].translate(verticalTrl,horizontalTrl);
    this->changeSurroundingRectangle(this->points[Line::FIRST], this->points[Line::SECOND]);
}

void Line::scale(float verticalScl, float horizontalScl) {
    scaleForLineAndPolygon(this->points[Line::FIRST], this->points[Line::SECOND], verticalScl, horizontalScl);


    if (this->points[Line::SECOND] <= this->points[Line::FIRST]) {
        unsigned temp = Line::FIRST;
        Line::FIRST = Line::SECOND;
        Line::SECOND = temp;
    }

    this->changeSurroundingRectangle(this->points[Line::FIRST], this->points[Line::SECOND]);
}


void Line::saveToSvgFile(std::ofstream &file) const {
    file << "<line ";
    file << "x1 = \"" << this->points[Line::FIRST].getX() << "\" ";
    file << "y1 = \"" << this->points[Line::FIRST].getY() << "\" ";
    file << "x2 = \"" << this->points[Line::SECOND].getX() << "\" ";
    file << "y2 = \"" << this->points[Line::SECOND].getY() << "\" ";
    file << "stroke = \"" << this->stroke << "\" ";
    file << "/>\n";
}


Element *LineCreator::userCreateShape(std::istream &input) const {
    float x1, y1, x2, y2;
    std::string stroke;

    input >> x1 >> y1 >> x2 >> y2 >> stroke;

    return new Line(x1, y1, x2, y2, stroke.c_str());
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
