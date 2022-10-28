#ifndef SCENE_HH
#define SCENE_HH

#include <map>
#include <memory>
#include <string>
#include "MobileObj.hh"

class Scene{
    std::map<std::string, std::shared_ptr<MobileObj>> Set_MobileObjs;

    public:
    std::shared_ptr<MobileObj> FindMobileObj(const char* sObjName);
    std::shared_ptr<MobileObj> FindMobileObj(const std::string& rObjNames);
};

#endif
