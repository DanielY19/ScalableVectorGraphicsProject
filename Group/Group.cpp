#include "Group.h"


Group::Group()
        : Element(Point(), Point()), elements(nullptr), size(0), capacity(5), TL(), BR() {
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

unsigned int Group::getSize() const {
    return this->size;
}

Element *Group::getElementAtIndex(unsigned int index) {
    return this->elements[index];
}

Group::~Group() {
    this->destroy();
}

void Group::allocateMem() {
    try {
        this->elements = new Element*[this->capacity];
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
    for(unsigned i=0;i< this->size;i++)
        delete this->elements[i];
    delete[] this->elements;
}