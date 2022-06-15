#ifndef SCALABLEVECTORGRAPHICS_SHAPEFACTORY_H
#define SCALABLEVECTORGRAPHICS_SHAPEFACTORY_H

#include "../../Shape/Shape.h"

class ShapeFactory {
public:
    ShapeFactory();

    Shape *userCreateShape(std::istream& input) const;

    Shape *svgCreateShape(std::ifstream& file) const;

    ~ShapeFactory();
private:
    static const unsigned SHAPES = 4;
    ShapeCreator *creators[ShapeFactory::SHAPES];

    void destroy();

};


#endif //SCALABLEVECTORGRAPHICS_SHAPEFACTORY_H
