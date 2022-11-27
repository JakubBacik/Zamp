#ifndef LIBINTERFACE_HH
#define  LIBINTERFACE_HH

#include <string>
#include "Interp4Command.hh"
#include <memory>

class LibInterface{
  private:
    void* _LibHandler;
    void *_pFun;
    std::string _CmdName;
    Interp4Command *(*_pCreateCmd)(void);
  public:
    LibInterface(const char* nameOfLib);
    int LibInterfaceInit();
    ~LibInterface();
    std::string GetCmdName(){return _CmdName;}
    std::unique_ptr<Interp4Command> createCmd();
};

#endif