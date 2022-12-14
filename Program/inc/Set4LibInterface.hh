#ifndef SET4LIBINTERFACE_HH
#define  SET4LIBINTERFACE_HH

#include <string>
#include <map>
#include <memory>
#include "LibInterface.hh"

class Set4LibInterface{
  private:
    std::map<std::string, std::shared_ptr<LibInterface>> mapToInterface;

  public:
    Set4LibInterface();
    ~Set4LibInterface();
    bool CreateInterpCommand(const char* libname);
    void RemoveInterpCommand(const char* libname);
    std::map<std::string, std::shared_ptr<LibInterface>> GetmapToInterface(){ return mapToInterface;}
};

#endif