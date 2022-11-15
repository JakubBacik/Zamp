#ifndef  COMMAND4ROTATE_HH
#define  COMMAND4ROTATE_HH

#ifndef __GNUG__
# pragma interface
# pragma implementation
#endif

#include "Interp4Command.hh"
#include "Sender.hh"
#include <memory>

/*!
 * \file
 * \brief Definicja klasy Interp4Move
 *
 * Plik zawiera definicję klasy Interp4Move ...
 */

/*!
 * \brief Modeluje polecenie dla robota mobilnego, które wymusza jego ruch do przodu
 *
 *  Klasa modeluje ...
 */
class Interp4Rotate: public Interp4Command {
  /*
   *  Tu należy zdefiniować pola, które są niezbędne
   *  do przechowywania wartości parametrów danego polecenia.
   *  Ponieżej zdefiniowane jest tylko jedno pole jako przykład.
   */
  std::string _objectName;
  double  _speed;
  double _angle;
 public:
  /*!
   * \brief
   */
  Interp4Rotate();  
  /*!
   * \brief Wyświetla postać bieżącego polecenia (nazwę oraz wartości parametrów)
   */
  void PrintCmd() const override;
  /*!
   * \brief Wyświetla składnię polecenia
   */
  void PrintSyntax() const override;
  /*!
   * \brief Wyświetla nazwę polecenia
   */
  const char* GetCmdName() const override;
  /*!
   * \brief Wykonuje polecenie oraz wizualizuje jego realizację
   */
  bool ExecCmd(std::shared_ptr<MobileObj> pMobObj,  int socket) const override;
  /*!
   * \brief Czyta wartości parametrów danego polecenia
   */
  bool ReadParams(std::istream& Strm_CmdsList) override;
  /*!
   * \brief Wyświetla wartości wczytanych parametrów
   */
  void PrintParams() {}
  /*!
   * \brief
   *
   *  Ta metoda nie musi być zdefiniowna w klasie bazowej.
   */
  static Interp4Command* CreateCmd();
  std::string GetName()override{return _objectName;}
 };

#endif
