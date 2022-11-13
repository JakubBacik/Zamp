#include "Scene.hh"

std::shared_ptr<MobileObj> Scene::FindMobileObj(const char* sObjName){
    return FindMobileObj(std::string{sObjName});
}
std::shared_ptr<MobileObj> Scene::FindMobileObj(const std::string& rObjNames){
    if(Set_MobileObjs.find(rObjNames) == Set_MobileObjs.end()){
        return Set_MobileObjs[rObjNames];
    }
    return nullptr;
}
void Scene::AddMobileObj(const std::string& objName){
    Set_MobileObjs[objName] = std::make_shared<MobileObj>();
    Set_MobileObjs[objName]->SetName(objName.c_str());
}
void Scene::AddObjOperation(const std::string& objName, const std::string& operName, const Vector3D& values){
    Set_MobileObjs[objName]->SetMobileMap(operName, values);
}
void Scene::printObjects(){
     for (const auto& [_, obj] : Set_MobileObjs) {
        std::cout << obj->GetName() << ":\n";
        for (const auto& [name, val] : obj->getMobileMap()) {
            std::cout << "\t" << name << " " << val << "\n";
        }
    }
}