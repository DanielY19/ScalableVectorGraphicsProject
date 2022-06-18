#ifndef SCALABLEVECTORGRAPHICS_INTERFACE_H
#define SCALABLEVECTORGRAPHICS_INTERFACE_H

#include "../Canvas/Canvas.h"

class Interface {
public:
    Interface() = default;

    void commandLine();

    ~Interface() = default;

private:
    Canvas image;
};


#endif //SCALABLEVECTORGRAPHICS_INTERFACE_H
