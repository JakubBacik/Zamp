#ifndef SET4LIBINTERFACE_HH
#define  SET4LIBINTERFACE_HH

#include <string>
#include <map>
#include <memory>
#include "LibInterface.hh"

class Set4LibInterface{
    std::map<std::string, std::shared_ptr<LibInterface>> mapToInterface;

    public:
    Set4LibInterface();
    void Set4LibInterfaceInit();

};

#endif