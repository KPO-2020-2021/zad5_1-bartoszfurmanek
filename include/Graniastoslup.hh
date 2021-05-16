#ifndef GRANIASTOSLUP_HH
#define GRANIASTOSLUP_HH

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
 *\brief Definicja klasy Graniastoslup.
 */

/*!
 * \brief Klasa Graniastoslup.
 *
 * Klasa reprezentucja graniastoslup. Jego wierzcholki sa prezentowane przez
 * tablice wektorow 3D, gdzie jeden wektor to dany wierzcholek. graniastoslup
 * mozna przesuwac oraz obracac. Kazdy graniastoslup posiada 2 pliki ze wspolrzednymi bryly,
 * oraz ze wspolrzednymi bryly wzorcowej.
 */
class Graniastoslup {

/*!
 * \brief Wierzcholki
 *
 * Atrybut modeluje 12 wierzcholkow granistoslupa w formie
 * tablicy z wektorami 3D.
 *
 */
  Wektor3D Wierzcholek[24];

/*!
 * \brief Polozenie
 *
 * Atrybut modeluje wspolrzedne polozenia graniastoslupa.
 * Za wspolrzedne polozenia przyjmujemy srodek podstawy danego graniastoslupa.
 *
 */
  Wektor3D Polozenie;

/*!
 * \brief Kat orientacji
 *
 * Atrybut modeluje kat orientacyjny graniastoslupa
 *
 */
  double KatOrientacji;

/*!
 * \brief Nazwa pliku z rysowanym graniastoslupem
 *
 * Zmienna pamietajaca nazwe pliku, ktory przechowuje wspolrzedne graniastoslupa
 */
  std::string NazwaPlikuBryla;

  public:

/*!
 * \brief Indeksowanie wierzcholkow graniastoslupa.
 */
  Wektor3D operator[](int Indeks)const;

/*!
 * \brief Indeksowanie wierzcholkow graniastoslupa.
 */
  Wektor3D& operator[](int Indeks);

/*!
 * \brief Uzyskiwanie wspolrzednych polozenia graniastoslupa.
 */
  Wektor3D WspolPolozenia()const;

/*!
 * \brief Uzyskiwanie wspolrzednych polozenia graniastoslupa.
 */
  Wektor3D& WspolPolozenia();

/*!
 * \brief Uzyskiwanie katu orientacji graniastoslupa.
 */
  double Orientacja()const;

/*!
 * \brief Uzyskiwanie katu orientacji polozenia graniastoslupa.
 */
  double& Orientacja();


/*!
 * \brief Obliczenie wspolrzednych polozenia prostopadloscianu.
 */
  void ObliczPolozenie();

/*!
 * \brief Konstruktor bezparametryczny.
 */
  Graniastoslup();

/*!
 * \brief Konstruktor parametryczny.
 */
  Graniastoslup(Wektor3D WspolPolozenia, double Kat, std::string NazwaBryly);

/*!
 * \brief Przeciazenie operatora porownania dla graniastoslupa.
 */
  bool operator ==(Graniastoslup Gr)const;

/*!
 * \brief Metoda sluzaca do obracania graniastoslupa o zadany kat wokol wybranej osi.
 */
  Graniastoslup& Obrot(double Kat, char Os);

/*!
 * \brief Metoda sluzaca do przesuwania graniastoslupa o zadany wektor.
 */
  Graniastoslup& Translacja(Wektor3D Wektor);

/*!
 * \brief Metoda sprowadzajaca graniastoslup do wlasnego ukladu wspolrzednych.
 */
  void TransformujDoUkladuRodzica();

/*!
 * \brief Metoda sprowadzajaca graniastoslup do globalnego ukladu wspolrzednych.
 */
  void TransformujDoUkladuGlobalnego();

/*!
 *\brief Zapis wspolrzednych wiercholkow do pliku.
 */
  bool ZapisWspolrzednychDoPliku(const std::string sNazwaPliku)const;

/*!
 * \brief Zapis wspolrzednych  do strumienia.
 */
  void ZapisWspolrzednychDoStrumienia(std::ostream &StrmWy)const;

/*!
 *\brief Odczyt wspolrzednych wiercholkow do pliku.
 */
  bool OdczytWspolrzednychDoPliku(const std::string sNazwaPliku);

/*!
 * \brief Odczyt wspolrzednych woercholkow do strumienia.
 */
  void OdczytWspolrzednychDoStrumienia(std::istream &StrmWej);

/*!
 * \brief Metoda zapisuje wspolrzedne graniastoslupa do pliku
 */
  void ZapiszBryle()const;

/*!
 * \brief Metoda odczytuje wspolrzedne graniastloslupa z pliku ze wzorcem bryly.
 */
  void OdczytajBryleWzorcowa();

  void UzyjWzorca();


};

/*!
 * \brief Metoda sluzaca do przekazywania do strumienia wierzcholkow graniastoslupa.
 */
std::ostream& operator << (std::ostream &Strm, const Graniastoslup &Gr);





#endif
