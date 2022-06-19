#ifndef SCALABLEVECTORGRAPHICS_ELEMENT_H
#define SCALABLEVECTORGRAPHICS_ELEMENT_H

#include "../Shape/Point/Point.h"
#include <fstream>
#include <vector>

class Element {
public:
    Element(const Point &TL, const Point &BR);

    Element(const Element &other) = delete;

    virtual void print() const = 0;

    void bringForward(unsigned layers);

    void sendBackwards(unsigned layers) ;

    virtual void translate(float verticalTrl, float horizontalTrl) = 0;

    virtual void scale(float verticalScl, float horizontalScl) = 0;

    //virtual void rotate(int angle) = 0;//for later

    bool isContained(float tlX, float tlY, float brX, float brY) const;

    virtual void saveToSvgFile(std::ofstream &file) const = 0;

    unsigned getID() const;

    Element &operator=(const Element &other) = delete;

    virtual ~Element() = default;

    Point getCenterOfSurroundingRect() const;

    void changeTL(float x, float y);

    void changeBR(float x, float y);

    const Point &getTL() const;

    const Point &getBR() const;

    virtual std::vector<Element *> ungroup();

protected:
    unsigned id;

    static unsigned idGenerator;
private:
    Point TL;
    Point BR;
};


#endif //SCALABLEVECTORGRAPHICS_ELEMENT_H
