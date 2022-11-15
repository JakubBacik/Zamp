#include <iostream>
#include "Interp4Move.hh"
#include "MobileObj.hh"
#include "Sender.hh"
#include <unistd.h>
#include <cmath>

using std::cout;
using std::endl;


extern "C" {
 Interp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Move"; }
}




/*!
 * \brief
 *
 *
 */
Interp4Command* CreateCmd(void)
{
  return Interp4Move::CreateCmd();
}


/*!
 *
 */
Interp4Move::Interp4Move(): _speedMs(0), _distanceM(0)
{}


/*!
 *
 */
void Interp4Move::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " << _objectName << " " << _speedMs << " " << _distanceM << endl;
}


/*!
 *
 */
const char* Interp4Move::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 *
 */
int Send(int Socket, const char *sMesg)
{
  ssize_t  IlWyslanych;
  ssize_t  IlDoWyslania = (ssize_t) strlen(sMesg);

  while ((IlWyslanych = write(Socket,sMesg,IlDoWyslania)) > 0) {
    IlDoWyslania -= IlWyslanych;
    sMesg += IlWyslanych;
  }
  if (IlWyslanych < 0) {
    std::cerr << "*** Blad przeslania napisu." << std::endl;
  }
  return 0;
}

bool Interp4Move::ExecCmd(std::shared_ptr<MobileObj> pMobObj,   int socket) const
{
  int durationOfMove = std::abs(_distanceM/_speedMs);

  for (int i = 0; i < durationOfMove; ++i)
  {
    std::map<std::string, Vector3D> mapa = pMobObj->getMobileMap();
    Vector3D position = mapa["Trans_m"];
    Vector3D angle = mapa["RotXYZ_deg"];


    position[0] += _speedMs*std::cos(M_PI *angle[2]/180);
    position[1] += _speedMs*std::sin(M_PI *angle[2]/180); 

    pMobObj->SetMobileMap("Trans_m", position);
    std::string ToSend = "UpdateObj ";
    ToSend += pMobObj->ConcatMessage();
    cout << ToSend << endl;
    Send(socket, ToSend.c_str());
    usleep(100000);

  }
  cout << "Exec:" << GetCmdName() << " " << _objectName << " " << _speedMs << " " << _distanceM << endl;
  return true;
}


/*!
 *
 */
bool Interp4Move::ReadParams(std::istream& Strm_CmdsList)
{
  if(!(Strm_CmdsList >> _objectName)){
    return false;
  }
  if(!(Strm_CmdsList >> _speedMs)){
    return false;
  }
  if(!(Strm_CmdsList >> _distanceM)){
    return false;
  }
  return true;
}


/*!
 *
 */
Interp4Command* Interp4Move::CreateCmd()
{
  return new Interp4Move();
}


/*!
 *
 */
void Interp4Move::PrintSyntax() const
{
  cout << "  Move  NameOfObject  Speed[m/s]  Distance[m]" << endl;
}
