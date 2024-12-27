/**

*/
#include "../include/BST.h"
#include <iostream>

BST::BST() {
    kok = nullptr;
    asciiToplam = 0;
}
        
BST::~BST() {
    agaciSil(kok);
}
void BST::kokAta(int deger) {
        kok = new BSTNode(deger);
    }
void BST::ekle(int deger) {
    try {
        if (deger < 0 || deger > 255) {
            throw std::out_of_range("ASCII degeri gecersiz!");
        }
        kok = ekleOzyineli(kok, deger);
        asciiToplamGuncelle();
    }
    catch (const std::exception& e) {
        std::cerr << "Hata: " << e.what() << std::endl;
    }
}

int BST::tumAgacToplami(BSTNode* dugum) {
    if (!dugum) return 0;
    
    int toplam = dugum->value;
    for (BSTNode* solDugum = dugum->sol; solDugum != nullptr; solDugum = solDugum->sol) {
        toplam += (solDugum->value * 2); 
        if (solDugum->sag) {  
            toplam += tumAgacToplami(solDugum->sag);
        }
    }

    for (BSTNode* sagDugum = dugum->sag; sagDugum != nullptr; sagDugum = sagDugum->sag) {
        toplam += sagDugum->value;
        if (sagDugum->sol) {
            toplam += tumAgacToplami(sagDugum->sol);
        }
    }
    
    return toplam;
}

void BST::asciiToplamGuncelle() {
    if (!kok) {
        asciiToplam = 0;
        return;
    }
    asciiToplam = tumAgacToplami(kok);
}

BSTNode* BST::ekleOzyineli(BSTNode* dugum, int deger) {
    if (!dugum) {
        return new BSTNode(deger);
    }
    
    if (deger < dugum->value) {
        dugum->sol = ekleOzyineli(dugum->sol, deger);
    } else {
        dugum->sag = ekleOzyineli(dugum->sag, deger);
    }
    return dugum;
}

BSTNode* BST::kokAl() {
    return kok;
}

void BST::asciiToplamAta(int toplam) {
    asciiToplam = toplam;
}

int BST::asciiToplamAl() {
    return asciiToplam;
}

void BST::agaciSil(BSTNode* dugum) {
    if (dugum == nullptr) return;
    agaciSil(dugum->sol);
    agaciSil(dugum->sag);
    delete dugum;
}

BSTNode* BST::aynaOzyineli(BSTNode* dugum) {
    if (dugum == nullptr) return nullptr;
   
    BSTNode* gecici = dugum->sol;
    dugum->sol = aynaOzyineli(dugum->sag);
    dugum->sag = aynaOzyineli(gecici);
    
    return dugum;
}

void BST::aynala() {
    if (!kok) return;  
    kok = aynaOzyineli(kok);
    asciiToplamGuncelle();
}
