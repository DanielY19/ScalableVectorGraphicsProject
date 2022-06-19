#ifndef SCALABLEVECTORGRAPHICS_CANVAS_H
#define SCALABLEVECTORGRAPHICS_CANVAS_H

#include "../Shapes/ShapeFactory/ShapeFactory.h"
#include "../Group/Group.h"

class Canvas {
public:
    Canvas();

    Canvas(const Canvas &other) = delete;

    void openSvg(const char *fileName);

    void print();

    void create(std::istream &input);

    void group(float tlX, float tlY, float brX, float brY);

    void ungroup(unsigned id);

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
    Element **elements;
    ShapeFactory factory;
    unsigned size;
    unsigned capacity;

    std::string currentFile;

    void addElement(Element *element);

    void moveBack(Element *element, unsigned pos);

    void moveFront(Element *element, unsigned pos);

    void shiftBack(unsigned index);

    void allocateMem();

    void resize();

    void destroy();
};


#endif //SCALABLEVECTORGRAPHICS_CANVAS_H
