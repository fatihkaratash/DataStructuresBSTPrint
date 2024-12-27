/**

*/

#include "../include/LinkedList.h"
#include <fstream>
#include <string>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <functional>
#include <cmath>

LinkedList::LinkedList() {
    bas = nullptr;
    guncelGosterimPozisyonu = nullptr;
}

LinkedList::~LinkedList() {
    LinkedListNode* simdiki = bas;
    while (simdiki != nullptr) {
        LinkedListNode* sonraki = simdiki->sonraki;
        delete simdiki;
        simdiki = sonraki;
    }
}

void LinkedList::dugumEkle() {
    LinkedListNode* yeniDugum = new LinkedListNode();
    if (bas == nullptr) {
        bas = yeniDugum;
    } else {
        LinkedListNode* gecici = bas;
        while (gecici->sonraki != nullptr) {
            gecici = gecici->sonraki;
        }
        gecici->sonraki = yeniDugum;
    }
}
void LinkedList::metinDosyasiIsle(const char* dosyaAdi) {
    std::ifstream dosya(dosyaAdi);
    std::string satir;
    
    while (std::getline(dosya, satir)) {
        // Remove BOM if present
        if (satir.size() >= 3 && (unsigned char)satir[0] == 0xEF 
            && (unsigned char)satir[1] == 0xBB 
            && (unsigned char)satir[2] == 0xBF) {
            satir.erase(0, 3);
        }

        if (satir.empty()) continue;

        std::string temizSatir;
        for (char karakter : satir) {
            int asciiDeger = static_cast<int>(karakter);
            if (asciiDeger >= 32 && asciiDeger <= 126) {
                temizSatir += karakter;
            }
        }

        if (!temizSatir.empty()) {
            dugumEkle();
            LinkedListNode* simdiki = bas;
            while (simdiki->sonraki != nullptr) {
                simdiki = simdiki->sonraki;
            }

            for (char karakter : temizSatir) {
                int asciiDeger = static_cast<int>(karakter);
                simdiki->bst->ekle(asciiDeger);
            }
        }
    }
    dosya.close();
    guncelGosterimPozisyonu = bas;
}

LinkedListNode* LinkedList::basAl() {
    return bas;
}


//--------------------------------
void LinkedList::sonrakineGit() {
    if (guncelGosterimPozisyonu && guncelGosterimPozisyonu->sonraki) {
        guncelGosterimPozisyonu = guncelGosterimPozisyonu->sonraki;
    }
}

void LinkedList::oncekineGit() {
    if (guncelGosterimPozisyonu && guncelGosterimPozisyonu != bas) {
        LinkedListNode* gecici = bas;
        while (gecici->sonraki != guncelGosterimPozisyonu) {
            gecici = gecici->sonraki;
        }
        guncelGosterimPozisyonu = gecici;
    }
}

void LinkedList::tusaBasildiginda(char tus) {
    if (tus == 'a' && guncelGosterimPozisyonu != bas) {
        oncekineGit();
    }
    else if (tus == 'd' && guncelGosterimPozisyonu->sonraki != nullptr) {
        sonrakineGit();
    }
     
    else if (tus == 'w' && guncelGosterimPozisyonu) {
        guncelGosterimPozisyonu->bst->aynala();
    }
    else if (tus == 's' && guncelGosterimPozisyonu) {
        guncelDugumuSil();
    }
}


void LinkedList::guncelDugumuSil() {
    if (!guncelGosterimPozisyonu || !bas) return;
    
    LinkedListNode* silinecek = guncelGosterimPozisyonu;
    
    if (silinecek == bas) {
        bas = bas->sonraki;
        guncelGosterimPozisyonu = bas;
    }
    else {
        LinkedListNode* onceki = bas;
        while (onceki && onceki->sonraki != silinecek) {
            onceki = onceki->sonraki;
        }
        
        if (onceki) {
            onceki->sonraki = silinecek->sonraki;
            guncelGosterimPozisyonu = silinecek->sonraki ? silinecek->sonraki : onceki;
        }
    }
    
    delete silinecek;
    system("cls");
    agBSTGoster();
}

