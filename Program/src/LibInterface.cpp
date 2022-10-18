#include "LibInterface.hh"
#include <iostream>
#include <dlfcn.h>

LibInterface::LibInterface(const char* nameOfLib){
  std::string fullNameOfLib = "libInterp4";
  fullNameOfLib += nameOfLib;
  fullNameOfLib += ".so";
  _LibHandler = dlopen(fullNameOfLib.c_str(),RTLD_LAZY);


  if (!_LibHandler) {
    std::cerr << "!!!" << fullNameOfLib <<" not found" << std::endl;
    exit(0);
  }

  _pFun = dlsym(_LibHandler,"CreateCmd");
  if (!_pFun) {
    std::cerr << "!!! CreateCmd not found" << std::endl;
    exit(0);
  }

  _pCreateCmd = reinterpret_cast<Interp4Command* (*)(void)>(_pFun);


  Interp4Command *pCmd = _pCreateCmd();

  _CmdName = pCmd->GetCmdName(); 
  
  delete pCmd;
}

LibInterface::~LibInterface(){
  dlclose(_LibHandler);
}