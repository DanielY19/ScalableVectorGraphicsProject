#include "Shape.h"
#include <iostream>
#include <cstring>

unsigned Shape::shapeIDGenerator = 1;

const char *checkForNullptr(const char *str) {
    if (str == nullptr)
        return "transparent";
    return str;
}

Shape::Shape(const char *stroke, const char *fill, const Point &TL, const Point &BR)
        : Element(TL, BR, Shape::shapeIDGenerator++), stroke(checkForNullptr(stroke)), fill(checkForNullptr(fill)) {}


void Shape::print() const {
    unsigned size = this->points.size();

    for (unsigned i = 0; i < size; i++)
        this->points[i].print();
}

void Shape::bringForward(unsigned int layers) {
    if (layers + this->id > Shape::shapeIDGenerator) {
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

unsigned int Shape::getID() const {
    return this->id;
}


ShapeCreator::ShapeCreator(const char *targetedShape)
        : shape(targetedShape) {}

const char *ShapeCreator::getTargetedShape() const {
    return this->shape.c_str();
}

void scaleForLineAndPolygon(const Point &first, Point &second, float verticalScl, float horizontalScl) {
    float distanceY = second.getY() - first.getY();
    float distanceX = second.getX() - first.getX();

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
    unsigned currentIndex = file.tellg();

    unsigned maxSize = strlen(source);

    while (file.get(symbol) && symbol != '>') {
        if (symbol == *source && size < maxSize) {
            buffer[size++] = symbol;
            source++;
            currentIndex = file.tellg();
        } else if (size == maxSize) {
            buffer[size] = '\0';
            source -= size;
            file.seekg(currentIndex);
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
    int sign = 1;

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
        else if (digit == '-')
            sign *= -1;

        fractions *= (foundFractions) ? (10) : (1);
    }

    if (!foundEquals) {
        file.seekg(currentIndex);
        return 0;
    }

    file.seekg(currentIndex);
    return actualNumber * sign;
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
        else if (apostropheCount && (symbol >= 'a' && symbol <= 'z') || (symbol >= 'A' && symbol <= 'Z'))
            text.push_back(symbol);
    }

    if (!foundEquals) {
        file.seekg(currentIndex);
        return nullptr;
    }

    file.seekg(currentIndex);
    return strcpy(new char[text.size() + 1], text.c_str());
}