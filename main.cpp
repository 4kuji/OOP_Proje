#include <iostream>
#include "DynamicArray.h"
#include "SortedArray.h"
#include "UniqueArray.h"

using namespace std;

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
