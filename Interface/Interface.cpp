#include "Interface.h"
#include <iostream>
#include <cstring>

void Interface::commandLine() {
    std::string command("default");

    while (true) {
        std::cout << '>';
        std::cin >> command;

        if(strcmp(command.c_str(), "openFormat") == 0){
            std::string file;
            std::cin >> file;
            this->image.openFormat(file.c_str());
        }

        else if (strcmp(command.c_str(), "openSvg") == 0) {
            std::string file;
            std::cin >> file;
            this->image.openSvg(file.c_str());
        }

        else if (strcmp(command.c_str(), "print") == 0)
            this->image.print();


        else if (strcmp(command.c_str(), "create") == 0)
            this->image.create(std::cin);

        else if(strcmp(command.c_str(),"group")==0){
            float tlX,tlY,brX,brY;
            std::cin>>tlX>>tlY>>brX>>brY;
            this->image.group(tlX,tlY,brX,brY);
        }

        else if(strcmp(command.c_str(),"ungroup")==0){
            unsigned id;
            std::cin>>id;
            this->image.ungroup(id);
        }

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
        }

        else if(strcmp(command.c_str(), "saveAs") == 0){
            this->image.saveSvg();
        }

        else if(strcmp(command.c_str(),"help")==0){
            std::cout << "open <file_name> = opens a file with the given file name!\n";
            std::cout << "print = prints the current shapes in the image!\n";
            std::cout << "create <shape_type> <required parameters> = creates the given figure with the parameters!\n";
            std::cout << "group <point_TL> <point_BR> = groups shapes that are within the given area!\n";
            std::cout << "ungroup <id> = ungroups the given element at id!\n";
            std::cout << "bringForward <id> <layers> = brings the given element <layers> layers forward!\n";
            std::cout << "sendBackward <id> <layers> = sends the given element <layers> layers backward!\n";
            std::cout << "translate <id> <verticalTranslate> <horizontalTranslate> = translates the element with vertTrl and horzTrl!\n";
            std::cout << "scale <id> <verticalScale> <horizontalScale> = scales the element with vertScl and horzScl!\n";
            std::cout << "save = saves the changes in the current file that is opened!\n";
            std::cout << "saveAs = saves the changes as an svg file!\n\n";

        }

        else if(strcmp(command.c_str(),"exit")==0){
            return;
        }
        
        std::cout << "\n\n";
    }
}