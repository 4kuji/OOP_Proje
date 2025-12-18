#include "SortedArray.h"

// Sirali ekleme (artan sirada)
void SortedArray::push(int value) {
    int n = getSize();

    // Once temel siniftan sona bir bos yer ac
    DynamicArray::push(0); // gecici deger, sadece yer acmak icin

    int i = n - 1;
    // Yeni degerden buyuk olan tum elemanlari bir saga kaydir
    while (i >= 0 && (*this)[i] > value) {
        (*this)[i + 1] = (*this)[i];
        --i;
    }

    // Bosalan yere yeni degeri yaz
    (*this)[i + 1] = value;
}

// Binary Search Algoritmasi
int SortedArray::binarySearch(int value) const {
    int left = 0;
    int right = getSize() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        int midVal = (*this)[mid];

        if (midVal == value)
            return mid; // Bulundu

        if (midVal < value)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1; // Bulunamadi
}
