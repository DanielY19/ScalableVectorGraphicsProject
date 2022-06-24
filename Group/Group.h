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

    void saveToFormat(std::ofstream &file) const override;

    void saveToSvgFile(std::ofstream &file) const override;

    std::vector<Element *> ungroup() override;

    ~Group() override;

private:
    std::vector<Element*> elements;
    unsigned size;

    void destroy();
};


#endif //SCALABLEVECTORGRAPHICS_GROUP_H
