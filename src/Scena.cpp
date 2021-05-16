#include "Scena.hh"

/*!
 *\file
 *\brief Definicja metod klasy Scena
 */

Scena::Scena()
{
    Lacze.DodajNazwePliku("../BrylyWzorcowe/Plaszczyzna.dat",PzG::RR_Ciagly,2);
    Lacze.ZmienTrybRys(PzG::TR_3D);
    Lacze.UstawZakresY(0,200);
    Lacze.UstawZakresX(0,200);
    Lacze.UstawZakresZ(0,120);
}

void Scena::DodajDrona(int NrDrona, Wektor3D Polozenie, double Kat, std::string NazwaDrona)
{
    if(NrDrona <= 0 || NrDrona > ILOSC_DRONOW)
        {
        throw std::runtime_error("Blad: Zly numer drona");
        }
    TabDronow[NrDrona-1]=Dron(Polozenie, Kat, NazwaDrona);
    TabDronow[NrDrona-1].ZapiszBryly();     
}

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

Wektor3D Scena::PolozenieDrona(int NrDrona)const
{
    if(NrDrona <= 0 || NrDrona > ILOSC_DRONOW)
    {
    throw std::runtime_error("Blad: Zly numer drona");
    }  

    return TabDronow[NrDrona-1].WspolPolozenia();
}


int Scena::NumerAktywnegoDrona()const
{
    return NrAktywnegoDrona;
}

int& Scena::NumerAktywnegoDrona()
{
    return NrAktywnegoDrona;
}

Dron& Scena::AktywnyDron()
{
    return TabDronow[NrAktywnegoDrona-1];
}

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

bool Scena::PrzemiescDrona(double Odleglosc, double Kat)
    {
        int i=0;
        std::cout <<std::endl << "Rysowanie trasy..." << std::endl;     //Rysowanie trasy
        (*this).RysujTrase(Odleglosc, Kat);
        usleep(3000000);

        std::cout << std::endl << "Podnoszonie drona..." << std::endl;  //Podnoszenie drona
        for(i=0; i<60; i++)
            {
            (*this).AktywnyDron().Wzniesienie(1);
            (*this).AktywnyDron().ObrotRotora(0,10);
            (*this).AktywnyDron().ObrotRotora(1,-10);
            (*this).AktywnyDron().ObrotRotora(2,-10);
            (*this).AktywnyDron().ObrotRotora(3,10);
            (*this).AktywnyDron().ZapiszBryly();
            Lacze.Rysuj();
            usleep(40000);
            }
        (*this).AktywnyDron().UzyjWzorca();


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
            (*this).AktywnyDron().ZapiszBryly();
            Lacze.Rysuj();
            usleep(40000);
            }
        (*this).AktywnyDron().UzyjWzorca();

        std::cout << std::endl << "Lot Drona..."  << std::endl;       //Lot drona;
        for(i=0; i<Odleglosc; i++)
            {
            (*this).AktywnyDron().Przemieszczenie(1);
            (*this).AktywnyDron().ObrotRotora(0,10);
            (*this).AktywnyDron().ObrotRotora(1,-10);
            (*this).AktywnyDron().ObrotRotora(2,-10);
            (*this).AktywnyDron().ObrotRotora(3,10);
            (*this).AktywnyDron().ZapiszBryly();
            Lacze.Rysuj();
            usleep(40000);
            }
        (*this).AktywnyDron().UzyjWzorca();

        std::cout << std::endl << "Opadanie drona..." << std::endl;  //Opadanie
        for(i=0; i<60; i++)
            {
            (*this).AktywnyDron().Opadanie(1);
            (*this).AktywnyDron().ObrotRotora(0,10);
            (*this).AktywnyDron().ObrotRotora(1,-10);
            (*this).AktywnyDron().ObrotRotora(2,-10);
            (*this).AktywnyDron().ObrotRotora(3,10);
            (*this).AktywnyDron().ZapiszBryly();
            Lacze.Rysuj();
            usleep(40000);
            }
        (*this).AktywnyDron().UzyjWzorca();

        std::cout<< std::endl << "Usuwanie trasy..." << std::endl;     //Usuwanie trasy
        Lacze.UsunOstatniaNazwe();
        Lacze.Rysuj();
        usleep(3000000);

        return true;
    }

