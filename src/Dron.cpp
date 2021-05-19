#include "Dron.hh"

#include "Wektor3D.hh"

/*!
 *\file
 *\brief Definicja metod dla klasy Dron.
 */

/*!
 *\brief Metoda uzyskujaca wektor3D reprezentujacy wspolrzedne polozenia drona.
 *\retval Wektor3D reprezentujacy wspolrzedne polozenia drona.
 */
Wektor3D Dron::WspolPolozenia()const
{
    return Polozenie;
}

/*!
 *\brief Metoda uzyskujaca dostep do wektora3D reprezentujacego wspolrzedne polozenia drona.
 *\retval referencja do Wektora3D reprezentujacego wspolrzedne polozenia drona.
 */
Wektor3D& Dron::WspolPolozenia()
{
    return Polozenie;
}

/*!
 *\brief Metoda uzyskujaca kat orientacji drona.
 *\retval Wartosc kata orientacji drona.
 */
double Dron::Orientacja()const
{
    return KatOrientacji;
}

/*!
 *\brief Metoda uzyskujaca dostep do kata  orientacji drona.
 *\retval referencja do wartosci kata orientacji drona.
 */
double& Dron::Orientacja()
{
    return KatOrientacji;
}


/*!
 *\brief Metoda obliczajaca wspolrzedne polozenia korupsu drona
 * oraz jego rotortow. Za wspolrzedne polozenia calego drona 
 * przyjmuje sie polozenie jego korpusu.
 */
void Dron::ObliczPolozenie()
{
    Korpus.ObliczPolozenie();
    (*this).WspolPolozenia()=Korpus.WspolPolozenia();
    for(int i=0; i<4; i++)
    {
        Rotor[i].ObliczPolozenie();
    }
}

/*!
 *\brief Konstruktor bezparametryczny drona.
 */
Dron::Dron()
{
    Korpus = Prostopadloscian();
    Rotor[0] = Graniastoslup();
    Rotor[1] = Graniastoslup();
    Rotor[2] = Graniastoslup();
    Rotor[3] = Graniastoslup();
}

/*!
 *\brief Konstruktor parametryczny drona.
 * Rotory drona, sa tworzone na podstawie wierzcholkow jego gornej
 * podstawy.
 *\param[in] PolozenieDrona - wspolrzedne polozenia korpusu drona.
 *\param[in] Kat - kat orientacji korpusu drona.
 *\param[in] Nazwa - nazwa drona.
 */
Dron::Dron(Wektor3D PolozenieDrona,double Kat, std::string Nazwa)
{
    Korpus = Prostopadloscian(PolozenieDrona, Kat ,Nazwa + "_Korpus");
    Rotor[0] = Graniastoslup(Korpus[1], Kat, Nazwa+"_Rotor1");
    Rotor[1] = Graniastoslup(Korpus[2], Kat, Nazwa+"_Rotor2");
    Rotor[2] = Graniastoslup(Korpus[5], Kat, Nazwa+"_Rotor3");
    Rotor[3] = Graniastoslup(Korpus[6], Kat, Nazwa+"_Rotor4");
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
    (*this).ObliczPolozenie();
}
/*!
 *\brief Metoda zapisujaca korpus i rotory dron do plikow z ich brylami.
 * \retval True - jeżeli zapis uda sie pomyslnie.
 * \retval False - jezeli zapis ktorejs z bryl sie nie uda
 */
bool Dron::ZapiszBryly()const
{
    if(!Korpus.ZapiszBryle())
        {
        throw std::runtime_error("Odczyt plikow sie nie powiodl");   
        return false;
        }
    for(int i=0; i<4; i++)
        {
        if(!Rotor[i].ZapiszBryle())
            {
            throw std::runtime_error("Odczyt plikow sie nie powiodl");    
            return false;
            }
        }
    return true;
}

/*!
 *\brief Metoda transformujaca drona do ukladu wspolrzednych jego korpusu.
 */
void Dron::TransformujDoUkladuRodzica()
{
    Korpus.Translacja((-1*Polozenie));
    Rotor[0].Translacja((-1*Polozenie));
    Rotor[1].Translacja((-1*Polozenie));
    Rotor[2].Translacja((-1*Polozenie));
    Rotor[3].Translacja((-1*Polozenie));
    Korpus.Obrot((KatOrientacji*-1),'z');
    Rotor[0].Obrot((KatOrientacji*-1),'z');
    Rotor[1].Obrot((KatOrientacji*-1),'z');
    Rotor[2].Obrot((KatOrientacji*-1),'z');
    Rotor[3].Obrot((KatOrientacji*-1),'z');
}

/*!
 *\brief Metoda transformujaca drona do globalnego ukladu wspolrzednych
 */
void Dron::TransformujDoUkladuGlobalnego()
{
    Korpus.Obrot((KatOrientacji),'z');
    Rotor[0].Obrot((KatOrientacji),'z');
    Rotor[1].Obrot((KatOrientacji),'z');
    Rotor[2].Obrot((KatOrientacji),'z');
    Rotor[3].Obrot((KatOrientacji),'z');
    Korpus.Translacja((Polozenie));
    Rotor[0].Translacja((Polozenie));
    Rotor[1].Translacja((Polozenie));
    Rotor[2].Translacja((Polozenie));
    Rotor[3].Translacja((Polozenie));
}

