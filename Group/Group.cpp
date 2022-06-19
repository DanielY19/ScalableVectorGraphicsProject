#include "Group.h"

unsigned Group::groupIDGenerator = 1;

Group::Group()
        : Element(Point(), Point(), Group::groupIDGenerator++), elements(nullptr), size(0), capacity(5), TL(), BR() {
    this->allocateMem();

    if (this->elements == nullptr)
        throw std::bad_alloc();
}

void Group::addElement(Element *element) {
    if (element == nullptr)
        return;
    if (this->size == this->capacity)
        this->resize();
    if (this->size == this->capacity)
        return;
    this->elements[this->size++] = element;

    if (element->getTL() < this->TL)
        this->TL.change(element->getTL().getX(), element->getTL().getY());

    if (element->getBR() > this->BR)
        this->BR.change(element->getBR().getX(), element->getBR().getY());
}

void Group::print() const {
    for (unsigned i = 0; i < this->size; i++)
        this->elements[i]->print();
}

void Group::bringForward(unsigned int layers) {
    unsigned oldID = this->elements[this->size - 1]->getID();
    this->elements[this->size - 1]->bringForward(layers);

    if (this->elements[this->size - 1]->getID() == oldID)
        return;

    for (unsigned i = this->size - 2; i >= 0; i--) {
        this->elements[i]->bringForward(layers);
    }
}

void Group::sendBackwards(unsigned int layers) {
    unsigned oldID = this->elements[0]->getID();
    this->elements[0]->sendBackwards(layers);

    if (this->elements[0]->getID() == oldID)
        return;

    for (unsigned i = 1; i < this->size; i--) {
        this->elements[i]->sendBackwards(layers);
    }
}

void Group::translate(float verticalTrl, float horizontalTrl) {
    for (unsigned i = 0; i < this->size; i++)
        this->elements[i]->translate(verticalTrl, horizontalTrl);
}

void Group::scale(float verticalScl, float horizontalScl) {
    for (unsigned i = 0; i < this->size; i++)
        this->elements[i]->scale(verticalScl, horizontalScl);
}

void Group::saveToSvgFile(std::ofstream &file) const {
    for (unsigned i = 0; i < this->size; i++)
        this->elements[i]->saveToSvgFile(file);
}

unsigned int Group::getID() const {
    return this->id;
}

Group::~Group() {
    this->destroy();
}

void Group::allocateMem() {
    try {
        this->elements = new Element *[this->capacity];
    }
    catch (std::bad_alloc &) {
        this->elements = nullptr;
    }
}

void Group::resize() {
    Element **copyElements = this->elements;
    this->capacity *= 2;

    this->allocateMem();

    if (this->elements == nullptr) {
        this->elements = copyElements;
        this->capacity /= 2;
        return;
    }

    for (unsigned i = 0; i < this->size; i++)
        this->elements[i] = copyElements[i];

    delete[] copyElements;
}

void Group::destroy() {
    delete[] this->elements;
}