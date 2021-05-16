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
 * klase prostopadloscian  oraz z 4 rotorow repreznowanych przez klase graniastoslup.
 *
 */
class Dron{

/*!
 *\brief Korpus drona
 *
 * Atrybut reprezentuje korpus drona, bedący instancja klasy prostopadloscian.
 */
Prostopadloscian  Korpus;

Graniastoslup Rotor[4];

double KatOrientacji;

Wektor3D Polozenie;

public:

Wektor3D WspolPolozenia()const;

Wektor3D& WspolPolozenia();

double Orientacja()const;

double& Orientacja();

void ObliczPolozenie();

Dron();

Dron(Wektor3D WspolPolozenie,double Kat, std::string Nazwa);

void ZapiszBryly();

void TransformujDoUkladuRodzica();

void TransformujDoUkladuGlobalnego();

void Obrot(double Kat);

void Wzniesienie(double Wysokosc);

void Opadanie(double Wysokosc);

void ObrotRotora(int Indeks, double Kat);

void Przemieszczenie(double Odleglosc);

void UzyjWzorca();

};










#endif