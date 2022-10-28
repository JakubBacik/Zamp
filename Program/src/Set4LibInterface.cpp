#include "Set4LibInterface.hh"
#include <iostream>
#include <memory>

void Set4LibInterface::Set4LibInterfaceInit(){
    const char* nameOfLibInterface[] = {"Move", "Rotate", "Set", "Pause"}; 
    for(const char* itemInTable : nameOfLibInterface){
       std::shared_ptr tmp = std::make_shared<LibInterface>(LibInterface{itemInTable});
       std::cout << itemInTable << std::endl;
       tmp->LibInterfaceInit();
       mapToInterface[{itemInTable}]=tmp;
    }
}

Set4LibInterface::~Set4LibInterface(){
    mapToInterface.clear();
}

Set4LibInterface::Set4LibInterface(){
    std::cout << "Utowrzenie obiektu"<< std::endl;
}
