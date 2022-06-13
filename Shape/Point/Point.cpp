#include "Point.h"
#include <iostream>


Point::Point()
        : Point(0, 0) {}

Point::Point(float x, float y)
        : x(x), y(y) {}

void Point::setX(float x) {
    this->x = x;
}

void Point::setY(float y) {
    this->y = y;
}

float Point::getX() const {
    return this->x;
}

float Point::getY() const {
    return this->y;
}

void Point::print() const {
    std::cout << this->x << ' ' << this->y << ' ';
}

void Point::translate(float verticalTrl, float horizontalTrl) {
    this->y += verticalTrl;
    this->x += horizontalTrl;
}

/*
void Point::scale(float verticalScl, float horizontalScl) {
    this->y *= verticalScl;
    this->x *= horizontalScl;
}
*/

void Point::change(float x, float y) {
    this->setX(x);
    this->setY(y);
}