/*!
 *\brief Metoda obraca calego drona o zadany kat wzgledem osi Z korpusu.
 * Metoda przeksztalca dron do wlasnego ukladu wspolrzednych, obraca go,
 * a nastepnie przywraca do lokalnego ukladu wspolrzednych.
 * \param[in] Kat - Kat obrotu drona.
 */
void Dron::Obrot(double Kat)
{
    (*this).TransformujDoUkladuRodzica();
    Korpus.Obrot(Kat,'z');
    Rotor[0].Obrot(Kat,'z');
    Rotor[1].Obrot(Kat,'z');
    Rotor[2].Obrot(Kat,'z');
    Rotor[3].Obrot(Kat,'z');
    (*this).TransformujDoUkladuGlobalnego();

    (*this).ObliczPolozenie();

    KatOrientacji+=Kat;
    Korpus.Orientacja()+=Kat;
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

}
/*!
 *\brief Metoda podnosi drona na dana wysokosc.
 *\param[in] Wysokosc - wysokosc na jaka drona ma zostac podniesiony
 * wzgledem jego poprzedniej wysokosci.
 */
void Dron::Wzniesienie(double Wysokosc)
{
    Wektor3D Przesuniecie{0,0,Wysokosc};
    Korpus.Translacja(Przesuniecie);
    Rotor[0].Translacja(Przesuniecie);
    Rotor[1].Translacja(Przesuniecie);
    Rotor[2].Translacja(Przesuniecie);
    Rotor[3].Translacja(Przesuniecie);

    (*this).ObliczPolozenie();
}

/*!
 *\brief Metoda opuszcza drona o dana wysokosc.
 *\param[in] Wysokosc - wysokosc o jaka drona ma zostac opuszczony
 * wzgledem jego poprzedniej wysokosci.
 */
void Dron::Opadanie(double Wysokosc)
{
    Wektor3D Przesuniecie{0,0,-Wysokosc};
    Korpus.Translacja(Przesuniecie);
    Rotor[0].Translacja(Przesuniecie);
    Rotor[1].Translacja(Przesuniecie);
    Rotor[2].Translacja(Przesuniecie);
    Rotor[3].Translacja(Przesuniecie); 

    (*this).ObliczPolozenie();
}

/*!
 *\brief Metoda obraca wygrany rotor o zadany kat wzgledem jego wlasnej osi Z.
 * Metoda najpierw sprowadza rotor do jego wlasnego ukladu wspolrzednych, po czym
 * obraca go, a nastepnie przywraca do globalnego ukladu wspolrzednych
 *\param[in] Indeks - indeks wybranego rotora.
 *\param[in] Kat - o jaki rotor ma zostac obrocony.
 */
void Dron::ObrotRotora(int Indeks, double Kat)
{
    if(Indeks >=4)
        {
        throw std::runtime_error("Blad: Zly indeks rotora");
        }

    Rotor[Indeks].TransformujDoUkladuRodzica();
    Rotor[Indeks].Obrot(Kat, 'z');
    Rotor[Indeks].TransformujDoUkladuGlobalnego();

    Rotor[Indeks].Orientacja() += Kat;
    while(Rotor[Indeks].Orientacja()<= -360 || Rotor[Indeks].Orientacja() >= 360)
    {
    if(Rotor[Indeks].Orientacja()<= -360)
        {
        Rotor[Indeks].Orientacja() +=360;
        }
    if(Rotor[Indeks].Orientacja()>= 360)
        {
        Rotor[Indeks].Orientacja() -=360;
        }    
    }

  (*this).ObliczPolozenie();

}

/*!
 *\brief Metoda przemieszcza drona od zadana odleglosc.
 * Przemieszczenie odbywa sie wzdloz prostej o takim samym kacie,
 * jak kat orientacji.
 *\param[in] Odleglosc - Dlugosc o jaka dron ma zostac przemieszczony.
 */
void Dron::Przemieszczenie(double Odleglosc)
{
    Wektor3D Przesuniecie{Odleglosc,0,0};
    Przesuniecie = MacierzObrotu(KatOrientacji, 'z') * Przesuniecie;
    Korpus.Translacja(Przesuniecie);
    Rotor[0].Translacja(Przesuniecie);
    Rotor[1].Translacja(Przesuniecie);
    Rotor[2].Translacja(Przesuniecie);
    Rotor[3].Translacja(Przesuniecie);
    (*this).ObliczPolozenie();
}
    
/*!
 *\brief Metoda zastepuje bryly drona brylami wzorcowymi,
 ktore zostaja odpowiednio przemieszczone i obroce, tak
 aby zgadzaly sie z polozeniem aktualnego drona.
 * \retval True - jeżeli oczyt uda sie pomyslnie.
 * \retval False - jezeli odczyt ktorejs z bryl sie nie uda
 */
bool Dron::UzyjWzorca()
{
    (*this).ObliczPolozenie();
    if(!Korpus.UzyjWzorca())
        {
        throw std::runtime_error("Odczyt plikow sie nie powiodl");
        return false;
        }
    for(int i=0; i<4; i++)
        {
        if(!Rotor[i].UzyjWzorca())
            {
            throw std::runtime_error("Odczyt plikow sie nie powiodl");
            return false;
            }
        }
    (*this).ZapiszBryly();
    return true;
}