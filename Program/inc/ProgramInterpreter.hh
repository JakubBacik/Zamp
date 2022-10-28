#ifndef PROGRAMINTERPRETER_HH
#define PROGRAMINTERPRETER_HH

#include "Scene.hh"
#include "Set4LibInterface.hh"
#include <iostream>
#include <sstream>

class ProgramInterpreter{
    Scene _scene;
    Set4LibInterface _set4LibInterface;
    int _socket2Server;

    public:
    bool Read_XML_Config(const char* fileName);
    bool ExecProgram(const char* fileNameProg);
    bool ExecPreprocesor(const char* NameOfFile, std::istringstream &IStrm4Cmds);
    bool SendSceneState2Server();

};

#endif
