#include "Canvas.h"
#include <iostream>
#include <cstring>

Canvas::Canvas()
        : factory(), size(0), currentFile("default.txt") {
}

void skip(std::ifstream &file) {
    //have to make sure that the tag is closed!
    char symbol = 0;
    while (file.get(symbol) && symbol != '>');
}

void Canvas::openFormat(const char *fileName) {
    std::ifstream file(fileName);

    if (!file.is_open()) {
        std::cerr << "Cannot openSvg file!";
        return;
    }

    while (file.good())
        this->addElement(this->factory.formatCreateShape(file));

    file.close();
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

    int i = 0;
    bool taken = false;

    while (i != this->size) {
        if (this->elements[i]->isContained(tlX, tlY, brX, brY)) {
            elementGroup->addElement(this->elements[i]);
            this->shiftBack(i);
            --i;
            taken = true;
        }
        ++i;
    }

    if (!taken) {
        delete elementGroup;
        return;
    }

    this->addElement(elementGroup);
}

void Canvas::ungroup(unsigned int id) {
    for (unsigned i = 0; i < this->size; i++)
        if (this->elements[i]->getID() == id) {

            std::vector<Element *> group(this->elements[i]->ungroup());
            unsigned groupSize = group.size();

            if (this->inElements(group[0]))
                return;

            delete this->elements[i];
            this->shiftBack(i);
            --Element::idGenerator;

            for (unsigned j = 0; j < groupSize; j++) {
                this->addElement(group[j]);
                this->moveBack(this->elements[this->size - 1], this->size - 1);
            }

            return;
        }
}

void Canvas::bringForward(unsigned int id, unsigned int n) {
    int index = -1;
    unsigned oldId = id;
    bool found = false;

    for (unsigned i = 0; i < this->size; i++)
        if (this->elements[i]->getID() == id) {
            this->elements[i]->bringForward(n);
            if (this->elements[i]->getID() == id)
                return;
            index = i;
            found = true;
        }

    if (!found)
        return;

    for (unsigned i = 0; i < this->size; i++) {
        if (i != index && this->elements[i]->getID() > oldId &&
            this->elements[index]->getID() >= this->elements[i]->getID())
            this->elements[i]->sendBackwards(1);
    }

    this->moveFront(this->elements[index], index);
}


void Canvas::sendBackwards(unsigned int id, unsigned int n) {
    int index = -1;
    unsigned oldId = id;
    bool found = false;

    for (unsigned i = 0; i < this->size; i++)
        if (this->elements[i]->getID() == id) {
            this->elements[i]->sendBackwards(n);
            if (this->elements[i]->getID() == id)
                return;
            index = i;
            found = true;
        }


    if (!found)
        return;

    for (unsigned i = 0; i < this->size; i++) {
        if (i != index && this->elements[i]->getID() < oldId &&
            this->elements[index]->getID() <= this->elements[i]->getID())
            this->elements[i]->bringForward(1);
    }

    this->moveBack(this->elements[index], index);
}


void Canvas::translate(int id, float verticalTrl, float horizontalTrl) {
    for (unsigned i = 0; i < this->size; i++) {
        if (this->elements[i]->getID() == id) {
            this->elements[i]->translate(verticalTrl, horizontalTrl);
            return;
        } else if (id < 0)
            this->elements[i]->translate(verticalTrl, horizontalTrl);
    }
}

void Canvas::scale(int id, float verticalScl, float horizontalScl) {
    for (unsigned i = 0; i < this->size; i++) {
        if (this->elements[i]->getID() == id) {
            this->elements[i]->scale(verticalScl, horizontalScl);
            return;
        } else if (id < 0)
            this->elements[i]->scale(verticalScl, horizontalScl);
    }
}


void Canvas::save() {
    std::ofstream file(currentFile.c_str(), std::ios::trunc);
    if (!file.is_open()) {
        std::cerr << "Cannot open file!";
        return;
    }

    for (unsigned i = 0; i < this->size; i++)
        this->elements[i]->saveToFormat(file);


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

    for (unsigned j = 0; j < this->size; j++)
        this->elements[j]->saveToSvgFile(file);

    file << "</svg>";

    file.close();
}

Canvas::~Canvas() {
    this->destroy();
}

void Canvas::addElement(Element *element) {
    if (element == nullptr)
        return;
    this->elements.push_back(element);
    ++this->size;
}

bool Canvas::inElements(const Element *element) const {
    for (unsigned i = 0; i < this->size; i++)
        if (this->elements[i] == element)
            return true;
    return false;
}

void Canvas::moveBack(Element *element, unsigned int pos) {
    unsigned i = pos;

    while (i > 0 && this->elements[i - 1]->getID() > element->getID()) {
        this->elements[i] = this->elements[i - 1];
        --i;
    }

    this->elements[i] = element;
}

void Canvas::moveFront(Element *element, unsigned int pos) {
    unsigned i = pos;

    while (i < this->size - 1 && this->elements[i + 1]->getID() < element->getID()) {
        this->elements[i] = this->elements[i + 1];
        ++i;
    }

    this->elements[i] = element;
}

void Canvas::shiftBack(unsigned int index) {
    for (unsigned i = index; i < this->size - 1; i++)
        this->elements[i] = this->elements[i + 1];
    this->elements.pop_back();
    this->size--;
}

void Canvas::destroy() {
    for (unsigned i = 0; i < this->size; i++)
        delete this->elements[i];
}