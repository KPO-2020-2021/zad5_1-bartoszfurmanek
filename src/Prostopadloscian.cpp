#include "Prostopadloscian.hh"

#define MIN_ROZNICA 0.001

/*!
 *\file
 *\brief Definicja metod klasy Prostopadloscian.
 */


/*!
 * \brief Metoda służąca do indeksowania prostopadloscianu.
 * Argumenty:
 *   \param[in] Indeks - indeks zadanego wierzcholka prostopadloscianu.
 * Zwraca:
 *   \retval Wektor3D reprezentujacy dany wierzcholek prostopadloscianu,
 */
Wektor3D Prostopadloscian::operator [](int Indeks)const
{
    if(Indeks >= 16)
        {
        throw std::runtime_error("Blad: Zly indeks");
        }
    
    return Wierzcholek[Indeks];
}

/*!
 * \brief Metoda służąca do indeksowania prostopadloscianu.
 * Argumenty:
 *   \param[in] Indeks - indeks zadanego wierzcholka prostopadloscianu.
 * Zwraca:
 *   \retval Wektor3D reprezentujacy dany wierzcholek prostopadloscianu,
 */
Wektor3D& Prostopadloscian::operator [](int Indeks)
{
    if(Indeks >= 16)
        {
        throw std::runtime_error("Blad: Zly indeks");
        }
    
    return Wierzcholek[Indeks];
}

/*!
 * \brief Uzyskiwanie wspolrzednych polozenia prostopadloscianu.
 * Zwraca:
 *  \retval Wektor3D reprezentujacy polozenie prostopadloscianu.
 */
  Wektor3D Prostopadloscian::WspolPolozenia()const
  {
      return Polozenie;
  }

/*!
 * \brief Uzyskiwanie wspolrzednych polozenia prostopadloscianu.
 * Zwraca:
 *  \retval referencja do Wektora3D reprezentującego polozenie prostopadloscianu.
 */
  Wektor3D& Prostopadloscian::WspolPolozenia()
  {
      return Polozenie;
  }

/*!
 * \brief Uzyskiwanie katu orientacji prostopadloscianu.
 * Zwraca:
 *  \retval Wartosc kata orientacji prostopadloscianu.
 */
  double Prostopadloscian::Orientacja()const
  {
      return KatOrientacji;
  }

/*!
 * \brief Uzyskiwanie katu orientacji polozenia prostopadloscianu.
 * Zwraca:
 *  \retval referencja do katu orientacji prostopadloscianu.
 */
  double& Prostopadloscian::Orientacja()
  {
      return KatOrientacji;
  }


/*!
 * \brief Obliczenie wspolrzednych polozenia prostopadloscianu.
 * Metoda wylicza wspolrzedne polozenia prostopadloscianu na podstawie
 * wiercholkow jego podstawy. Za wspolrzednie polozenia przyjmuje sie
 * srodek podstawy prostopadloscianu.
 */
  void Prostopadloscian::ObliczPolozenie()
  {
      Polozenie = Wierzcholek[9];
      Polozenie += Wierzcholek[10];
      Polozenie += Wierzcholek[13];
      Polozenie += Wierzcholek[14];
      Polozenie = 0.25 * Polozenie;

  }

/*!
 *\brief Konstruktor bezparamateryczny prostopadloscianu.
 */
Prostopadloscian::Prostopadloscian()
{
    KatOrientacji=0;
    Polozenie={0,0,0};
    for(int i=0; i<16; i++)
        {
        Wierzcholek[i]={0,0,0};
        }
}

/*!
 *\brief Konstruktor parametryczny prostopadloscianu.
 *Argumenty:
 *  \param[in] WspolPolozenia - Wspolrzedne polozenia srodka prostopadloscianu
 *  \param[in] Kat - Kat orientacji prostopadloscianu.
 *  \param[in] NazwaBryly - Nazwa prostopadloscianu.
 */
Prostopadloscian::Prostopadloscian(Wektor3D WspolPolozenia, double Kat, std::string NazwaBryly)
{
(*this).OdczytajBryleWzorcowa();
(*this).Obrot(Kat, 'z');
(*this).Translacja(WspolPolozenia);
KatOrientacji=Kat;
while(KatOrientacji<= -360 || KatOrientacji >= 360)
  {
    if(KatOrientacji<= -360)
    {
      KatOrientacji +=360;
    }
    if(KatOrientacji>= 360)
    {
      KatOrientacji -=360;
    }    
  }
Polozenie=WspolPolozenia;
NazwaPlikuBryla=NazwaBryly + ".dat";

}


/*!
 * \brief Metoda służąca do porownywania prostopadloscianow z dokladnoscia do 0,001.
 * Argumenty:
 *  \param[in] Pr - Prostopadloscian odniesienia.
 * Zwraca:
 *   \retval True, jeżeli prostopadlosciany są takie same.
 *   \retval False jeżeli prostopadlosciany sie roznia
 */
