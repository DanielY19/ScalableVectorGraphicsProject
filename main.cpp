#include <iostream>
#include "Canvas/Canvas.h"

int main() {
    Canvas can;

    can.openSvg("test.txt");
    can.translate(4, 200, 200);
    can.scale(1, 1.5,1.5);
    //can.bringForward(3, 2);
    //can.scale(5, 0.5, 1.5);
    //can.translate(-1, 200, 200);
    //can.bringForward(1, 4);
    //can.scale(5, 0.5, 1.5);

    can.print();

    can.saveSvg("test1.html");



    return 0;
}
