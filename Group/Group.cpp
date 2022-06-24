#include "Group.h"


Group::Group()
        : Element(Point(), Point()), size(0) {
}

void Group::addElement(Element *element) {
    if (element == nullptr)
        return;
    this->elements.push_back(element);
    ++this->size;

    if (this->size == 1) {
        this->changeTL(element->getTL().getX(), element->getTL().getY());
        this->changeBR(element->getBR().getX(), element->getBR().getY());
    } else {
        if (element->getTL() <= this->getTL())
            this->changeTL(element->getTL().getX(), element->getTL().getY());
        if (element->getBR() >= this->getBR())
            this->changeBR(element->getBR().getX(), element->getBR().getY());
    }
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

void Group::saveToFormat(std::ofstream &file) const {
    for (unsigned i = 0; i < this->size; i++)
        this->elements[i]->saveToFormat(file);
}

void Group::saveToSvgFile(std::ofstream &file) const {
    for (unsigned i = 0; i < this->size; i++)
        this->elements[i]->saveToSvgFile(file);
}

std::vector<Element *> Group::ungroup() {
    std::vector<Element *> currentGroup;
    for (unsigned i = 0; i < this->size; i++)
        currentGroup.push_back(this->elements[i]);

    this->size = 0;
    return currentGroup;
}

Group::~Group() {
    this->destroy();
}

void Group::destroy() {
    for (unsigned i = 0; i < this->size; i++)
        delete this->elements[i];
}