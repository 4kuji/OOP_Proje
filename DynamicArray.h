#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <iostream>

class DynamicArray {
private:
    // Veri uyeleri private (kapsulleme icin)
    int* m_data;        // Dizi isaretcisi
    int m_size;         // Mevcut eleman sayisi
    int m_capacity;     // Toplam kapasite

public:
    // --- Yapicilar ve Yikici (Constructors & Destructor) ---
    DynamicArray();                         // Varsayilan yapici
    DynamicArray(int capacity);             // Parametreli yapici
    DynamicArray(const DynamicArray& other);// Kopyalama yapicisi (Deep Copy)
    virtual ~DynamicArray();                // Yikici (Virtual olmak zorunda degil ama sorun da yok)

    // --- Temel Fonksiyonlar ---
    virtual void push(int value); // Virtual: SortedArray ve UniqueArray override edecek
    void pop();
    int  get(int index) const;
    void set(int index, int value);
    int  getSize() const;
    int  getCapacity() const;
    bool isEmpty() const;
    void clear();
    void print() const;

    // --- Operator Yuklemeleri ---
    int& operator[](int index);             // Okuma ve yazma icin
    const int& operator[](int index) const; // Sadece okuma icin (const nesnelerde)

    DynamicArray& operator=(const DynamicArray& other); // Atama operatoru (Deep Copy)
    bool operator==(const DynamicArray& other) const;
    bool operator!=(const DynamicArray& other) const;

    // Arkadas Fonksiyonlar (Friend Functions)
    friend DynamicArray operator+(const DynamicArray& left, const DynamicArray& right);
    friend std::ostream& operator<<(std::ostream& os, const DynamicArray& array);
};

#endif
