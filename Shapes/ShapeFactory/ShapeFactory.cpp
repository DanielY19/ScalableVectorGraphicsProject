#include "ShapeFactory.h"
#include "../../Shapes/Line/Line.h"
#include "../../Shapes/Circle/Circle.h"
#include "../../Shapes/Rectangle/Rectangle.h"
#include "../../Shapes/Polygon/Polygon.h"
#include <cstring>

ShapeFactory::ShapeFactory() {
    unsigned size = 0;

    try {
        this->creators[0] = new LineCreator;
        ++size;

        this->creators[1] = new CircleCreator;
        ++size;

        this->creators[2] = new RectangleCreator;
        ++size;

        this->creators[3] = new PolygonCreator;
        ++size;
    }
    catch (std::bad_alloc &) {
        this->destroy(size);
        throw;
    }
}

Element *ShapeFactory::userCreateShape(std::istream &input) const {
    std::string shapeType;
    input >> shapeType;

    for (unsigned i = 0; i < ShapeFactory::SHAPES; i++)
        if (strcmp(shapeType.c_str(), this->creators[i]->getTargetedShape()) == 0)
            return this->creators[i]->userCreateShape(input);


    return nullptr;
}

Element *ShapeFactory::formatCreateShape(std::ifstream &file) const {
    return this->userCreateShape(file);
}

Element *ShapeFactory::svgCreateShape(std::ifstream &file) const {
    std::string shapeType;
    file >> shapeType;

    for (unsigned i = 0; i < ShapeFactory::SHAPES; i++)
        if (strcmp(shapeType.c_str(), this->creators[i]->getTargetedShape()) == 0)
            return this->creators[i]->svgCreateShape(file);

    return nullptr;
}

ShapeFactory::~ShapeFactory() {
    this->destroy(ShapeFactory::SHAPES);
}

void ShapeFactory::destroy(unsigned size) {
    for (unsigned i = 0; i < size; i++)
        delete this->creators[i];
}