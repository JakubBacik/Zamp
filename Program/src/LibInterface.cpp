#include "LibInterface.hh"
#include <iostream>
#include <dlfcn.h>
#include <memory>

LibInterface::LibInterface(const char* nameOfLib): _CmdName{nameOfLib}{}

int LibInterface::LibInterfaceInit(){
  std::string fullNameOfLib = "libInterp4" + _CmdName + ".so";
  
  if(!_LibHandler){
    std::cerr << "!!! " << fullNameOfLib << " was inital yet" << std::endl;
    return false;
  }

  _LibHandler = dlopen(fullNameOfLib.c_str(),RTLD_LAZY);

  if (!_LibHandler) {
    std::cerr << "!!!"  << fullNameOfLib <<" not found" << std::endl;
    return false;
  }

  _pFun = dlsym(_LibHandler,"CreateCmd");
  if (!_pFun) {
    std::cerr << "!!! CreateCmd not found" << std::endl;
    return false;
  }

  _pCreateCmd = reinterpret_cast<Interp4Command* (*)(void)>(_pFun);

  return true;
}

LibInterface::~LibInterface(){
  if(_LibHandler) {
    dlclose(_LibHandler);
  }
}

std::unique_ptr<Interp4Command> LibInterface::createCmd() {
  if (_pCreateCmd) {
    return std::unique_ptr<Interp4Command>(_pCreateCmd());
  }
  return nullptr;
}
