📦 DynamicArray Projesi (C++)

Bu proje, C++ dilinde dinamik dizi yapısının sıfırdan nasıl tasarlanacağını ve nesne yönelimli programlama (OOP) prensipleriyle nasıl genişletilebileceğini göstermektedir.
DynamicArray temel sınıfı üzerine kurulu SortedArray ve UniqueArray türev sınıfları ile kalıtım (inheritance) ve polimorfizm (polymorphism) örneklenmiştir.

🚀 Özellikler
🔹 DynamicArray

Dinamik bellek yönetimi (new[] / delete[])

Otomatik kapasite artırma (2 katına çıkarma)

Derin kopyalama (Copy Constructor & Assignment Operator)

Operatör aşırı yükleme:

[] indeksleme

+ iki diziyi birleştirme

== / != karşılaştırma

<< ekrana yazdırma

Hata kontrolü (std::out_of_range)

Kapsülleme (private veri üyeleri)

🔹 SortedArray (DynamicArray’den türetilmiştir)

Elemanları artan sırada ekler

Binary Search (ikili arama) desteği

push() fonksiyonu override edilmiştir

🔹 UniqueArray (DynamicArray’den türetilmiştir)

Aynı elemanın tekrar eklenmesini engeller

Lineer arama ile contains() fonksiyonu

push() fonksiyonu override edilmiştir

🧠 Kullanılan OOP Kavramları

Encapsulation (Kapsülleme)

Inheritance (Kalıtım)

Polymorphism (Sanal fonksiyonlar)

Operator Overloading

Rule of Three (Destructor, Copy Constructor, Assignment Operator)

🛠️ Sınıf Yapısı
DynamicArray
│
├── SortedArray
│
└── UniqueArray
