#include "Element.h"
#include <iostream>

unsigned Element::idGenerator = 1;

Element::Element(const Point &TL, const Point &BR)
        : TL(TL), BR(BR), id(Element::idGenerator++) {}

void Element::bringForward(unsigned int layers) {
    if (layers + this->id > Element::idGenerator) {
        std::cerr << "Cannot move shape,because it will go out of bounds!";
        return;
    }

    this->id += layers;
}

void Element::sendBackwards(unsigned int layers) {
    if (layers >= this->id) {
        std::cerr << "Cannot move shape,because it will go out of bounds!";
        return;
    }

    this->id -= layers;
}


bool Element::isContained(float tlX, float tlY, float brX, float brY) const {
    bool first = (this->getTL().getX() >= tlX) && (this->getTL().getY() >= tlY);

    bool second = (this->getBR().getX() <= brX) &&
                  (this->getBR().getY() <= brY);

    return first && second;
}

unsigned int Element::getID() const {
    return this->id;
}

Point Element::getCenterOfSurroundingRect() const {
    return Point((this->TL.getX() + this->BR.getX()) / 2, (this->TL.getY() + this->BR.getY()) / 2);
}

void Element::changeTL(float x, float y) {
    this->TL.change(x, y);
}

void Element::changeBR(float x, float y) {
    this->BR.change(x, y);
}

const Point &Element::getTL() const {
    return this->TL;
}

const Point &Element::getBR() const {
    return this->BR;
}