#include "Configuration.hh"

void Configuration::addObjOperations(char* obj, char* operName, Vector3D& values){
  ObjectsOperations[obj]->SetMobileMap(operName, values);
}

void Configuration::addObject(const std::string& objName){
  ObjectsOperations[objName] = std::make_shared<MobileObj>();
  ObjectsOperations[objName]->SetName(objName.c_str());
}

void Configuration::addLibName(const std::string& Lib){
  std::string letter = Lib.substr(9, Lib.length()); 
  std::string letter2 =letter.substr(0, letter.length()-3); 
  libNames.push_back(letter2);
}