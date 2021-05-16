#ifndef PROSTOPADLOSCIAN_HH
#define PROSTOPADLOSCIAN_HH

#include <iostream>
#include "Wektor3D.hh"
#include "Wektor.hh"
#include "Macierz3x3.hh"
#include "Macierz.hh"
#include <tgmath.h>
#include <math.h>
#include <iomanip>
#include <fstream>



/*!
 *\file
 *\brief Definicja klasy Prostopadloscian.
 */

/*!
 * \brief Klasa Prostopadloscian.
 *
 * Klasa reprezentucja prostopadlocian. Jego wierzcholki sa prezentowane przez
 * tablice wektorow 3D, gdzie jeden wektor to dany wierzcholek. prostopadloscian
 * mozna przesuwac oraz obracac. Kazdy prostopadloscian posiada  plik ze wspolrzednymi bryly,
 * oraz ze wspolrzednymi bryly wzorcowej.
 */
class Prostopadloscian {

/*!
 * \brief Wierzcholki
 *
 * Atrybut modeluje 8 wierzcholkow prostopadloscianu oraz 8 dodatkowych
 * punktow, ktore sluza do rysowania scian prostopadloscianu
 * w gnuplocie. Wierzcholki i punkty sa przedstawione w formie tablicy
 * wektorow3D. Elementy o indeksach 1,2,5,6,9,10,13,14 reczywistymi wierzcholkami
 * prostopadloscianu, pozostale elemnty to punkty dodatkowe
 *
 */
  Wektor3D Wierzcholek[16];

/*!
 * \brief Polozenie
 *
 * Atrybut modeluje wspolrzedne polozenia Prostopadloscianu.
 * Za wspolrzedne polozenia przyjmujemy srodek podstawy danego Prostopadloscianu.
 *
 */
  Wektor3D Polozenie;

/*!
 * \brief Kat orientacji
 *
 * Atrybut modeluje kat orientacyjny prostopadoscianu
 *
 */
  double KatOrientacji;

/*!
 * \brief Nazwa pliku z rysowanym prostopadloscianem
 *
 * Zmienna pamietajaca nazwe pliku, ktory przechowuje wspolrzedne prostopadloscianu
 */
  std::string NazwaPlikuBryla;

  public:

/*!
 * \brief Indeksowanie wierzcholkow prostopadloscianu.
 */
  Wektor3D operator[](int Indeks)const;

/*!
 * \brief Indeksowanie wierzcholkow prostopadloscianu.
 */
  Wektor3D& operator[](int Indeks);

/*!
 * \brief Uzyskiwanie wspolrzednych polozenia prostopadloscianu.
 */
  Wektor3D WspolPolozenia()const;

/*!
 * \brief Uzyskiwanie wspolrzednych polozenia prostopadloscianu.
 */
  Wektor3D& WspolPolozenia();

/*!
 * \brief Uzyskiwanie katu orientacji prostopadloscianu.
 */
  double Orientacja()const;

/*!
 * \brief Uzyskiwanie katu orientacji polozenia prostopadloscianu.
 */
  double& Orientacja();


/*!
 * \brief Obliczenie wspolrzednych polozenia prostopadloscianu.
 */
  void ObliczPolozenie();

/*!
 * \brief Konstruktor bezparametryczny.
 */
  Prostopadloscian();

/*!
 * \brief Konstruktor parametryczny.
 */
  Prostopadloscian(Wektor3D WspolPolozenia, double Kat, std::string NazwaBryly);

/*!
 * \brief Przeciazenie operatora porownania dla prostopadlocianu.
 */
  bool operator ==(Prostopadloscian Pr)const;

/*!
 * \brief Metoda sluzaca do opracania prostopadloscianu o zadany kat wokol wybranej osi.
 */
  Prostopadloscian& Obrot(double Kat, char Os);

/*!
 * \brief Metoda sluzaca do przesuwania prostopadlosianu o zadany wektor.
 */
  Prostopadloscian& Translacja(Wektor3D Wektor);

/*!
 * \brief Metoda sprowadzajaca prostopadloscian do wlasnego ukladu wspolrzednych.
 */
  void TransformujDoUkladuRodzica();

/*!
 * \brief Metoda sprowadzajaca prostopadloscian do globalnego ukladu wspolrzednych.
 */
  void TransformujDoUkladuGlobalnego();

/*!
 *\brief Zapis wspolrzednych wiercholkow do pliku.
 */
  bool ZapisWspolrzednychDoPliku(const std::string sNazwaPliku)const;

/*!
 * \brief Zapis wspolrzednych prostopadloscianu do strumienia.
 */
  void ZapisWspolrzednychDoStrumienia(std::ostream &StrmWy)const;

/*!
 *\brief Odczyt wspolrzednych wiercholkow do pliku.
 */
  bool OdczytWspolrzednychDoPliku(const std::string sNazwaPliku);

/*!
 * \brief Odczyt wspolrzednych prostopadloscianu do strumienia.
 */
  void OdczytWspolrzednychDoStrumienia(std::istream &StrmWej);

/*!
 * \brief Metoda zapisuje wspolrzedne prostopadloscianu do pliku
 */
  void ZapiszBryle()const;

/*!
 * \brief Metoda odczytuje wspolrzedne prostopadloscianu z pliku ze wzorcem prostopadloscianu.
 */
  void OdczytajBryleWzorcowa();

  void UzyjWzorca();


};

/*!
 * \brief Metoda sluzaca do przekazywania do strumienia wierzcholkow prostopadlocianu.
 */
std::ostream& operator << (std::ostream &Strm, const Prostopadloscian &Pr);





#endif
