// Executables must have the following defined if the library contains
// doctest definitions. For builds with this disabled, e.g. code shipped to
// users, this can be left out.
#ifdef ENABLE_DOCTEST_IN_LIBRARY
#define DOCTEST_CONFIG_IMPLEMENT
#include "../tests/doctest/doctest.h"
#endif

#include <iostream>
#include <stdlib.h>
#include "Prostopadloscian.hh"
#include "lacze_do_gnuplota.hh"
#include "Scena.hh"

#include "exampleConfig.h"

#include "Dron.hh"



int main() {


    Scena Sc;                                               //Scena dla dronow
    char Opcja;                                             //Wybor w menu programu
    int i;                                                  //Zmienna do indeksowania
    int WybranyDron;                                        //Numer aktywnego dron
    int KoniecPetli=0;
    double Kat;                                             //Kat obrotu drona
    double Odleglosc;                                       //Odleglosc na jaka dron poleci

    Sc.DodajDrona(1, {20,20,0}, 0, "Dron1");                //Dodanie dronow do scemy
    Sc.DodajDrona(2, {20,100,0}, 0, "Dron2");
  
    Sc.DodajNazwePliku("../data/Dron1_Korpus.dat");         //Zapisanie nazwy plikow z brylami dronow
    Sc.DodajNazwePliku("../data/Dron1_Rotor1.dat");
    Sc.DodajNazwePliku("../data/Dron1_Rotor2.dat");
    Sc.DodajNazwePliku("../data/Dron1_Rotor3.dat");
    Sc.DodajNazwePliku("../data/Dron1_Rotor4.dat");

    Sc.DodajNazwePliku("../data/Dron2_Korpus.dat");
    Sc.DodajNazwePliku("../data/Dron2_Rotor1.dat");
    Sc.DodajNazwePliku("../data/Dron2_Rotor2.dat");
    Sc.DodajNazwePliku("../data/Dron2_Rotor3.dat");
    Sc.DodajNazwePliku("../data/Dron2_Rotor4.dat");
    
    Sc.NumerAktywnegoDrona()=1;                            //Domyslnie dron pierwszy jest aktywny

    std::cout << std::endl;                                //Wyswietlenie menu
    std::cout << "Polozenie aktywnego drona (x,y): ";
    std::cout << Sc.AktywnyDron().WspolPolozenia()[0];
    std::cout << " ";
    std::cout << Sc.AktywnyDron().WspolPolozenia()[1];
    std::cout << std::endl << std::endl;
    std::cout << "a - wybierz aktywnego drona" << std::endl;
    std::cout << "p - zadaj parametry przelotu" << std::endl;
    std::cout << "o - zadaj parametry lotu po okregu" << std::endl;
    std::cout << "m - wyswietl menu" << std::endl;
    std::cout << std::endl << "k - koniec programu"<< std::endl;
    
    while(1)
      {
        std::cout << std::endl << "Aktualna ilosc wektorow: " << Wektor3D::WezIloscAktualna() << std::endl;
        std::cout << "Ogolna Ilosc wektorow: " << Wektor3D::WezIloscOgolna() << std::endl;
        std::cout << std::endl << "Twoj wybor (m - menu) -> ";
        std::cin >> Opcja;
        std::cin.ignore(100000,'\n');
        switch(Opcja)
          {
          case 'a':                                       //Wybor aktywnego drona
            {
            std::cout << std::endl << "Wybor aktywnego drona" << std::endl << std::endl;
            for(i=0; i< ILOSC_DRONOW; i++)
              {
                std::cout << i+1 << " - Polozenie (x,y): " << Sc.PolozenieDrona(i+1)[0]  << " "<< Sc.PolozenieDrona(i+1)[1];
                if((i+1)== Sc.NumerAktywnegoDrona())
                  {
                  std::cout << "  <-- Aktywny Dron"<<std::endl<<std::endl;
                  }
                else
                  {
                  std::cout << std::endl <<std::endl;
                  }
              }
              KoniecPetli=0;
              while(!KoniecPetli)
                {
                std::cout << "Wybierz numer drona: ";
                std::cin >> WybranyDron;
                std::cin.ignore(100000,'\n');
                if(WybranyDron <=0 || WybranyDron>ILOSC_DRONOW)
                  {
                  std::cout << "Zly numer drona. Sprobuj ponownie" << std::endl;
                  }
                else
                  {
                  Sc.NumerAktywnegoDrona()=WybranyDron;
                  KoniecPetli=1;
                  }
                }
                std::cout << std::endl;                                //Polozenia aktywnego drona
                std::cout << "Polozenie aktywnego drona (x,y): ";
                std::cout << Sc.AktywnyDron().WspolPolozenia()[0];
                std::cout << " ";
                std::cout << Sc.AktywnyDron().WspolPolozenia()[1];
                std::cout << std::endl << std::endl;
              break;
            }
          case 'p':                                       //Przelot drona
            {
            std::cout << std::endl << "Podaj kierunek lotu (Kat):";
            std::cin >> Kat;
            std::cin.ignore(100000,'\n');
            std::cout << "Podaj odleglosc lotu: ";
            std::cin >> Odleglosc;
            std::cin.ignore(100000,'\n');
            std::cout << std::endl;

            while(Kat<=-360 || Kat>=360)            //Usuniecie okresow kata
              {
              if(Kat<=-360)
                {
                Kat+=360;
                }
              if(Kat>=360)
                {
                Kat-=360;
                }    
              }
            Sc.PrzemiescDrona(Odleglosc, Kat);
            break;
            }
          case 'o':                                       //Przelot drona
            {
            std::cout << "Podaj promien okregu po ktorym ma przeleciec dron: ";
            std::cin >> Odleglosc;
            std::cin.ignore(100000,'\n');
            std::cout << std::endl;

            Sc.RuchPoOkregu(Odleglosc);
            break;
            }
          case 'm':
            {
            std::cout << std::endl << std::endl;
            std::cout << "a - wybierz aktywnego drona" << std::endl;
            std::cout << "p - zadaj parametry przelotu" << std::endl;
            std::cout << "o - zadaj parametry lotu po okregu" << std::endl;
            std::cout << "m - wyswietl menu" << std::endl;
            std::cout << std::endl << "k - koniec programu"<< std::endl << std::endl;
            break;
            }
          case 'k':
            {
            std::cout << std::endl << "Koniec Programu" <<std::endl;
            return 0;
            }
          default:
            {
            std::cout << std::endl << "Nieznana opcja" << std::endl;
            }
          }
      }










return 0;
}
