#include "Interface.h"
#include <iostream>
#include <cstring>

void Interface::commandLine() {
    std::string command("default");

    while (true) {
        std::cout << '>';
        std::cin >> command;


        if (strcmp(command.c_str(), "open") == 0) {
            std::string file;
            std::cin >> file;
            this->image.openSvg(file.c_str());
        }

        else if (strcmp(command.c_str(), "print") == 0)
            this->image.print();


        else if (strcmp(command.c_str(), "create") == 0)
            this->image.create(std::cin);


        else if (strcmp(command.c_str(), "bringForward") == 0) {
            unsigned id = 0;
            unsigned layers = 0;
            std::cin >> id >> layers;
            this->image.bringForward(id, layers);
        }

        else if (strcmp(command.c_str(), "sendBackward") == 0) {
            unsigned id = 0;
            unsigned layers = 0;
            std::cin >> id >> layers;
            this->image.sendBackwards(id, layers);
        }

        else if (strcmp(command.c_str(), "translate") == 0) {
            int id = -1;
            float verticalTrl, horizontalTrl;
            std::cin >> id >> verticalTrl >> horizontalTrl;
            this->image.translate(id, verticalTrl, horizontalTrl);
        }

        else if(strcmp(command.c_str(), "scale") == 0){
            int id = -1;
            float verticalScl, horizontalScl;
            std::cin >> id >> verticalScl >> horizontalScl;
            this->image.scale(id, verticalScl, horizontalScl);
        }

        else if(strcmp(command.c_str(), "save") == 0){
            this->image.save();
            break;
        }

        else if(strcmp(command.c_str(), "saveAs") == 0){
            this->image.saveSvg();
            break;
        }

        std::cout << "\n\n";
    }
}