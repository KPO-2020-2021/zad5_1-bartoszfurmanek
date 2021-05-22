#ifndef SCENA_HH
#define SCENA_HH

#include "Dron.hh"
#include "lacze_do_gnuplota.hh"

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
 *\brief Numer aktywnego drona.
 *Zmienna informuje o numerze aktywnego drona
 */
 int NrAktywnegoDrona;

 public:

/*!
 *\brief Konstruktor bezparametryczny sceny.
 */
 Scena();

/*!
 *\brief Metoda dodajaca drona do sceny.
 */
 void DodajDrona(int NrDrona, Wektor3D Polozenie, double Kat, std::string NazwaDrona);

/*!
 *\brief Metoda dodajaca do lacza gnuplot nazwe pliku z rysowana bryla.
 */
 bool DodajNazwePliku(const char *NazwaPliku);

/*!
 *\brief Metoda uzyskujaca polozenie wybranego drona.
 */
 Wektor3D PolozenieDrona(int NrDrona)const;

/*!
 *\brief Metoda uzyskujaca numer aktywnego drona.
 */
 int NumerAktywnegoDrona()const;

/*!
 *\brief Metoda uzyskujaca dostep do numeru aktywnego drona.
 */
 int& NumerAktywnegoDrona();

/*!
 *\brief Metoda uzyskujaca dostep do aktywnego drona.
 */
 Dron& AktywnyDron();

/*!
 *\brief Metoda wyswietlajaca w sposob aniomowany obrot aktynwego drona o zadany kat,
 * oraz jego przelot o zadana odleglosc.
 */
 bool PrzemiescDrona(double Odleglosc, double Kat);

/*!
 *\brief Metoda wyswietlajaca w sposob aniomowany ruchh po okregu aktywnego drona.
 */
 bool RuchPoOkregu(double Promien);
 };








#endif