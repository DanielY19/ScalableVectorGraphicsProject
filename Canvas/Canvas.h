#ifndef SCALABLEVECTORGRAPHICS_CANVAS_H
#define SCALABLEVECTORGRAPHICS_CANVAS_H

#include "../Shapes/ShapeFactory/ShapeFactory.h"
#include "../Shape/Shape.h"

class Canvas {
public:
    Canvas();

    void open(const char *fileName);

    void print();

    void create();

    //group

    //bringForward

    //sendBackward

    void translate(int id, float verticalTrl, float horizontalTrl);

    void scale(int id, float verticalScl, float horizonatlScl);

    //rotate

    void save() const;

    void saveAs(const char *format) const;

    ~Canvas();

private:
    Shape **shapes;
    ShapeFactory factory;
    unsigned size;
    unsigned capacity;

    std::string currentFile;

    void resize();

    void destroy();
};


#endif //SCALABLEVECTORGRAPHICS_CANVAS_H
