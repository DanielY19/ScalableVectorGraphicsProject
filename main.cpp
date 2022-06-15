#include <iostream>
#include "Canvas/Canvas.h"

int main() {
    Canvas can;

    can.openSvg("test.txt");
    can.print();
    can.save();


    return 0;
}