void LinkedList::agBSTGoster() {
    try {
        system("cls");
        std::cout << std::string(120, '=') << std::endl;
        std::cout << "KONTROLLER : (w = aynala[ASCII degisir], s = sil, a = geri, d = ileri, 'q' = cikis)" << std::endl;
        std::cout << std::string(120, '=') << std::endl;

        if (!bas) {
            std::cout << "Gösterilecek düğüm yok.\n";
            return;
        }

        if (!guncelGosterimPozisyonu) {
            guncelGosterimPozisyonu = bas;
        }

        const int MAX_SUTUN = 10;
        int toplamDugum = 0;
        int guncelIndeks = 0;
        
        LinkedListNode* gecici = bas;
        while (gecici) {
            if (gecici == guncelGosterimPozisyonu) {
                guncelIndeks = toplamDugum;
            }
            toplamDugum++;
            gecici = gecici->sonraki;
        }
        
      

        int pencereBaslangic = (guncelIndeks / MAX_SUTUN) * MAX_SUTUN;
        
        if (toplamDugum - pencereBaslangic < MAX_SUTUN && pencereBaslangic > 0) {
            pencereBaslangic = ((toplamDugum - 1) / MAX_SUTUN) * MAX_SUTUN;
        }

        LinkedListNode* pencereDugumu = bas;
        for (int i = 0; i < pencereBaslangic && pencereDugumu; i++) {
            pencereDugumu = pencereDugumu->sonraki;
        }

        const int genislik = 10;
        const std::string dugumSiniri(genislik, '.');
        pencereDugumu = bas;
        for (int i = 0; i < pencereBaslangic; i++) {
            pencereDugumu = pencereDugumu->sonraki;
        }

        for (int i = 0; i < MAX_SUTUN && pencereDugumu; i++) {
            std::cout << dugumSiniri << "   ";
            pencereDugumu = pencereDugumu->sonraki;
        }
        std::cout << std::endl;

        pencereDugumu = bas;
        for (int i = 0; i < pencereBaslangic; i++) {
            pencereDugumu = pencereDugumu->sonraki;
        }

        for (int i = 0; i < MAX_SUTUN && pencereDugumu; i++) {
            unsigned int adres = reinterpret_cast<unsigned long long>(pencereDugumu) % 10000;
            std::cout << "." << std::setw(genislik - 2) << std::right << adres << "." << "   ";
            pencereDugumu = pencereDugumu->sonraki;
        }
        std::cout << std::endl;

        pencereDugumu = bas;
        for (int i = 0; i < pencereBaslangic; i++) {
            pencereDugumu = pencereDugumu->sonraki;
        }

        for (int i = 0; i < MAX_SUTUN && pencereDugumu; i++) {
            std::cout << dugumSiniri << "   ";
            pencereDugumu = pencereDugumu->sonraki;
        }
        std::cout << std::endl;

        pencereDugumu = bas;
        for (int i = 0; i < pencereBaslangic; i++) {
            pencereDugumu = pencereDugumu->sonraki;
        }

        //burası hatalı
        for (int i = 0; i < MAX_SUTUN && pencereDugumu; i++) {
            int agacDegeri = pencereDugumu->bst->asciiToplamAl();
            std::string goruntu = std::to_string(agacDegeri);

            int toplamBosluk = genislik - 2;
            int solBosluk = (toplamBosluk - goruntu.length()) / 2;
            int sagBosluk = toplamBosluk - solBosluk - goruntu.length();

            std::cout << "." 
                      << std::string(solBosluk, ' ') 
                      << goruntu
                      << std::string(sagBosluk, ' ') 
                      << "." << "   ";
            pencereDugumu = pencereDugumu->sonraki;
        }
        std::cout << std::endl;

        pencereDugumu = bas;
        for (int i = 0; i < pencereBaslangic; i++) {
            pencereDugumu = pencereDugumu->sonraki;
        }

        for (int i = 0; i < MAX_SUTUN && pencereDugumu; i++) {
            std::cout << dugumSiniri << "   ";
            pencereDugumu = pencereDugumu->sonraki;
        }
        std::cout << std::endl;

        pencereDugumu = bas;
        for (int i = 0; i < pencereBaslangic; i++) pencereDugumu = pencereDugumu->sonraki;
        for (int i = 0; i < MAX_SUTUN && pencereDugumu; i++) {
            if (pencereDugumu->sonraki == nullptr) {
                std::cout << "." << std::setw(genislik-2) << std::right << "NULL" << "." << "   ";
            } else {
                unsigned int sonrakiAdres = reinterpret_cast<unsigned long long>(pencereDugumu->sonraki) % 10000;
                std::cout << "." << std::setw(genislik-2) << std::right << sonrakiAdres << "." << "   ";
            }
            pencereDugumu = pencereDugumu->sonraki;
        }
        std::cout << std::endl;

        pencereDugumu = bas;
        for (int i = 0; i < pencereBaslangic; i++) pencereDugumu = pencereDugumu->sonraki;
        for (int i = 0; i < MAX_SUTUN && pencereDugumu; i++) {
            std::cout << dugumSiniri << "   ";
            pencereDugumu = pencereDugumu->sonraki;
        }
        std::cout << std::endl;

        int gorecePozisyon = guncelIndeks - pencereBaslangic;
        int bosluklar = gorecePozisyon * (genislik + 3);
        std::cout << std::string(bosluklar, ' ') << std::string(genislik, '^') << std::endl;
        
        std::string cubuklar;
        for (int i = 0; i < genislik; i++) {
            if (i % 2 == 0) cubuklar += "|";
            else cubuklar += " ";
        }
        std::cout << std::string(bosluklar, ' ') << cubuklar << std::endl;

        std::cout << "\nMevcut Dugumun BST'si:\n";
        if (guncelGosterimPozisyonu) {
            bstDugumuGoster(guncelGosterimPozisyonu->bst->kokAl(), 0, "");
        }

    } catch (const std::exception& e) {
        std::cout << "Ag'da hata: " << e.what() << std::endl;
    }
}

