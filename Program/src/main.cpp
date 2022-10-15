#include <iostream>
#include <sstream>
#include <dlfcn.h>
#include <cassert>
#include "Interp4Command.hh"
#include "MobileObj.hh"
#include <string>
#include <cstdio>

using namespace std;

bool ExecPreprocesor(const char* NameOfFile, istringstream &IStrm4Cmds){
    string Cmd4Preproc = "cpp -P ";
    char Line[500];
    ostringstream OTmpStrm;

    Cmd4Preproc += NameOfFile;
    FILE* pProc = popen(Cmd4Preproc.c_str(), "r");

    if(!pProc) return false;

    while(fgets(Line, 500, pProc)){
      OTmpStrm << Line;
    }
    IStrm4Cmds.str(OTmpStrm.str());

    return pclose(pProc) == 0;
}


int main(int argc, char **argv)
{/*
  void *pLibHnd_Move = dlopen("libInterp4Move.so",RTLD_LAZY);
  Interp4Command *(*pCreateCmd_Move)(void);
  void *pFun;

  if (!pLibHnd_Move) {
    cerr << "!!! Brak biblioteki: Interp4Move.so" << endl;
    return 1;
  }


  pFun = dlsym(pLibHnd_Move,"CreateCmd");
  if (!pFun) {
    cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
    return 1;
  }
  pCreateCmd_Move = *reinterpret_cast<Interp4Command* (**)(void)>(&pFun);


  Interp4Command *pCmd = pCreateCmd_Move();

  cout << endl;
  cout << pCmd->GetCmdName() << endl;
  cout << endl;
  pCmd->PrintSyntax();
  cout << endl;
  pCmd->PrintCmd();
  cout << endl;
  
  delete pCmd;

  dlclose(pLibHnd_Move);*/
  if(argc < 2){
    cerr << "Not enough number of Parameters" << endl;
    return 1;
  }

  istringstream IStrm4Cmds;

  if(!ExecPreprocesor(argv[1], IStrm4Cmds)){
    cerr <<" Problem with ExecPreprocesor "<< endl;
  }

  cout << IStrm4Cmds.str() << endl;
  
  return 0;
}
