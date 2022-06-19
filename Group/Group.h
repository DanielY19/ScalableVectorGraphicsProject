#ifndef SCALABLEVECTORGRAPHICS_GROUP_H
#define SCALABLEVECTORGRAPHICS_GROUP_H
#include "../Shape/Shape.h"

class Group : public Element {
public:
    Group();

    void addElement(Element *element);

    void print() const override;

    void translate(float verticalTrl, float horizontalTrl) override;

    void scale(float verticalScl, float horizontalScl) override;

    //void rotate(int angle) override;//for later

    void saveToSvgFile(std::ofstream &file) const override;

    unsigned getSize() const;

    Element* giveElement(unsigned index);

    ~Group() override;

private:
    Element **elements;
    unsigned size;
    unsigned capacity;

    void allocateMem();

    void resize();

    void destroy();

private:
    Point TL;
    Point BR;

};


#endif //SCALABLEVECTORGRAPHICS_GROUP_H
