#include <iostream>
#include "Interp4Rotate.hh"
#include "MobileObj.hh"
#include <cmath>

using std::cout;
using std::endl;


extern "C" {
 Interp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Rotate"; }
}




/*!
 * \brief
 *
 *
 */
Interp4Command* CreateCmd(void)
{
  return Interp4Rotate::CreateCmd();
}


/*!
 *
 */
Interp4Rotate::Interp4Rotate(): _speed(0), _angle(0)
{}


/*!
 *
 */
void Interp4Rotate::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " << _speed << " " << _angle  << endl;
}


/*!
 *
 */
const char* Interp4Rotate::GetCmdName() const
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
bool Interp4Rotate::ExecCmd(Scene& scene, Sender& sender) const
{
  std::shared_ptr<MobileObj> pMobObj = scene.FindMobileObj(_objectName);
  if(pMobObj == nullptr){
    std::cerr << "Object " << _objectName <<" not found, ExecCmd"  << std::endl;
    return false;
  }
  
  int durationOfMove = std::abs(_angle /_speed);

  for (int i = 0; i < durationOfMove; ++i)
  {
    std::map<std::string, Vector3D> mapa = pMobObj->getMobileMap();
    Vector3D position = mapa["RotXYZ_deg"];

    position[2] += _speed;

    pMobObj->SetMobileMap("RotXYZ_deg", position);
    std::string ToSend = "UpdateObj ";
    ToSend += pMobObj->ConcatMessage();
    cout << ToSend << endl;
    sender.Send(ToSend.c_str());
    usleep(100000);

  }
  cout << "Exec:" << GetCmdName() << " " << _speed << " " << _angle  << endl;
  return true;
}


/*!
 *
 */
bool Interp4Rotate::ReadParams(std::istream& Strm_CmdsList)
{
   if(!(Strm_CmdsList >> _objectName)){
    return false;
  }
  if(!(Strm_CmdsList >> _speed)){
    return false;
  }
  if(!(Strm_CmdsList >> _angle)){
    return false;
  }
  return true;
}


/*!
 *
 */
Interp4Command* Interp4Rotate::CreateCmd()
{
  return new Interp4Rotate();
}


/*!
 *
 */
void Interp4Rotate::PrintSyntax() const
{
  cout << "   Rotate  NameOfObject Speed Angle" << endl;
}
