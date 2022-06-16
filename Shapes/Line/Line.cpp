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

void Line::scale(float verticalScl, float horizontalScl) {
    scaleForLineAndPolygon(this->points[Line::FIRST], this->points[Line::SECOND], verticalScl, horizontalScl);

    bool onTop = this->points[Line::SECOND].getY() > this->points[Line::FIRST].getY();
    bool onLeft = this->points[Line::SECOND].getX() < this->points[Line::FIRST].getX();

    if (onTop && onLeft) {
        unsigned temp = Line::FIRST;
        Line::FIRST = Line::SECOND;
        Line::SECOND = temp;
    }

    this->changeTL(this->points[Line::FIRST].getX(), this->points[Line::FIRST].getY());
    this->changeBR(this->points[Line::SECOND].getX(), this->points[Line::SECOND].getY());
}


bool Line::isContained(float tlX, float tlY, float brX, float brY) const {
    bool tlXContained = (this->points[Line::FIRST].getX() >= tlX && this->points[Line::SECOND].getX() >= tlX);
    bool brXContained = (this->points[Line::FIRST].getX() <= brX && this->points[Line::SECOND].getX() <= brX);

    bool tlYContained = (this->points[Line::FIRST].getY() <= tlY && this->points[Line::SECOND].getY() <= tlY);
    bool brYContained = (this->points[Line::FIRST].getY() >= brY && this->points[Line::SECOND].getY() >= brY);

    return tlXContained && brXContained && tlYContained && brYContained;
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


Shape *LineCreator::userCreateShape(std::istream &input) const {
    float x1, y1, x2, y2;
    std::string stroke;

    input >> x1 >> y1 >> x2 >> y2 >> stroke;

    return new Line(x1, y1, x2, y2, stroke.c_str());
}

Shape *LineCreator::svgCreateShape(std::ifstream &file) const {
    float x1, y1, x2, y2;

    x1 = findNumericAttribute(file, "x1");
    y1 = findNumericAttribute(file, "y1");
    x2 = findNumericAttribute(file, "x2");
    y2 = findNumericAttribute(file, "y2");
    const char *stroke = findTextAttribute(file, "stroke");

    Shape *obj = new Line(x1, y1, x2, y2, stroke);
    delete[] stroke;

    return obj;
}
