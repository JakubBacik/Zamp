#include <iostream>
#include "Interp4Set.hh"
#include "MobileObj.hh"
#include <cmath>

using std::cout;
using std::endl;


extern "C" {
 Interp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Set"; }
}




/*!
 * \brief
 *
 *
 */
Interp4Command* CreateCmd(void)
{
  return Interp4Set::CreateCmd();
}


/*!
 *
 */
Interp4Set::Interp4Set(): _positionX(0), _positionY(0), _angleOZ(0)
{}


/*!
 *
 */
void Interp4Set::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " << _objectName << " " << _positionX<< " " << _positionY << " " << _angleOZ << endl;
}


/*!
 *
 */
const char* Interp4Set::GetCmdName() const
{
  return ::GetCmdName();
}

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

/*!
 *
 */
bool Interp4Set::ExecCmd(std::shared_ptr<MobileObj> pMobObj,   int socket) const
{
  std::map<std::string, Vector3D> mapa = pMobObj->getMobileMap();
  Vector3D position = mapa["Trans_m"];
  Vector3D AnglePosition = mapa["RotXYZ_deg"];
  
  position[0] = _positionX;
  position[1] = _positionY;
  AnglePosition[2] = _angleOZ;

  pMobObj->SetMobileMap("Trans_m", position);
  pMobObj->SetMobileMap("RotXYZ_deg", AnglePosition);
  std::string ToSend = "UpdateObj ";
  ToSend += pMobObj->ConcatMessage();
  cout << ToSend << endl;
  Send(socket, ToSend.c_str());

  cout << "Exec:" << GetCmdName() << " " << _objectName << " " << _positionX << " " << _positionY << " " << _angleOZ << endl;
  return true;
}


/*!
 *
 */
bool Interp4Set::ReadParams(std::istream& Strm_CmdsList)
{
  if(!(Strm_CmdsList >> _objectName)){
    return false;
  }
  if(!(Strm_CmdsList >> _positionX )){
    return false;
  }
  if(!(Strm_CmdsList >> _positionY)){
    return false;
  }
  if(!(Strm_CmdsList >> _angleOZ)){
    return false;
  }
  return true;
}


/*!
 *
 */
Interp4Command* Interp4Set::CreateCmd()
{
  return new Interp4Set();
}


/*!
 *
 */
void Interp4Set::PrintSyntax() const
{
  cout << "   Set  NameOfObject  PositionX  PositionY AngleOZ" << endl;
}
