#ifndef PROGRAMINTERPRETER_HH
#define PROGRAMINTERPRETER_HH

#include "Scene.hh"
#include "Set4LibInterface.hh"
#include "Configuration.hh"
#include "Sender.hh"
#include <iostream>
#include <sstream>
#include <list>
#include <thread>

class ProgramInterpreter{
  private:
    Scene _scene;
    Set4LibInterface _set4LibInterface;
    Configuration _config;
    Sender& _sender;
    std::list<std::thread> _threadList;

  public:
    ProgramInterpreter(Sender& _sender) : _sender{_sender}{}
    bool Read_XML_Config(const char* fileName);
    bool ExecProgram(const char* fileNameProg);
    bool ExecPreprocesor(const char* NameOfFile, std::istringstream &IStrm4Cmds);
    void SendSceneState2Server();
    void AddObjectsToScene();
    void InitLibrary();

};

#endif
