#include "Dron.hh"

#include "Wektor3D.hh"

/*!
 *\file
 *\brief Definicja metod dla klasy Dron.
 */


Wektor3D Dron::WspolPolozenia()const
{
    return Polozenie;
}

Wektor3D& Dron::WspolPolozenia()
{
    return Polozenie;
}

double Dron::Orientacja()const
{
    return KatOrientacji;
}

double& Dron::Orientacja()
{
    return KatOrientacji;
}

void Dron::ObliczPolozenie()
{
    Korpus.ObliczPolozenie();
    (*this).WspolPolozenia()=Korpus.WspolPolozenia();
    for(int i=0; i<4; i++)
    {
        Rotor[i].ObliczPolozenie();
    }
}

Dron::Dron()
{
    Korpus = Prostopadloscian();
    Rotor[0] = Graniastoslup();
    Rotor[1] = Graniastoslup();
    Rotor[2] = Graniastoslup();
    Rotor[3] = Graniastoslup();
}

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

void Dron::ZapiszBryly()
{
    Korpus.ZapiszBryle();
    Rotor[0].ZapiszBryle();
    Rotor[1].ZapiszBryle();
    Rotor[2].ZapiszBryle();
    Rotor[3].ZapiszBryle();
}

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
    

void Dron::UzyjWzorca()
{
    (*this).ObliczPolozenie();
    Korpus.UzyjWzorca();
    Rotor[0].UzyjWzorca();
    Rotor[1].UzyjWzorca();
    Rotor[2].UzyjWzorca();
    Rotor[3].UzyjWzorca();
    (*this).ZapiszBryly();
}