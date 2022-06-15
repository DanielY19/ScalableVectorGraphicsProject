#include <iostream>
#include "Canvas/Canvas.h"

int main() {
    Canvas can;

    can.create();
    can.create();
    can.create();

    can.bringForward(1,2);
    can.translate(3,10,10);
    can.scale(3,2,2);

    can.print();



    return 0;
}
