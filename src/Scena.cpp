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
 *\brief Metoda rysujaca trase przelotu drona.
 * Metoda rysuje trase polegajaca na podniesieniu sie drona,
 * obrocie i przelocie o zadana odleglosc pod zadanym katem,
 * a nastepnie opuszczeniu na plaszczyzne.
 * \param[in] Odlegosc - Dlugosc przelotu drona.
 * \param[in] Kat - kat obrotu drona.
 * \retval True, jezeli uda sie zapisac trase do pliku.
 * \retval False, jezeli nie uda sie zapisaac trase do pliku.
 */
bool Scena::RysujTrase(double Odleglosc, double Kat)
    {
    Wektor3D PunktDocelowy = MacierzObrotu(((*this).AktywnyDron().Orientacja()+Kat), 'z') * Wektor3D{Odleglosc,0,0};     //Obliczenie punktu koncowego trasy
    PunktDocelowy += (*this).AktywnyDron().WspolPolozenia();
    std::ofstream  StrmPlikowy;
    StrmPlikowy.open("../data/TrasaPrzelotu.dat");
    if (!StrmPlikowy.is_open())  
        {
        std::cerr << "Operacja otwarcia do zapisu " << "TrasaPrzelotu.dat" << std::endl << " nie powiodla sie." << std::endl;
        return false;
        }
    
    StrmPlikowy << (*this).AktywnyDron().WspolPolozenia() << std::endl;
    StrmPlikowy << ((*this).AktywnyDron().WspolPolozenia() + Wektor3D{0,0,60}) << std::endl;
    StrmPlikowy << (PunktDocelowy + Wektor3D{0,0,60}) << std::endl;
    StrmPlikowy << PunktDocelowy << std::endl;    
    
    StrmPlikowy.close();

    Lacze.DodajNazwePliku("../data/TrasaPrzelotu.dat");
    Lacze.Rysuj();


    return true;
    }

/*!
 *\brief Metoda realizuje przelot aktywnego drona.
 * Jego przemieszenie odbywa sie w sposob animowany.
 * Dron podnosi sie, obraca o odpowiedni kat, przelatuje
 * o zadana odleglosc (Podczas przelotu jego rotory odpowiednio
 * wiruja), a na koniec opuszcza sie na plaszczyzne.
 * \param[in] Odlegosc - Dlugosc przelotu drona.
 * \param[in] Kat - kat obrotu drona.
 * \retval True, jezeli operacja wykona sie poprawnie
 * \retval False, jezeli podczas operacji wystapia bledy
 */
bool Scena::PrzemiescDrona(double Odleglosc, double Kat)
    {
        int i=0;
        std::cout <<std::endl << "Rysowanie trasy..." << std::endl;     //Rysowanie trasy
        if(!(*this).RysujTrase(Odleglosc, Kat))
            {
            throw std::runtime_error("Blad zapisu trasy");
            return false;
            }
        usleep(3000000);

        std::cout << std::endl << "Podnoszonie drona..." << std::endl;  //Podnoszenie drona
        for(i=0; i<60; i++)
            {
            (*this).AktywnyDron().Wzniesienie(1);
            (*this).AktywnyDron().ObrotRotora(0,10);
            (*this).AktywnyDron().ObrotRotora(1,-10);
            (*this).AktywnyDron().ObrotRotora(2,-10);
            (*this).AktywnyDron().ObrotRotora(3,10);
            if(!(*this).AktywnyDron().ZapiszBryly())
                {
                return false;
                }
            Lacze.Rysuj();
            usleep(40000);
            }
        if(!(*this).AktywnyDron().UzyjWzorca())
            {
            return false;
            }


        std::cout << std::endl << "Obrot drona..."  << std::endl;       //Obrot drona;
        for(i=0; i<abs(Kat); i++)
            {
            if(Kat>0)
                {
                (*this).AktywnyDron().Obrot(1);
                }
            else
                {
                (*this).AktywnyDron().Obrot(-1);
                }
            (*this).AktywnyDron().ObrotRotora(0,10);
            (*this).AktywnyDron().ObrotRotora(1,-10);
            (*this).AktywnyDron().ObrotRotora(2,-10);
            (*this).AktywnyDron().ObrotRotora(3,10);
            if(!(*this).AktywnyDron().ZapiszBryly())
                {
                return false;
                }
            Lacze.Rysuj();
            usleep(40000);
            }
        if(!(*this).AktywnyDron().UzyjWzorca())
            {
            return false;
            }

        std::cout << std::endl << "Lot Drona..."  << std::endl;       //Lot drona;
        for(i=0; i<Odleglosc; i++)
            {
            (*this).AktywnyDron().Przemieszczenie(1);
            (*this).AktywnyDron().ObrotRotora(0,10);
            (*this).AktywnyDron().ObrotRotora(1,-10);
            (*this).AktywnyDron().ObrotRotora(2,-10);
            (*this).AktywnyDron().ObrotRotora(3,10);
            if(!(*this).AktywnyDron().ZapiszBryly())
                {
                return false;
                }
            Lacze.Rysuj();
            usleep(40000);
            }
        if(!(*this).AktywnyDron().UzyjWzorca())
            {
            return false;
            }

        std::cout << std::endl << "Opadanie drona..." << std::endl;  //Opadanie
        for(i=0; i<60; i++)
            {
            (*this).AktywnyDron().Opadanie(1);
            (*this).AktywnyDron().ObrotRotora(0,10);
            (*this).AktywnyDron().ObrotRotora(1,-10);
            (*this).AktywnyDron().ObrotRotora(2,-10);
            (*this).AktywnyDron().ObrotRotora(3,10);
            if(!(*this).AktywnyDron().ZapiszBryly())
                {
                return false;
                }
            Lacze.Rysuj();
            usleep(40000);
            }
        if(!(*this).AktywnyDron().UzyjWzorca())
            {
            return false;
            }

        std::cout<< std::endl << "Usuwanie trasy..." << std::endl;     //Usuwanie trasy
        Lacze.UsunOstatniaNazwe();
        Lacze.Rysuj();
        usleep(3000000);

        return true;
    }

