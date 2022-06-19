#ifndef SCALABLEVECTORGRAPHICS_ELEMENT_H
#define SCALABLEVECTORGRAPHICS_ELEMENT_H

#include "../Shape/Point/Point.h"
#include <fstream>

class Element {
public:
    Element(const Point &TL, const Point &BR,unsigned id);

    Element(const Element &other) = delete;

    virtual void print() const = 0;

    virtual void bringForward(unsigned layers) = 0;

    virtual void sendBackwards(unsigned layers) = 0;

    virtual void translate(float verticalTrl, float horizontalTrl) = 0;

    virtual void scale(float verticalScl, float horizontalScl) = 0;

    //virtual void rotate(int angle) = 0;//for later

    virtual bool isContained(float tlX, float tlY, float brX, float brY) const;

    virtual void saveToSvgFile(std::ofstream &file) const = 0;

    virtual unsigned getID() const = 0;

    Element &operator=(const Element &other) = delete;

    virtual ~Element() = default;

    Point getCenterOfSurroundingRect() const;

    void changeTL(float x, float y);

    void changeBR(float x, float y);

    const Point &getTL() const;

    const Point &getBR() const;

protected:
    unsigned id;
private:
    Point TL;
    Point BR;
};


#endif //SCALABLEVECTORGRAPHICS_ELEMENT_H
