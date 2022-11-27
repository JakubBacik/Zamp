#ifndef SCENE_HH
#define SCENE_HH

#include <map>
#include <memory>
#include <string>
#include "MobileObj.hh"

class Scene{
  private:
    std::map<std::string, std::shared_ptr<MobileObj>> Set_MobileObjs;

  public:
    std::shared_ptr<MobileObj> FindMobileObj(const char* sObjName){return FindMobileObj(std::string{sObjName});} 
    std::map<std::string, std::shared_ptr<MobileObj>> GetMobileObjects() { return Set_MobileObjs; };
    std::shared_ptr<MobileObj> FindMobileObj(const std::string& rObjNames){
      std::cout << rObjNames << std::endl;
      if(Set_MobileObjs.find(rObjNames) != Set_MobileObjs.end()){
        return Set_MobileObjs[rObjNames];    
      }
      return nullptr;
    }
    void AddMobileObj(const std::string& objName){
      Set_MobileObjs[objName] = std::make_shared<MobileObj>();
      Set_MobileObjs[objName]->SetName(objName.c_str());
    }
    void AddObjOperation(const std::string& objName, const std::string& operName, const Vector3D& values){
      Set_MobileObjs[objName]->SetMobileMap(operName, values);
    }
    void printObjects(){
      for (const auto& [_, obj] : Set_MobileObjs) {
        std::cout << obj->GetName() << ":\n";
        for (const auto& [name, val] : obj->getMobileMap()) {
          std::cout << "\t" << name << " " << val << "\n";
        }
      }   
    }
};

#endif
