#ifndef SCALABLEVECTORGRAPHICS_SHAPEFACTORY_H
#define SCALABLEVECTORGRAPHICS_SHAPEFACTORY_H

#include "../../Shape/Shape.h"

class ShapeFactory {
public:
    ShapeFactory();

    ShapeFactory(const ShapeFactory& other) = delete;

    Element *userCreateShape(std::istream& input) const;

    Element *svgCreateShape(std::ifstream& file) const;

    ShapeFactory& operator=(const ShapeFactory& other) = delete;

    ~ShapeFactory();
private:
    static const unsigned SHAPES = 4;
    ShapeCreator *creators[ShapeFactory::SHAPES];

    void destroy(unsigned size);

};


#endif //SCALABLEVECTORGRAPHICS_SHAPEFACTORY_H
