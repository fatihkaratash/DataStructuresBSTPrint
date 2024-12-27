/**

*/

#include <iostream>
#include <iomanip>
#include <conio.h> 
#include "../include/LinkedList.h"

int main() {
    LinkedList liste;
    liste.metinDosyasiIsle("agaclar.txt");

    system("cls");
    liste.agBSTGoster();
    
    char tus;
    while (true) {
        tus = _getch();
        if (tus == 'q') break;
        
        if (tus == 0 || tus == 224) {
            tus = _getch();
            switch(tus) {
                case 75: tus = 'a'; break;  // Sol ok
                case 77: tus = 'd'; break;  // Sağ ok
            }
        }
        
        if (tus == 'a' || tus == 'd' || tus == 'w' || tus == 's') {
            system("cls");
            liste.tusaBasildiginda(tus);
            liste.agBSTGoster();
        }
        else {
            std::cout << "Gecersiz secim!\n";
        }
    }
        return 0;
}



