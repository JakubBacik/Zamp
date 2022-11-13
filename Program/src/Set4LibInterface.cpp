#include "Set4LibInterface.hh"
#include <iostream>
#include <memory>

Set4LibInterface::~Set4LibInterface(){
    mapToInterface.clear();
}

Set4LibInterface::Set4LibInterface(){
    std::cout << "Utowrzenie obiektu"<< std::endl;
}

bool Set4LibInterface::CreateInterpCommand(const char* libname){
    mapToInterface[libname] = std::make_shared<LibInterface>(LibInterface({libname}));
    return mapToInterface[libname]->LibInterfaceInit();
}

void Set4LibInterface::RemoveInterpCommand(const char* libname){
     auto it = mapToInterface.find(libname);
     if(it != mapToInterface.end()){
        mapToInterface.erase(it);
    }
}
