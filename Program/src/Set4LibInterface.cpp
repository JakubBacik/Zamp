#include "Set4LibInterface.hh"
#include <iostream>

void Set4LibInterface::Set4LibInterfaceInit(){
    const char* nameOfLibInterface[] = {"Pause", "Move", "Rotate", "Set"}; 
    for(const char* itemInTable : nameOfLibInterface){
       mapToInterface[{itemInTable}] = std::make_shared<LibInterface>(LibInterface{itemInTable}); 
    }

    for(auto itemInTable : mapToInterface){
       itemInTable.second->LibInterfaceInit();
    }
}

Set4LibInterface::~Set4LibInterface(){
    mapToInterface.clear();
}

Set4LibInterface::Set4LibInterface(){
    std::cout << "Utowrzenie obiektu"<< std::endl;
}
