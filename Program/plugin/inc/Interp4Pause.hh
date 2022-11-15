#ifndef  COMMAND4PAUSE_HH
#define  COMMAND4PAUSE_HH

#ifndef __GNUG__
# pragma interface
# pragma implementation
#endif

#include "Interp4Command.hh"
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
class Interp4Pause: public Interp4Command {
  /*
   *  Tu należy zdefiniować pola, które są niezbędne
   *  do przechowywania wartości parametrów danego polecenia.
   *  Ponieżej zdefiniowane jest tylko jedno pole jako przykład.
   */

  double  _time;
 public:
  /*!
   * \brief
   */
  Interp4Pause();  
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
  std::string GetName()override{return "Pause";}
 };

#endif
