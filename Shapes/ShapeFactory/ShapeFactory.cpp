#include "ShapeFactory.h"
#include "../../Shapes/Line/Line.h"
#include "../../Shapes/Circle/Circle.h"
#include "../../Shapes/Rectangle/Rectangle.h"
#include "../../Shapes/Polygon/Polygon.h"
#include <cstring>

ShapeFactory::ShapeFactory() {
    try {
        this->creators[0] = new LineCreator;
        this->creators[1] = new CircleCreator;
        this->creators[2] = new RectangleCreator;
        this->creators[3] = new PolygonCreator;
    }
    catch (std::bad_alloc &) {
        this->destroy();
    }
}

Shape *ShapeFactory::userCreateShape(std::istream &input) const {
    std::string shapeType;
    input >> shapeType;

    for (unsigned i = 0; i < ShapeFactory::SHAPES; i++)
        if (strcmp(shapeType.c_str(), this->creators[i]->getTargetedShape()) == 0)
            return this->creators[i]->userCreateShape(input);

    return nullptr;
}

Shape *ShapeFactory::svgCreateShape(const char *fileName) const {
    std::ifstream file(fileName);

    if (!file.is_open())
        return nullptr;

    return nullptr;
}

ShapeFactory::~ShapeFactory() {
    this->destroy();
}

void ShapeFactory::destroy() {
    for (unsigned i = 0; i < ShapeFactory::SHAPES; i++)
        delete this->creators[i];
}