#include "Scena.hh"

/*!
 *\file
 *\brief Definicja metod klasy Scena
 */

/*!
 *\brief Konstruktor bezparametryczny sceny.
 * Konstruktor tworzy scene. Ustawia zakresy oraz tryb
 * rysowania jej lacza do gnuplota oraz dodaj do sceny
 * plaszczyzne.
 */
Scena::Scena()
{
    Lacze.DodajNazwePliku("../BrylyWzorcowe/Plaszczyzna.dat",PzG::RR_Ciagly,2);
    Lacze.ZmienTrybRys(PzG::TR_3D);
    Lacze.UstawZakresY(0,200);
    Lacze.UstawZakresX(0,200);
    Lacze.UstawZakresZ(0,120);
}

/*!
 *\brief Metoda dodajaca drona do sceny.
 * Metoda dodaje do sceny dron na pozycje o zadanym numerze.
 * UWAGA: Metoda nie dodaje nazw plikow z brylami do lacza.
 * \param[in] NrDrona - Numer w tablicy dronow, jaki tworzony dron ma przyjac.
 * \param[in] Polozenie - Wspolrzedne polozenia drona.
 * \param[in] Kat - Kat orientacji drona.
 * \param[in] NazwaDrona - Nazwa drona.
 */
void Scena::DodajDrona(int NrDrona, Wektor3D Polozenie, double Kat, std::string NazwaDrona)
{
    if(NrDrona <= 0 || NrDrona > ILOSC_DRONOW)
        {
        throw std::runtime_error("Blad: Zly numer drona");
        }
    TabDronow[NrDrona-1]=Dron(Polozenie, Kat, NazwaDrona);
    TabDronow[NrDrona-1].ZapiszBryly();     
}

/*!
 *\brief Metoda dodaje do lacza nazwe pliku, z bryla ktora ma zostac rysowana.
 *\param[in] NazwaPliku - nazwa pliku, ktora ma zostac dodana do lacza.
 */
bool Scena::DodajNazwePliku(const char *NazwaPliku)
{
    if(Lacze.DodajNazwePliku(NazwaPliku,PzG::RR_Ciagly,2))
        {
        return true;
        }
    else
        {
        return false;
        }
}

/*!
 *\brief Metoda uzyskuje wspolrzedne polozenia wybranego drona.
 *\param[in] NrDrona - Numer drona
 *\retval Wektor3D reprezentujacy wspolrzedne polozenia drona.
 */
Wektor3D Scena::PolozenieDrona(int NrDrona)const
{
    if(NrDrona <= 0 || NrDrona > ILOSC_DRONOW)
    {
    throw std::runtime_error("Blad: Zly numer drona");
    }  

    return TabDronow[NrDrona-1].WspolPolozenia();
}

/*!
 *\brief Metoda uzyskujaca numer aktywnego drona.
 *\retval - Numer aktywnego drona.
 */
int Scena::NumerAktywnegoDrona()const
{
    return NrAktywnegoDrona;
}

/*!
 *\brief Metoda uzyskujaca dostep do aktywnego drona.
 *\retval Referencja do numeru aktywnego drona.
 */
int& Scena::NumerAktywnegoDrona()
{
    return NrAktywnegoDrona;
}

/*!
 *\brief Metoda uzyskujaca dostep do aktywnego drona.
 *\retval referencja do aktywnego drona.
 */
Dron& Scena::AktywnyDron()
{
    return TabDronow[NrAktywnegoDrona-1];
}

/*!
 *\brief Metoda wyswietlajaca w sposob aniomowany obrot aktywnego drona o zadany kat,
 * oraz jego przelot o zadana odleglosc.
 * \param[in] Odleglosc - Odleglosc o jaka dron ma przeleciec.
 * \param[in] Kat - Kat o jaki dron ma sie obrocic.
 * \retval True, jezeli operacja wykona sie poprawnie
 * \retval False, jezeli podczas operacji wystapia bledy
 */
 bool Scena::PrzemiescDrona(double Odleglosc, double Kat)
 {
 if(!(*this).AktywnyDron().PrzemiescDrona(Odleglosc, Kat, Lacze))
    {
    return false;
    }
return true;
 }

/*!
 *\brief Metoda wyswietlajaca w sposob aniomowany ruch po okregu aktywnego drona.
 * \param[in] Promien - Promien okregu, po jakim dron ma sie przemieszczac.
 * \retval True, jezeli operacja wykona sie poprawnie
 * \retval False, jezeli podczas operacji wystapia bledy
 */
bool Scena::RuchPoOkregu(double Promien)
 {
 if(!(*this).AktywnyDron().RuchPoOkregu(Promien, Lacze))
    {
    return false;
    }
return true;
 }
 