bool Prostopadloscian::operator ==(Prostopadloscian Pr)const
{
for(int i=0; i<16; i++)
    {
    if(!((*this)[i]==Pr[i]))
        {return false;}
    }
return true;
}

/*!
 * \brief Metoda służąca do obrotu prostopadloscianu o zadany kat wokol osi x,y,z.
 * UWAGA: Metoda nie sprawdza czy podano poprawna os (mozliwe opcje to x,y oraz z).
 * Argumenty:
 *  \param[in] Kat - Kat obrotu.
 *  \param[in] Os - Os obrotu.
 * Zwraca:
 *   \retval Obrocony prostopadloscian.
 */
Prostopadloscian& Prostopadloscian::Obrot(double Kat, char Os)
{
    for(int i=0; i<16; i++)
    {
    (*this)[i] = MacierzObrotu(Kat, Os) * (*this)[i];  //Wymnożenie każdego wierzcholka przez macierz obrotu
    }               
    return *this;
}

/*!
 * \brief Metoda służąca do przesuniecie prostopadloscianu o zadany wektor
 * Argumenty:
 *  \param[in] Wektor - Wektor przesuniecia.
 * Zwraca:
 *   \retval Przesuniety prostopadloscian.
 */
Prostopadloscian& Prostopadloscian::Translacja(Wektor3D Wektor)
{
    for(int i=0; i<16; i++)
    {
    (*this)[i] += Wektor;
    }
    return (*this);
}

/*!
 * \brief Metoda sprowadzajaca prostopadloscian do wlasnego ukladu wspolrzednych.
 */
  void Prostopadloscian::TransformujDoUkladuRodzica()
  {
    (*this).Translacja((-1*Polozenie));
    (*this).Obrot((KatOrientacji*-1),'z');

  }

/*!
 * \brief Metoda sprowadzajaca prostopadloscian do globalnego ukladu wspolrzednych.
 */
  void Prostopadloscian::TransformujDoUkladuGlobalnego()
  {
    (*this).Obrot(KatOrientacji,'z');
    (*this).Translacja((Polozenie));

  }


/*!
 * \brief Zapis wspolrzednych prostopadloscianu do strumienia.
 * Metoda służy do zapisu wspolrzednych wierzcholków prostopadloscianu do danego strumienia,
 * w celu zapisu go do pliku, ktory bedzie rysowac gnuplot.
 * przy wykonywaniu rysunku.
 * Argumenty:
 *  \param[in] StrmWy - Strumien na ktory wierzcholki maja zostac wypisane.
 */
void Prostopadloscian::ZapisWspolrzednychDoStrumienia(std::ostream &StrmWy)const
{
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << Wierzcholek[0] << std::endl;
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << Wierzcholek[1] << std::endl;
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << Wierzcholek[2] << std::endl;
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << Wierzcholek[3] << std::endl;
  StrmWy << std::endl;
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << Wierzcholek[4] << std::endl;
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << Wierzcholek[5] << std::endl;
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << Wierzcholek[6] << std::endl;
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << Wierzcholek[7] << std::endl;
  StrmWy << std::endl;
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << Wierzcholek[8] << std::endl;
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << Wierzcholek[9] << std::endl;
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << Wierzcholek[10] << std::endl;
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << Wierzcholek[11] << std::endl;
  StrmWy << std::endl;
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << Wierzcholek[12] << std::endl;
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << Wierzcholek[13] << std::endl;
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << Wierzcholek[14] << std::endl;
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << Wierzcholek[15] << std::endl;
  StrmWy << std::endl;
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << Wierzcholek[0] << std::endl;
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << Wierzcholek[1] << std::endl;
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << Wierzcholek[2] << std::endl;
  StrmWy << std::setw(16) << std::fixed << std::setprecision(10) << Wierzcholek[3] << std::endl;

}



/*!
 *\brief Zapis wspolrzednych wiercholkow do pliku.
 * Funkcja służy do zapisu wspolrzednych prostopadloscianu od pliku w celu
 * narysowania i wyswietlenia go przez gnu-plot.
 * Argumenty: 
 *  \param[in] sNazwaPliku - Nazwa pliku ktory ma przechowywac informacje o wierzcholkach
 * Zwraca:
 * \retval True - jeżeli zapis uda sie pomyslnie.
 * \retval False - jezeli zapis sie nie uda..
 */
