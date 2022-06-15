#include "Canvas.h"
#include <iostream>

Canvas::Canvas()
        : shapes(nullptr), factory(), size(0), capacity(5) {
    this->allocateMem();
    if (shapes == nullptr)
        throw std::bad_alloc();
}

void Canvas::print() {
    for (unsigned i = 0; i < this->size; i++)
        this->shapes[i]->print();
}

void Canvas::create() {
    Shape *addition = this->factory.userCreateShape(std::cin);
    this->addElement(addition);
}

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
        if (this->shapes[i]->getID() >= oldId && i != index)
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
        if (this->shapes[i]->getID() <= oldId && i != index)
            this->shapes[i]->bringForward(1);
    }

    this->moveBack(this->shapes[index], index);
}

void Canvas::translate(int id, float verticalTrl, float horizontalTrl) {
    for (unsigned i = 0; i < this->size; i++)
        if (id < 0)
            this->shapes[i]->translate(verticalTrl, horizontalTrl);
        else if (id == this->shapes[i]->getID()) {
            this->shapes[i]->translate(verticalTrl, horizontalTrl);
            break;
        }
}

void Canvas::scale(int id, float verticalScl, float horizontalScl) {
    for (unsigned i = 0; i < this->size; i++)
        if (id < 0)
            this->shapes[i]->scale(verticalScl, horizontalScl);
        else if (id == this->shapes[i]->getID()) {
            this->shapes[i]->scale(verticalScl, horizontalScl);
            break;
        }
}

Canvas::~Canvas() {
    this->destroy();
}

void Canvas::addElement(Shape *element) {
    if (element == nullptr)
        return;
    if (this->size == this->capacity)
        this->resize();
    if (this->size == this->capacity)
        return;
    this->shapes[this->size++] = element;
}

void Canvas::moveBack(Shape *element, unsigned int pos) {
    unsigned i = pos;

    while (i > 0 && this->shapes[i - 1]->getID() > element->getID()) {
        this->shapes[i] = this->shapes[i - 1];
        --i;
    }

    this->shapes[i] = element;
}

void Canvas::moveFront(Shape *element, unsigned int pos) {
    unsigned i = pos;

    while (i < this->size - 1 && this->shapes[i + 1]->getID() < element->getID()) {
        this->shapes[i] = this->shapes[i + 1];
        ++i;
    }

    this->shapes[i] = element;
}

void Canvas::allocateMem() {
    try {
        this->shapes = new Shape *[this->capacity];
    }
    catch (std::bad_alloc &) {
        this->shapes = nullptr;
    }
}

void Canvas::resize() {
    this->capacity *= 2;
    Shape **copyShapes = this->shapes;

    this->allocateMem();

    if (this->shapes == nullptr) {
        this->shapes = copyShapes;
        this->capacity /= 2;
        return;
    }

    for (unsigned i = 0; i < this->size; i++)
        this->shapes[i] = copyShapes[i];

    delete[] copyShapes;
}

void Canvas::destroy() {
    for (unsigned i = 0; i < this->size; i++)
        delete this->shapes[i];
    delete[] this->shapes;
}