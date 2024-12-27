/**

*/

#ifndef BST_H
#define BST_H

#include "BSTNode.h"

class BST {
private:
    BSTNode* kok;
    int asciiToplam;
    int solAsciiToplam;
    int sagAsciiToplam;
    
    BSTNode* ekleOzyineli(BSTNode* dugum, int deger);
    void agaciSil(BSTNode* dugum); 
    //int agacDegeriHesapla(BSTNode* dugum); 
    BSTNode* aynaOzyineli(BSTNode* dugum);

    void asciiToplamGuncelle();
    int altAgacToplamHesapla(BSTNode* dugum, bool solMu);

public:
    BST();
    ~BST(); 
    void ekle(int deger);
    void kokAta(int deger);
    BSTNode* kokAl();
    void asciiToplamAta(int toplam);
    int asciiToplamAl();
   // int agacDegeriAl(); 
   int tumAgacToplami(BSTNode* dugum);
    void aynala();
};

#endif