#include "Canvas.h"
#include <iostream>
#include <cstring>

Canvas::Canvas()
        : elements(nullptr), factory(), size(0), capacity(5), currentFile("default.txt") {
    this->allocateMem();
    if (elements == nullptr)
        throw std::bad_alloc();
}

void skip(std::ifstream &file) {
    //have to make sure that the tag is closed!
    char symbol = 0;
    while (file.get(symbol) && symbol != '>');
}

void Canvas::openSvg(const char *fileName) {
    std::ifstream file(fileName);

    if (!file.is_open()) {
        std::cerr << "Cannot openSvg file!";
        return;
    }

    char symbol = 0;
    std::string buffer;
    bool found = false;

    while (file.get(symbol)) {
        if (symbol == '<')
            while (file.get(symbol) && symbol != '>' && symbol != ' ')
                buffer.push_back(symbol);
        if (strcmp(buffer.c_str(), "svg") == 0) {
            found = true;
            break;
        }
    }

    if (!found) {
        file.close();
        std::cerr << "Invalid file!";
        return;
    }

    this->currentFile.assign(fileName);

    while (file.get(symbol)) {
        if (symbol == '<') {
            unsigned currentIndex = file.tellg();
            file >> buffer;
            if (strcmp(buffer.c_str(), "/svg>") == 0)
                break;
            else {
                file.seekg(currentIndex);
                this->addElement(this->factory.svgCreateShape(file));
                skip(file);
            }
        }
    }

    file.close();
}

void Canvas::print() {
    for (unsigned i = 0; i < this->size; i++)
        this->elements[i]->print();
}

void Canvas::create(std::istream &input) {
    this->addElement(this->factory.userCreateShape(input));
}

void Canvas::group(float tlX, float tlY, float brX, float brY) {
    Group *elementGroup;

    try {
        elementGroup = new Group;
    }
    catch (std::bad_alloc &) {
        return;
    }

    for (unsigned i = 0; i < this->size; i++)
        if (this->elements[i]->isContained(tlX, tlY, brX, brY)) {
            elementGroup->addElement(this->elements[i]);
            this->shiftBack(i);
        }

    this->addElement(elementGroup);
}

/*

void Canvas::bringForward(unsigned int id, unsigned int n) {
    int index = -1;
    unsigned oldId = id;

    for (unsigned i = 0; i < this->size; i++)
        if (this->shapes[i]->getID() == id) {
            this->shapes[i]->bringForward(n);
            if (this->shapes[i]->getID() == id)
                return;
            index = i;
        }

    for (unsigned i = 0; i < this->size; i++) {
        if (i != index && this->shapes[i]->getID() > oldId && this->shapes[index]->getID() >= this->shapes[i]->getID())
            this->shapes[i]->sendBackwards(1);
    }

    this->moveFront(this->shapes[index], index);
}


void Canvas::sendBackwards(unsigned int id, unsigned int n) {
    int index = -1;
    unsigned oldId = id;

    for (unsigned i = 0; i < this->size; i++)
        if (this->shapes[i]->getID() == id) {
            this->shapes[i]->sendBackwards(n);
            if (this->shapes[i]->getID() == id)
                return;
            index = i;
        }

    for (unsigned i = 0; i < this->size; i++) {
        if (i != index && this->shapes[i]->getID() < oldId && this->shapes[index]->getID() <= this->shapes[i]->getID())
            this->shapes[i]->bringForward(1);
    }

    this->moveBack(this->shapes[index], index);
}

*/

void Canvas::translate(int id, float verticalTrl, float horizontalTrl) {

}


void Canvas::save() {
    std::ofstream file(currentFile.c_str(), std::ios::trunc);
    if (!file.is_open()) {
        std::cerr << "Cannot open file!";
        return;
    }

    file << "<svg>\n";

    for (unsigned i = 0; i < this->size; i++)
        this->elements[i]->saveToSvgFile(file);

    file << "</svg>";

    file.close();
}

void Canvas::saveSvg() const {
    std::string newFile;
    unsigned i = 0;

    while (*(currentFile.c_str() + i) != '.') {
        newFile += *(currentFile.c_str() + i);
        ++i;
    }

    newFile += ".html";

    std::ofstream file(newFile, std::ios::trunc);

    if (!file.is_open()) {
        std::cerr << "Cannot open file!";
        return;
    }

    file << "<svg width = \"100%\" height = \"100%\" >\n";

    for (unsigned i = 0; i < this->size; i++)
        this->elements[i]->saveToSvgFile(file);

    file << "</svg>";

    file.close();
}

Canvas::~Canvas() {
    this->destroy();
}

void Canvas::addElement(Element *element) {
    if (element == nullptr)
        return;
    if (this->size == this->capacity)
        this->resize();
    if (this->size == this->capacity)
        return;
    this->elements[this->size++] = element;
}

void Canvas::shiftBack(unsigned int index) {
    for (unsigned i = index; i < this->size - 1; i++)
        this->elements[i] = this->elements[i + 1];
    this->elements[this->size - 1] = nullptr;
    this->size--;
}

void Canvas::allocateMem() {
    try {
        this->elements = new Element *[this->capacity];
    }
    catch (std::bad_alloc &) {
        this->elements = nullptr;
    }
}

void Canvas::resize() {
    this->capacity *= 2;
    Element **copyShapes = this->elements;

    this->allocateMem();

    if (this->elements == nullptr) {
        this->elements = copyShapes;
        this->capacity /= 2;
        return;
    }

    for (unsigned i = 0; i < this->size; i++)
        this->elements[i] = copyShapes[i];

    delete[] copyShapes;
}

void Canvas::destroy() {
    for (unsigned i = 0; i < this->size; i++)
        delete this->elements[i];
    delete[] this->elements;
}