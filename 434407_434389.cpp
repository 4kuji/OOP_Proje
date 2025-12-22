#include <iostream>
#include <stdexcept> // std::out_of_range (exeption fırlatır) icin 
using namespace std;


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
    friend ostream& operator<<(ostream& os, const DynamicArray& array);
};

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

class UniqueArray : public DynamicArray {
public:
    UniqueArray() : DynamicArray() {}
    UniqueArray(int capacity) : DynamicArray(capacity) {}

    // Override: Eger eleman varsa eklemez
    void push(int value) override;

    // Eleman var mi kontrolu
    bool contains(int value) const;
};



int main() {
    cout << "--- DynamicArray Testi ---" << endl;
    // 1. DynamicArray testi
    DynamicArray arr1;
    arr1.push(10);
    arr1.push(20);
    arr1.push(30);
    arr1.print(); // Cikti: [10, 20, 30]

    // 2. Indeksleme operatoru
    cout << "\n--- Indeksleme Operatoru Testi ---" << endl;
    arr1[1] = 25;
    cout << "arr1[1] = " << arr1[1] << endl; // Cikti: 25
    cout << "Guncel arr1: " << arr1 << endl;

    // 3. Birlestirme operatoru
    cout << "\n--- Birlestirme Operatoru (+) Testi ---" << endl;
    DynamicArray arr2;
    arr2.push(40);
    arr2.push(50);

    DynamicArray arr3 = arr1 + arr2;
    arr3.print(); // Cikti: [10, 25, 30, 40, 50]

    // 4. SortedArray testi
    cout << "\n--- SortedArray Testi ---" << endl;
    SortedArray sorted;
    sorted.push(50);
    sorted.push(10);
    sorted.push(30);
    sorted.push(20);
    sorted.print(); // Cikti: [10, 20, 30, 50] (Otomatik siralanmis olmali)

    // Binary Search Testi
    int aranan = 30;
    int index = sorted.binarySearch(aranan);
    cout << aranan << " bulundu, indeks: " << index << endl;

    // 5. UniqueArray testi
    cout << "\n--- UniqueArray Testi ---" << endl;
    UniqueArray unique;
    unique.push(10);
    unique.push(20);
    unique.push(10); // Bu eklenmemeli (Tekrar)
    unique.push(30);
    unique.print(); // Cikti: [10, 20, 30]

    cout << "20 var mi? " << (unique.contains(20) ? "Evet" : "Hayir") << endl;

    return 0;
}

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
       cerr << "Uyari: Bos diziden eleman silinemez (pop)." << endl; //cerr error gödermek için
    }
}

// Indeks ile Eleman Getirme
int DynamicArray::get(int index) const {
    if (index < 0 || index >= m_size)
        throw out_of_range("get(): Indeks sinirlarin disinda!");
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
     cout << "[";
    for (int i = 0; i < m_size; ++i) {
        cout << m_data[i];
        if (i < m_size - 1) cout << ", ";
    }
       cout << "]" << endl;
}

// [] Operatoru (okuma + yazma)
int& DynamicArray::operator[](int index) {
    if (index < 0 || index >= m_size) {
           cerr << "Hata: [] operatoru ile gecersiz erisim! (index="
                  << index << ")" << endl;
        throw std::out_of_range("operator[]: Indeks sinirlarin disinda!");
    }
    return m_data[index];
}

// [] Operatoru (const versiyon, sadece okuma) -> sadece const nesler üzerinde kullanılır
const int& DynamicArray::operator[](int index) const {
    if (index < 0 || index >= m_size) {
           cerr << "Hata: [] const operatoru ile gecersiz erisim! (index="
                  << index << ")" << endl;
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
  ostream& operator<<(ostream& os, const DynamicArray& array) //dönüş tipini böyle seçtik çünkü arka arkaya yazdırma işlemi yapıyoruz
{
    os << "[";
    for (int i = 0; i < array.m_size; ++i) {
        os << array.m_data[i];
        if (i < array.m_size - 1) os << ", ";//son elemandan sonra virgül konulmaması için
    }
    os << "]";
    return os;
}

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
