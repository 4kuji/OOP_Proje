#include "DynamicArray.h"
#include <stdexcept> // std::out_of_range (exeption fırlatır) icin 

// Varsayilan Yapici: Kapasite 2 ile baslar
DynamicArray::DynamicArray() : m_data(nullptr), m_size(0), m_capacity(2) {
    m_data = new int[m_capacity];
}

// Parametreli Yapici
DynamicArray::DynamicArray(int capacity) : m_data(nullptr), m_size(0) {
    //m_capacity = (capacity > 0) ? capacity : 2;
    if (capacity > 0){
        m_capacity = capacity;
    }
    else{
        m_capacity = 2;
    }
    m_data = new int[m_capacity];
}

// Copy Constructor (Derin Kopyalama)
DynamicArray::DynamicArray(const DynamicArray& other)
    : m_data(nullptr), m_size(other.m_size), m_capacity(other.m_capacity) {
    m_data = new int[m_capacity];
    for (int i = 0; i < m_size; ++i) {
        m_data[i] = other.m_data[i];
    }
}

// Destructor (Bellek Temizligi)
DynamicArray::~DynamicArray() {
    if (m_data != nullptr) {
        delete[] m_data;// memo leak için
        m_data = nullptr; // Dangling pointer onlemi
    }
}

// Eleman Ekleme
void DynamicArray::push(int value) {
    if (m_size == m_capacity) {
        // Kapasite dolduysa 2 katina cikar
        int newCapacity = m_capacity * 2;
        int* newData = new int[newCapacity];

        for (int i = 0; i < m_size; ++i) {
            newData[i] = m_data[i];
        }

        delete[] m_data; // Eski bellegi sil
        m_data = newData;
        m_capacity = newCapacity;
    }
    m_data[m_size++] = value;
}

// Sondan Eleman Silme
void DynamicArray::pop() {
    if (m_size > 0) {
        m_size--;
    } else {
        std::cerr << "Uyari: Bos diziden eleman silinemez (pop)." << std::endl; //cerr error gödermek için
    }
}

// Indeks ile Eleman Getirme
int DynamicArray::get(int index) const {
    if (index < 0 || index >= m_size)
        throw std::out_of_range("get(): Indeks sinirlarin disinda!");
    return m_data[index];
}

// Indeks ile Eleman Degistirme
void DynamicArray::set(int index, int value) {
    if (index < 0 || index >= m_size)
        throw std::out_of_range("set(): Indeks sinirlarin disinda!");
    m_data[index] = value;
}

int DynamicArray::getSize() const { return m_size; }
int DynamicArray::getCapacity() const { return m_capacity; }
bool DynamicArray::isEmpty() const { return m_size == 0; }

void DynamicArray::clear() {
    // Kapasiteyi degistirmeden boyutu sifirlariz (hizli temizleme)
    m_size = 0;
}

void DynamicArray::print() const {
    std::cout << "[";
    for (int i = 0; i < m_size; ++i) {
        std::cout << m_data[i];
        if (i < m_size - 1) std::cout << ", ";
    }
    std::cout << "]" << std::endl;
}

// [] Operatoru (okuma + yazma)
int& DynamicArray::operator[](int index) {
    if (index < 0 || index >= m_size) {
        std::cerr << "Hata: [] operatoru ile gecersiz erisim! (index="
                  << index << ")" << std::endl;
        throw std::out_of_range("operator[]: Indeks sinirlarin disinda!");
    }
    return m_data[index];
}

// [] Operatoru (const versiyon, sadece okuma) -> sadece const nesler üzerinde kullanılır
const int& DynamicArray::operator[](int index) const {
    if (index < 0 || index >= m_size) {
        std::cerr << "Hata: [] const operatoru ile gecersiz erisim! (index="
                  << index << ")" << std::endl;
        throw std::out_of_range("operator[] const: Indeks sinirlarin disinda!");
    }
    return m_data[index];
}

// Atama Operatoru (=)
DynamicArray& DynamicArray::operator=(const DynamicArray& other) {
    if (this == &other) return *this; // Kendine atama kontrolu

    delete[] m_data; // Mevcut bellegi temizle

    m_size = other.m_size;
    m_capacity = other.m_capacity;
    m_data = new int[m_capacity];

    for (int i = 0; i < m_size; ++i) {
        m_data[i] = other.m_data[i];
    }
    return *this;
}

// Esitlik Operatoru (==)
bool DynamicArray::operator==(const DynamicArray& other) const {
    if (m_size != other.m_size) return false;
    for (int i = 0; i < m_size; ++i) {
        if (m_data[i] != other.m_data[i]) return false;
    }
    return true;
}

bool DynamicArray::operator!=(const DynamicArray& other) const {
    return !(*this == other);
}

// Toplama Operatoru (+)
DynamicArray operator+(const DynamicArray& left, const DynamicArray& right) {
    // Kapasite olarak tum elemanlari tasiyacak kadar alan acmak yeterli
    DynamicArray result(left.m_size + right.m_size);

    // Once sol tarafi ekle
    for (int i = 0; i < left.m_size; ++i) {
        result.push(left.m_data[i]);
    }
    // Sonra sag tarafi ekle
    for (int i = 0; i < right.m_size; ++i) {
        result.push(right.m_data[i]);
    }
    return result;
}

// Cikis Operatoru (<<)
std::ostream& operator<<(std::ostream& os, const DynamicArray& array) //dönüş tipini böyle seçtik çünkü arka arkaya yazdırma işlemi yapıyoruz
{
    os << "[";
    for (int i = 0; i < array.m_size; ++i) {
        os << array.m_data[i];
        if (i < array.m_size - 1) os << ", ";//son elemandan sonra virgül konulmaması için
    }
    os << "]";
    return os;
}
