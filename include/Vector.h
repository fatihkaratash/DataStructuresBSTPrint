/**

*/

#ifndef VECTOR_H
#define VECTOR_H

template <typename T>
class Vector {
private:
    T* elemanlar;
    int kapasite;
    int boyut;

    void yenidenBoyutlandir(int yeniKapasite) {
        T* yeniElemanlar = new T[yeniKapasite];
        for(int i = 0; i < boyut; i++) {
            yeniElemanlar[i] = elemanlar[i];
        }
        delete[] elemanlar;
        elemanlar = yeniElemanlar;
        kapasite = yeniKapasite;
    }

public:
    Vector() : elemanlar(new T[1]), kapasite(1), boyut(0) {}
    
    Vector(int baslangicBoyutu) : 
        elemanlar(new T[baslangicBoyutu]), 
        kapasite(baslangicBoyutu), 
        boyut(0) {}

    Vector(const Vector& other) : 
        elemanlar(new T[other.kapasite]),
        kapasite(other.kapasite),
        boyut(other.boyut) {
        for(int i = 0; i < boyut; i++) {
            elemanlar[i] = other.elemanlar[i];
        }
    }

    Vector& operator=(const Vector& other) {
        if(this != &other) {
            delete[] elemanlar;
            kapasite = other.kapasite;
            boyut = other.boyut;
            elemanlar = new T[kapasite];
            for(int i = 0; i < boyut; i++) {
                elemanlar[i] = other.elemanlar[i];
            }
        }
        return *this;
    }
    
    ~Vector() {
        if(elemanlar != nullptr) {
            delete[] elemanlar;
            elemanlar = nullptr;
        }
    }

    void ekle(const T& eleman) {
        if(boyut == kapasite) {
            yenidenBoyutlandir(kapasite * 2);
        }
        elemanlar[boyut++] = eleman;
    }
    
    T& operator[](int indeks) {
        return elemanlar[indeks];
    }
    
    const T& operator[](int indeks) const {
        return elemanlar[indeks];
    }
    
    int getBoyut() const {
        return boyut;
    }
    
    void temizle() {
        boyut = 0;
    }

      T* begin() { return elemanlar; }
    T* end() { return elemanlar + boyut; }
    const T* begin() const { return elemanlar; }
    const T* end() const { return elemanlar + boyut; }

    void kucult() {
        if (boyut < kapasite/2) {
            yenidenBoyutlandir(kapasite/2);
        }
    }
};

#endif