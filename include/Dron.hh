#ifndef DRON_HH
#define DRON_HH


#include <string>

#include "Prostopadloscian.hh"
#include "Graniastoslup.hh"
#include "Wektor3D.hh"




/*!
 *\file 
 *\brief Definicja klasy dron.
 */

/*!
 * Klasa reprezentucje dron. Dron sklada sie z korpusu reprezentowanego przez
 * klase prostopadloscian  oraz z 4 rotorow reprezentowanych przez klase graniastoslup.
 * Dronem mozna manpiulowac, dron moze sie wznosic oraz opadac, obracac sie oraz
 * przelatywac pewna odleglosc. Dodatkowo dron moze obracac swoimi rotorami.
 *
 */
class Dron{

/*!
 *\brief Korpus drona
 * Atrybut reprezentuje korpus drona, bedący instancja klasy prostopadloscian.
 */
Prostopadloscian  Korpus;

/*!
 *\brief Korpus drona
 * Atrybut reprezentuje rotory drona w formie tablicy 4 graniastoslupow
 * prawidlowych szeciokatnych, bedacych instancja klasy Graniastoslup.
 */
Graniastoslup Rotor[4];

/*!
 *\brief Kat orientacji
 * Atrybut reprezentuje kat orientacji drona, wzgledem wlasnej osi Z.
 */
double KatOrientacji;

/*!
 *\brief Wspolrzedne polozenia
 * Atrybut reprezentuje wspolrzedne polozenia drona.
 * Za wspolrzedne polozenia, przyjmuje sie srodek podstawy korpusu.
 */
Wektor3D Polozenie;

/*!
 *\brief Metoda transformujaca drona do ukladu wspolrzednych korpusu.
 */
void TransformujDoUkladuRodzica();

/*!
 *\brief Metoda transformujaca drona do globalnego ukladu wspolrzednych
 */
void TransformujDoUkladuGlobalnego();

/*!
 *\brief Metoda oblicza wspolrzedne polozenia drona, na podstawie
 * wierzcholkow podstawy korpusu.
 */
void ObliczPolozenie();

public:

/*!
 *\brief Metoda uzyskujaca wektor3D reprezentujacy wspolrzedne polozenia drona.
 */
Wektor3D WspolPolozenia()const;

/*!
 *\brief Metoda uzyskujaca dostep do wektora3D reprezentujacego
 * wspolrzedne polozenia drona.
 */
Wektor3D& WspolPolozenia();

/*!
 *\brief Metoda uzyskujaca kat orientacji drona.
 */
double Orientacja()const;

/*!
 *\brief Metoda uzyskujaca dostep do katu orientacji drona.
 */
double& Orientacja();

/*!
 *\brief Konstruktor bezparametryczny.
 */
Dron();

/*!
 *\brief Konstruktor parametryczny.
 */
Dron(Wektor3D WspolPolozenie,double Kat, std::string Nazwa);

/*!
 *\brief Metoda zapisujaca wspolrzedne korpusu i rotorow do plikow z ich brylami.
 */
void ZapiszBryly();

/*!
 *\brief Metoda obracajaca dron o zadany kat wzgledem wlasnej osi Z.
 */
void Obrot(double Kat);

/*!
 *\brief Metoda podnoszaca dron na dana wysokosc.
 */
void Wzniesienie(double Wysokosc);

/*!
 *\brief Metoda opuszczajaca drona z danej wysokosci.
 */
void Opadanie(double Wysokosc);

/*!
 *\brief Metoda obracajaca wybrany rotor o zadany kat wzgledem wlasnej
 * osi Z rotora.
 */
void ObrotRotora(int Indeks, double Kat);

/*!
 *\brief Metoda przemieszczajaca dron o zadana odleglosc w przod w zaleznosci od katu orientacji.
 */
void Przemieszczenie(double Odleglosc);

/*!
 *\brief Metoda zastepujaca bryly drona brylami wzorcowymi (odpowiednio przemieszczonymi
 * i obroconymi).
 */
void UzyjWzorca();

};










#endif