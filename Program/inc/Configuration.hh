#ifndef CONFIGURATION_HH
#define CONFIGURATION_HH



#include <vector>
#include <map>
#include <memory>
#include <string>
#include "MobileObj.hh"

class Configuration{
  std::map<std::string, std::shared_ptr<MobileObj>> ObjectsOperations;
  std::vector<std::string> libNames;

    public:
    void addObject(const std::string& objName);
    void addObjOperations(char* sName_Name, char* sName, Vector3D& values);
    void addLibName(const std::string& Lib);
    const std::map<std::string, std::shared_ptr<MobileObj>> & getObjectsList() const {return ObjectsOperations;}
    const std::vector<std::string>& getLibNames() const {return libNames;}
};

#endif
