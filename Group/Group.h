#ifndef SCALABLEVECTORGRAPHICS_GROUP_H
#define SCALABLEVECTORGRAPHICS_GROUP_H
#include "../Shape/Shape.h"

class Group : public Element {
public:
    Group();

    void addElement(Element *element);

    void print() const override;

    void bringForward(unsigned layers) override;

    void sendBackwards(unsigned layers) override;

    void translate(float verticalTrl, float horizontalTrl) override;

    void scale(float verticalScl, float horizontalScl) override;

    //virtual void rotate(int angle) = 0;//for later

    void saveToSvgFile(std::ofstream &file) const override;

    unsigned getID() const override;

    ~Group() override;

private:
    Element **shapes;
    unsigned size;
    unsigned capacity;

    void allocateMem();

    void resize();

    void destroy();

private:
    Point TL;
    Point BR;

    static unsigned groupIDGenerator;
};


#endif //SCALABLEVECTORGRAPHICS_GROUP_H
