#ifndef SCALABLEVECTORGRAPHICS_CANVAS_H
#define SCALABLEVECTORGRAPHICS_CANVAS_H

#include "../Shape/Shape.h"

class Canvas {
public:
    Canvas();

private:
    Shape **shapes;
    //ShapeFactory factory;
    unsigned size;
    unsigned capacity;

    void resize();

    void destroy();
};


#endif //SCALABLEVECTORGRAPHICS_CANVAS_H
