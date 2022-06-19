#ifndef SCALABLEVECTORGRAPHICS_ELEMENT_H
#define SCALABLEVECTORGRAPHICS_ELEMENT_H
#include <fstream>

class Element {
public:
    Element() = default;

    Element(const Element& other) = delete;

    virtual void print() const = 0;

    virtual void bringForward(unsigned layers) = 0;

    virtual void sendBackwards(unsigned layers) = 0;

    virtual void translate(float verticalTrl, float horizontalTrl) = 0;

    virtual void scale(float verticalScl, float horizontalScl) = 0;

    //virtual void rotate(int angle) = 0;//for later

    virtual bool isContained(float tlX, float tlY, float brX, float brY) const = 0;

    virtual void saveToSvgFile(std::ofstream& file) const = 0;

    Element& operator=(const Element& other) = delete;

    ~Element() = default;
};


#endif //SCALABLEVECTORGRAPHICS_ELEMENT_H
