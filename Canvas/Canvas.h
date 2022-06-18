#ifndef SCALABLEVECTORGRAPHICS_CANVAS_H
#define SCALABLEVECTORGRAPHICS_CANVAS_H

#include "../Shapes/ShapeFactory/ShapeFactory.h"
#include "../Shape/Shape.h"

class Canvas {
public:
    Canvas();

    Canvas(const Canvas &other) = delete;

    void openSvg(const char *fileName);

    void print();

    void create(std::istream &input);

    //group

    void bringForward(unsigned id, unsigned n);

    void sendBackwards(unsigned id, unsigned n);

    void translate(int id, float verticalTrl, float horizontalTrl);

    void scale(int id, float verticalScl, float horizontalScl);

    //rotate

    Canvas &operator=(const Canvas &other) = delete;

    void save();

    void saveSvg() const;

    ~Canvas();

private:
    Shape **shapes;
    ShapeFactory factory;
    unsigned size;
    unsigned capacity;

    std::string currentFile;

    void addElement(Shape *element);

    void moveBack(Shape *element, unsigned pos);

    void moveFront(Shape *element, unsigned pos);

    void allocateMem();

    void resize();

    void destroy();
};


#endif //SCALABLEVECTORGRAPHICS_CANVAS_H