void LinkedList::bstDugumuGoster(BSTNode* dugum, int seviye, std::string onEk) {
    if (!dugum) return;
    
    const int TOPLAM_GENISLIK = 80;
    const int MERKEZ_KONUM = 40;
    const int MIN_BOSLUK = 4;
    
    int yukseklik = agacYuksekligiAl(dugum);
    Vector<Vector<DugumPozisyonu>> seviyeDugumleri(yukseklik);
    
    // Her seviye için Vector oluştur
    for(int i = 0; i < yukseklik; i++) {
        seviyeDugumleri[i] = Vector<DugumPozisyonu>();
    }
    
    std::function<void(BSTNode*, int, int)> seviyePozisyonlariAta = 
    [&](BSTNode* d, int derinlik, int konum) {
        if (!d || derinlik >= yukseklik) return;
        seviyeDugumleri[derinlik].ekle(DugumPozisyonu(d, konum));
        int bosluk = TOPLAM_GENISLIK / (1 << (derinlik + 2));
        bosluk = std::max(bosluk, MIN_BOSLUK);
        if (d->sol) seviyePozisyonlariAta(d->sol, derinlik + 1, konum - bosluk);
        if (d->sag) seviyePozisyonlariAta(d->sag, derinlik + 1, konum + bosluk);
    };
    
    seviyePozisyonlariAta(dugum, 0, MERKEZ_KONUM);
    
    for (int i = 0; i < yukseklik; i++) {
        std::string dugumSatiri(TOPLAM_GENISLIK, ' ');
        for (int j = 0; j < seviyeDugumleri[i].getBoyut(); j++) {
            DugumPozisyonu& dugumPoz = seviyeDugumleri[i][j];
            std::string dugumMetni = std::string(1, static_cast<char>(dugumPoz.dugum->value));
            int duzeltilmisKonum = std::max(0, std::min(dugumPoz.konum, TOPLAM_GENISLIK - (int)dugumMetni.length()));
            for (size_t k = 0; k < dugumMetni.length() && duzeltilmisKonum + k < TOPLAM_GENISLIK; k++) {
                dugumSatiri[duzeltilmisKonum + k] = dugumMetni[k];
            }
        }
        std::cout << dugumSatiri << std::endl;
        
        if (i < yukseklik - 1) {
            std::string baglantiSatiri(TOPLAM_GENISLIK, ' ');
            std::string noktaSatiri(TOPLAM_GENISLIK, ' ');
            
            for (int j = 0; j < seviyeDugumleri[i].getBoyut(); j++) {
                DugumPozisyonu& ebeveynPoz = seviyeDugumleri[i][j];
                std::string dugumMetni = std::string(1, static_cast<char>(ebeveynPoz.dugum->value));
                int bosluk = TOPLAM_GENISLIK / (1 << (i + 2));
                bosluk = std::max(bosluk, MIN_BOSLUK);
                
                if (ebeveynPoz.dugum->sol && ebeveynPoz.dugum->sag) {
                    int solKonum = std::max(0, ebeveynPoz.konum - bosluk);
                    int sagKonum = std::min(TOPLAM_GENISLIK - 1, ebeveynPoz.konum + bosluk);
                    
                    for (int k = solKonum + 1; k < sagKonum; k++) {
                        if (k < TOPLAM_GENISLIK) baglantiSatiri[k] = '.';
                    }
                    if (solKonum < TOPLAM_GENISLIK) noktaSatiri[solKonum] = '.';
                    if (sagKonum < TOPLAM_GENISLIK) noktaSatiri[sagKonum] = '.';
                }
                else {
                    if (ebeveynPoz.dugum->sol) {
                        int solKonum = std::max(0, ebeveynPoz.konum - bosluk);
                        for (int k = solKonum + 1; k < ebeveynPoz.konum; k++) {
                            if (k < TOPLAM_GENISLIK) baglantiSatiri[k] = '.';
                        }
                        if (solKonum < TOPLAM_GENISLIK) noktaSatiri[solKonum] = '.';
                    }
                    if (ebeveynPoz.dugum->sag) {
                        int sagKonum = std::min(TOPLAM_GENISLIK - 1, ebeveynPoz.konum + bosluk);
                        for (int k = ebeveynPoz.konum + 1; k < sagKonum; k++) {
                            if (k < TOPLAM_GENISLIK) baglantiSatiri[k] = '.';
                        }
                        if (sagKonum < TOPLAM_GENISLIK) noktaSatiri[sagKonum] = '.';
                    }
                }
            }
            std::cout << baglantiSatiri << std::endl;
            std::cout << noktaSatiri << std::endl;
        }
    }
}

int LinkedList::agacYuksekligiAl(BSTNode* dugum) {
    if (!dugum) return 0;
    int solYukseklik = agacYuksekligiAl(dugum->sol);
    int sagYukseklik = agacYuksekligiAl(dugum->sag);
    return std::max(solYukseklik, sagYukseklik) + 1;
}