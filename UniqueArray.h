#ifndef UNIQUE_ARRAY_H
#define UNIQUE_ARRAY_H

#include "DynamicArray.h"

class UniqueArray : public DynamicArray {
public:
    UniqueArray() : DynamicArray() {}
    UniqueArray(int capacity) : DynamicArray(capacity) {}

    // Override: Eger eleman varsa eklemez
    void push(int value) override;

    // Eleman var mi kontrolu
    bool contains(int value) const;
};

#endif
