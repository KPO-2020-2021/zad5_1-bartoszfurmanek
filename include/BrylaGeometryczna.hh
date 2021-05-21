#ifndef BRYLAGEOMETRYCZNA_HH
#define BRYLAGEOMETRYCZNA_HH

/*!
 * \file 
 * \brief Definicja klasy BrylaGeometryczna.
 */


/*!
 * \brief Rodzaj bryly geometrycznej modelowanej przez daną klasę
 *
 *  Wartości tego typu sa identifykatorami mowiacymi jakiego typu jest
 *  dana bryla.
 */
enum TypBrylyGeometrycznej { 
      TB_Zadna              /*! Nie jest to żadna konkretna figura geometryczna */,  
      TB_Prostopadloscian    /*! Figura geometryczna jest kawadratem */,
      TB_Graniastoslup      /*! Figura geometryczna jest kołem */
   };


/*!
 * \brief Klasa BrylaGeometryczna
 *  Klasa modeluje pojęcie bryly geometrycznej.
 *  Klasa jest baza dla dziedziczenia klas Prostopadloscian
 *  i Graniastoslup. Kazda bryla posiada nazwe bryly wzorcowej
 *  oraz bryly finalnej. Dodatkowo kazda bryla posiada identyfikator
 *  mowiacy jakiego typu bryla jest.
 */
class BrylaGeometryczna {

  private:
/*!
 * \brief Identyfikator rodzaju figury geometrycznej
 */
  const TypBrylyGeometrycznej  _TypBryly;

  protected:

/*!
 * \brief Nazwa pliku przechowujacego wspolrzedne bryly finalnej
 */
  std::string NazwaBryly;

/*!
 * \brief Nazwa pliku przechowujacego wspolrzedne bryly wzorcowej
 */
  std::string NazwaBrylyWzorcowej;

/*!
 * \brief Konstruktor parametryczny dla Bryly Geometrycznej
 * \param[in] Typ - identyfikator typu bryly geoemtrycznej. Domyslnie TB_Zadna
 * \param[in] Nazwa - Nazwa pliku przechowujacego wspolrzedne bryly finalnej. Domyslnie nazwa jest pusta.
 * \param[in] NazwaWzorca - Nazwa pliku przechowujacego wspolrzedne bryly wzorcowej. Domyslnie nazwa jest pusta.
 */
  BrylaGeometryczna(TypBrylyGeometrycznej Typ = TB_Zadna, std::string Nazwa=" ", std::string NazwaWzorca=" "): 
  _TypBryly(Typ), NazwaBryly(Nazwa), NazwaBrylyWzorcowej(NazwaWzorca) {}


  public:

/*!
 * \brief Udostępnia indentyfikator typu bryly geometrycznej
 * \return Identyfikator danej bryly geometrycznej
 */
  TypBrylyGeometrycznej TypBryly()const 
  {return _TypBryly;} 

/*!
 * \brief Udostępnia nazwe pliku przechowujacego wspolrzedne bryly geometrycznej
 * \return Nazwa pliku z wspolrzednymi bryly geometrycznej
 */
  std::string NazwaPlikuBryly()const
  {return NazwaBryly;}

/*!
 * \brief Udostępnia nazwe pliku przechowujacego wspolrzedne wzorcowe bryly geometrycznej
 * \return Nazwa pliku z wspolrzednymi wzorcowymi bryly geometrycznej
 */
  std::string NazwaPlikuBrylyWzorcowej()const
  {return NazwaBrylyWzorcowej;}

};



#endif