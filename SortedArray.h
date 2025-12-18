#ifndef SORTED_ARRAY_H
#define SORTED_ARRAY_H

#include "DynamicArray.h"

class SortedArray : public DynamicArray {
public:
    // Yapicilar Base class'i cagirir
    SortedArray() : DynamicArray() {}
    SortedArray(int capacity) : DynamicArray(capacity) {}

    // Override: Elemani sirali sekilde ekler
    void push(int value) override;

    // Binary Search (Ikili Arama)
    int binarySearch(int value) const;
};

#endif
