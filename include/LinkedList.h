/**

*/

#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "LinkedListNode.h"
#include "Vector.h"
#include <string>

struct DugumPozisyonu {
    BSTNode* dugum;
    int konum;
    DugumPozisyonu() : dugum(nullptr), konum(0) {}
    DugumPozisyonu(BSTNode* d, int k) : dugum(d), konum(k) {}
};

class LinkedList {
private:
    LinkedListNode* bas;
    LinkedListNode* guncelGosterimPozisyonu;
    int asciiToplamHesapla(const std::string& satir);
    void guncelDugumuSil();
    int agacYuksekligiAl(BSTNode* dugum);
    void bstDugumuGoster(BSTNode* dugum, int seviye, std::string onEk);
    

public:
    LinkedList();
    ~LinkedList();
    void dugumEkle();
    void metinDosyasiIsle(const char* dosyaAdi);
    LinkedListNode* basAl();
    void sonrakineGit();
    void oncekineGit();
    void tusaBasildiginda(char tus);
    void agBSTGoster();
    LinkedListNode* guncelPozisyonAl() { return guncelGosterimPozisyonu; }
};

#endif