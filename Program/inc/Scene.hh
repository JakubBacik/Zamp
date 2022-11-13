#ifndef SCENE_HH
#define SCENE_HH

#include <map>
#include <memory>
#include <string>
#include "MobileObj.hh"
#include "AccessControl.hh"

class Scene: public AccessControl{
    std::map<std::string, std::shared_ptr<MobileObj>> Set_MobileObjs;

    public:
    std::shared_ptr<MobileObj> FindMobileObj(const char* sObjName);
    std::shared_ptr<MobileObj> FindMobileObj(const std::string& rObjNames);
    std::map<std::string, std::shared_ptr<MobileObj>> GetMobileObjects() { return Set_MobileObjs; };
    void AddMobileObj(const std::string& objName);
    void AddObjOperation(const std::string& objName, const std::string& operName, const Vector3D& values);
    void printObjects();
};

#endif
