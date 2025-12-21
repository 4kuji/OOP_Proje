#include "UniqueArray.h"

bool UniqueArray::contains(int value) const {
    // Dizi sirali olmak zorunda degil, o yuzden bastan sona ariyoruz (Linear Search)
    for (int i = 0; i < getSize(); ++i) {
        if ((*this)[i] == value) {
            return true;
        }
    }
    return false;
}

void UniqueArray::push(int value) {
    // Eger deger zaten varsa islem yapmadan cik
    if (contains(value)) {
        return;
    }

    // Yoksa Base sinifin standart push fonksiyonunu kullan (sona ekler)
    DynamicArray::push(value);
}
