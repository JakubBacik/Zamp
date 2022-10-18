#include <iostream>
#include <sstream>
#include <dlfcn.h>
#include <cassert>
#include "Interp4Command.hh"
#include "MobileObj.hh"
#include <string>
#include <cstdio>
#include "LibInterface.hh"
#include <map>
#include <memory>

using namespace std;

bool ExecPreprocesor(const char* NameOfFile, istringstream &IStrm4Cmds){
    constexpr int sizeOfLine = 500;
    string cmd4Preproc = "cpp -P ";
    char line[sizeOfLine];
    ostringstream oTmpStrm;

    cmd4Preproc += NameOfFile;
    FILE* pProc = popen(cmd4Preproc.c_str(), "r");

    if(!pProc) 
      return false;

    while(fgets(line, sizeOfLine, pProc)){
      oTmpStrm << line;
    }
    IStrm4Cmds.str(oTmpStrm.str());

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

  dlclose(pLibHnd_Move);
  */
  if(argc < 2){
    cerr << "Not enough number of Parameters" << endl;
    return 1;
  }

  istringstream IStrm4Cmds;

  if(!ExecPreprocesor(argv[1], IStrm4Cmds)){
    cerr <<" Problem with ExecPreprocesor "<< endl;
  }

  cout << IStrm4Cmds.str() << endl;

  std::map<std::string, std::unique_ptr<LibInterface>> mapToInterface;
  mapToInterface[{"Move"}] = std::make_unique<LibInterface>(LibInterface{"Move"});
  
  return 0;
}
