#ifndef LIBINTERFACE_HH
#define  LIBINTERFACE_HH

#include <string>
#include "Interp4Command.hh"

class LibInterface{
    void* _LibHandler;
    void *_pFun;
    std::string _CmdName;
    Interp4Command *(*_pCreateCmd)(void);

    public:
    LibInterface(const char* nameOfLib);
    ~LibInterface();
};

#endif