bool Prostopadloscian::ZapisWspolrzednychDoPliku(const std::string sNazwaPliku)const
{
  std::ofstream  StrmPlikowy;
  StrmPlikowy.open(sNazwaPliku);
  if (!StrmPlikowy.is_open())  {
    std::cerr << "Operacja otwarcia do zapisu \"" << sNazwaPliku << "\"" << std::endl
	 << " nie powiodla sie." << std::endl;
    return false;
  }
  (*this).ZapisWspolrzednychDoStrumienia(StrmPlikowy);
  StrmPlikowy.close();
  return !StrmPlikowy.fail();
}


/*!
 * \brief Odczyt wspolrzednych wierzcholkow prostopadloscianu ze strumienia.
 * Metoda służy do odczytu wspolrzednych wierzcholków prostopadloscianu z danego strumienia.
 * Argumenty:
 *  \param[in] StrmWej - Strumien z ktorego wierzcholki maja zostac wczytane.
 */
void Prostopadloscian::OdczytWspolrzednychDoStrumienia(std::istream &StrmWej)
{
StrmWej >> Wierzcholek[0];
StrmWej >> Wierzcholek[1];
StrmWej >> Wierzcholek[2];
StrmWej >> Wierzcholek[3];

StrmWej >> Wierzcholek[4];
StrmWej >> Wierzcholek[5];
StrmWej >> Wierzcholek[6];
StrmWej >> Wierzcholek[7];

StrmWej >> Wierzcholek[8];
StrmWej >> Wierzcholek[9];
StrmWej >> Wierzcholek[10];
StrmWej >> Wierzcholek[11];

StrmWej >> Wierzcholek[12];
StrmWej >> Wierzcholek[13];
StrmWej >> Wierzcholek[14];
StrmWej >> Wierzcholek[15];
}

/*!
 *\brief Odczyt wspolrzednych wiercholkow z pliku.
 * Argumenty: 
 *  \param[in] sNazwaPliku - Nazwa pliku ktory ma przechowywac informacje o wierzcholkach
 * Zwraca:
 * \retval True - jeżeli zapis uda sie pomyslnie.
 * \retval False - jezeli zapis sie nie uda..
 */
bool Prostopadloscian::OdczytWspolrzednychDoPliku(const std::string sNazwaPliku)
{
  std::ifstream  StrmPlikowy;
  StrmPlikowy.open(sNazwaPliku);
  if (!StrmPlikowy.is_open())  {
    std::cerr << "Operacja otwarcia do odczytu \"" << sNazwaPliku << "\"" << std::endl
	 << " nie powiodla sie." << std::endl;
    return false;
  }
  (*this).OdczytWspolrzednychDoStrumienia(StrmPlikowy);
  StrmPlikowy.close();
  return !StrmPlikowy.fail();
}


/*!
 * \brief Metoda zapisuje wspolrzedne prostopadloscianu do pliku
 */
  void Prostopadloscian::ZapiszBryle()const
  {
    (*this).ZapisWspolrzednychDoPliku("../data/"+NazwaPlikuBryla);
  }


/*!
 * \brief Metoda odczytuje wspolrzedne prostopadloscianu z pliku ze wzorcem prostopadloscianu.
 */
  void Prostopadloscian::OdczytajBryleWzorcowa()
  {
    (*this).OdczytWspolrzednychDoPliku("../BrylyWzorcowe/ProstopadloscianWzorcowy.dat");
  }

  void Prostopadloscian::UzyjWzorca()
  {
    (*this).OdczytajBryleWzorcowa();
    (*this).Obrot(KatOrientacji, 'z');
    (*this).Translacja(Polozenie);
  }


/*!
 * \brief Metoda sluzaca do przekazywania do strumienia wierzcholkow prostopadlocianu.
 * Argumenty:
 *  \param[in] Strm - Strumień, na ktory wierzcholki maja zostac przekazane
 *  \param[in] Pr - Prostopadloscian, ktorego wierzcholki maja zostac przekazane
 * Zwraca:
 *  \retval Strumień na który wierzcholki zostaly wypisane
 */
std::ostream& operator << (std::ostream &Strm, const Prostopadloscian &Pr)
{
    Strm << std::setw(16) << std::fixed << std::setprecision(10) << Pr[1] << std::endl;
    Strm << std::setw(16) << std::fixed << std::setprecision(10) << Pr[2] << std::endl;
    Strm << std::setw(16) << std::fixed << std::setprecision(10) << Pr[5] << std::endl;
    Strm << std::setw(16) << std::fixed << std::setprecision(10) << Pr[6] << std::endl;
    Strm << std::setw(16) << std::fixed << std::setprecision(10) << Pr[9] << std::endl;
    Strm << std::setw(16) << std::fixed << std::setprecision(10) << Pr[10] << std::endl;
    Strm << std::setw(16) << std::fixed << std::setprecision(10) << Pr[13] << std::endl;
    Strm << std::setw(16) << std::fixed << std::setprecision(10) << Pr[14] << std::endl;

return Strm;
}

