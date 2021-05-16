#ifndef SCENA_HH
#define SCENA_HH

#include "Dron.hh"
#include "lacze_do_gnuplota.hh"
#include <unistd.h>

#define ILOSC_DRONOW 2

/*!
 *\file
 *\brief Plik zawiera definicje klasy Scena
 */

/*!
 *\brief Klasa scena
 *Klasa definiuje scene, po ktorej dron bedzie sie przemieszczal w
 *Gnuplocie. Scena sklada sie z dwoch dronow, oraz podloza. 
 *Klasa pozwala na animowane wyswietlanie ruchu drona 
 *na pewnej plaszczyznie.
 */
 class Scena{

/*!
 *\brief Tablica dronowa.
 *Atrybut jest tablica przechowujaca 2 obiekty klasy dron.
 */
 Dron  TabDronow[ILOSC_DRONOW];

/*!
 *\brief Lacze do gnuplota.
 *Zmienna sluzy do operowania na gnuplocie w celu wyswietlania
 *w nim sceny.
 */
 PzG::LaczeDoGNUPlota  Lacze;

/*!
 *\brief Numer aktywnego drona
 *Zmienna informuje o numerze aktywnego drona
 */
 int NrAktywnegoDrona;

 public:

 Scena();

 void DodajDrona(int NrDrona, Wektor3D Polozenie, double Kat, std::string NazwaDrona);

 bool DodajNazwePliku(const char *NazwaPliku);

 Wektor3D PolozenieDrona(int NrDrona)const;

 int NumerAktywnegoDrona()const;

 int& NumerAktywnegoDrona();

 Dron& AktywnyDron();

 bool RysujTrase(double Odleglosc, double Kat);

 bool PrzemiescDrona(double Odleglosc, double Kat);
 };








#endif