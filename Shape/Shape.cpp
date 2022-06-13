#include "Shape.h"
#include <iostream>
#include <cstring>

unsigned Shape::idGenerator = 1;

const char *checkForNullptr(const char *str) {
    if (str == nullptr)
        return "transparent";
    return str;
}

Shape::Shape(const char *stroke, const char *fill, const Point &TL, const Point &BR)
        : id(Shape::idGenerator++), stroke(checkForNullptr(stroke)), fill(checkForNullptr(fill)), TL(TL), BR(BR) {}


void Shape::print() const {
    unsigned size = this->points.size();

    for (unsigned i = 0; i < size; i++)
        this->points[i].print();
}

void Shape::bringForward(unsigned int layers) {
    if (layers + this->id > idGenerator) {
        std::cerr << "Cannot move shape,because it will go out of bounds!";
        return;
    }

    this->id += layers;
}

void Shape::sendBackwards(unsigned int layers) {
    if (layers >= this->id) {
        std::cerr << "Cannot move shape,because it will go out of bounds!";
        return;
    }

    this->id -= layers;
}

void Shape::translate(float verticalTrl, float horizontalTrl) {
    unsigned size = this->points.size();

    for (unsigned i = 0; i < size; i++)
        this->points[i].translate(verticalTrl, horizontalTrl);
}

bool Shape::isContained(float tlX, float tlY, float brX, float brY) const {
    bool first = (this->getTL().getX() >= tlX) && (this->getTL().getY() <= tlY);

    bool second = (this->getBR().getX() <= brX) &&
                  (this->getBR().getY() >= brY);

    return first && second;
}


unsigned Shape::getID() const {
    return this->id;
}

Point Shape::getCenterOfSurroundingRect() const {
    return Point((this->TL.getX() + this->BR.getX()) / 2, (this->TL.getY() + this->BR.getY()) / 2);
}

void Shape::changeTL(float x, float y) {
    this->TL.change(x, y);
}

void Shape::changeBR(float x, float y) {
    this->BR.change(x, y);
}

const Point &Shape::getTL() const {
    return this->TL;
}

const Point &Shape::getBR() const {
    return this->BR;
}

ShapeCreator::ShapeCreator(const char *targetedShape)
        : shape(targetedShape) {}

const char *ShapeCreator::getTargetedShape() const {
    return this->shape.c_str();
}

void scaleForLineAndPolygon(const Point &first, Point &second, float verticalScl, float horizontalScl) {
    float distanceY = first.getY() - second.getY();
    float distanceX = first.getX() - second.getX();

    if (distanceX < 0)
        distanceX *= -1;

    if (distanceY < 0)
        distanceY *= -1;

    distanceY *= verticalScl;
    distanceX *= horizontalScl;

    second.change(first.getX() + distanceX,
                  first.getY() + distanceY);
}

float findNumericAttribute(std::ifstream &file, const char *searchedAttribute) {
    unsigned currentIndex = file.tellg();
    char buffer[7];


    if (findSource(buffer, searchedAttribute, file)) {
        return parseToNumber(file, currentIndex);
    }

    file.seekg(currentIndex);
    return 0;
}

const char *findTextAttribute(std::ifstream &file, const char *searchedAttribute) {
    unsigned currentIndex = file.tellg();
    char buffer[7];

    if (findSource(buffer, searchedAttribute, file)) {
        return parseToText(file, currentIndex);
    }

    file.seekg(currentIndex);
    return nullptr;
}

bool findSource(char *buffer, const char *source, std::ifstream &file) {
    char symbol = 0;
    unsigned size = 0;

    unsigned maxSize = strlen(source);

    while (file.get(symbol) && symbol != '>') {
        if (symbol == *source && size < maxSize) {
            buffer[size++] = symbol;
            source++;
        } else if (size == maxSize) {
            buffer[size] = '\0';
            source -= size;
            break;
        } else {
            source -= size;
            size = 0;
        }
    }

    return strcmp(buffer, source) == 0;
}


float parseToNumber(std::ifstream &file, unsigned currentIndex) {
    char digit = 0;

    unsigned apostropheCount = 0;
    bool foundEquals = false;

    float actualNumber = 0;
    float fractions = 1;
    bool foundFractions = false;

    while (file.get(digit) && apostropheCount != 2 && digit != '>') {
        if (digit == '=')
            foundEquals = true;
        else if (digit == '\"')
            apostropheCount++;
        else if (digit == '.')
            foundFractions = true;
        else if (digit >= '0' && digit <= '9' && !foundFractions)
            actualNumber = actualNumber * 10 + (digit - '0');
        else if (digit >= '0' && digit <= '9')
            actualNumber += (digit - '0') / fractions;

        fractions *= (foundFractions) ? (10) : (1);
    }

    if (!foundEquals) {
        file.seekg(currentIndex);
        return 0;
    }

    file.seekg(currentIndex);
    return actualNumber;
}

const char *parseToText(std::ifstream &file, unsigned currentIndex) {
    char symbol = 0;
    unsigned apostropheCount = 0;
    bool foundEquals = false;
    std::string text;

    while (file.get(symbol) && apostropheCount != 2 && symbol != '>') {
        if (symbol == '=')
            foundEquals = true;
        else if (symbol == '\"')
            apostropheCount++;
        else if ((symbol >= 'a' && symbol <= 'z') || (symbol >= 'A' && symbol <= 'Z'))
            text.push_back(symbol);
    }

    if (!foundEquals) {
        file.seekg(currentIndex);
        return nullptr;
    }

    file.seekg(currentIndex);
    return strcpy(new char[text.size() + 1], text.c_str());
}