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

