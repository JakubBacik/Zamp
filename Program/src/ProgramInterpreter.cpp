#include "ProgramInterpreter.hh"
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>
#include "xmlinterp.hh"
#include <iostream>
#include <list>

using namespace std;
using namespace xercesc;

bool ProgramInterpreter::ExecPreprocesor(const char* NameOfFile, std::istringstream &IStrm4Cmds){
  constexpr int sizeOfLine = 500;
  std::string cmd4Preproc = "cpp -P ";
  char line[sizeOfLine];
  std::ostringstream oTmpStrm;

  cmd4Preproc += NameOfFile;
  FILE* pProc = popen(cmd4Preproc.c_str(), "r");

  if(!pProc) 
    return false;

  while(fgets(line, sizeOfLine, pProc)){
    oTmpStrm << line;
  }
  IStrm4Cmds.str(oTmpStrm.str());

  return pclose(pProc) == 0;
}

bool ProgramInterpreter::ExecProgram(const char* fileNameProg){
  InitLibrary();
  AddObjectsToScene();
  //_scene.printObjects();
  if (!_sender.OpenConnection()) return false;
    SendSceneState2Server();

  std::istringstream IStrm4Cmds;
  if(!ExecPreprocesor(fileNameProg, IStrm4Cmds)){
    std::cerr <<" Problem with ExecPreprocesor "<< std::endl;
    return false;
  };

  std::string lineFromCmd;

  while(IStrm4Cmds >> lineFromCmd){
    std::map<std::string, std::shared_ptr<LibInterface>> mapFromSet4LibInterface = _set4LibInterface.GetmapToInterface();
        
    if(mapFromSet4LibInterface.find(lineFromCmd) == mapFromSet4LibInterface.end()){
      std::cerr << "Library" << lineFromCmd << "not found" << std::endl;
      return true;
    }
        
    std::unique_ptr<Interp4Command> createCmdFor  = mapFromSet4LibInterface[lineFromCmd]->createCmd();

    if(!(createCmdFor->ReadParams(IStrm4Cmds))){
      std::cerr << "Error some problem with parametrs to plugin" << std::endl;
      return false;
    }
    std::shared_ptr<MobileObj> _Obj = _scene.FindMobileObj(createCmdFor->GetName());
    //createCmdFor->PrintCmd();
    createCmdFor->ExecCmd(_Obj, _sender.getSocket());
  }

  _sender.Close();
  return true;
}

bool ProgramInterpreter::Read_XML_Config(const char* sFileName){
  try {
    XMLPlatformUtils::Initialize();
  }
  catch (const XMLException& toCatch) {
    char* message = XMLString::transcode(toCatch.getMessage());
    cerr << "Error during initialization! :\n";
    cerr << "Exception message is: \n" << message << "\n";
    XMLString::release(&message);
    return 1;
  }

  SAX2XMLReader* pParser = XMLReaderFactory::createXMLReader();

  pParser->setFeature(XMLUni::fgSAX2CoreNameSpaces, true);
  pParser->setFeature(XMLUni::fgSAX2CoreValidation, true);
  pParser->setFeature(XMLUni::fgXercesDynamic, false);
  pParser->setFeature(XMLUni::fgXercesSchema, true);
  pParser->setFeature(XMLUni::fgXercesSchemaFullChecking, true);

  pParser->setFeature(XMLUni::fgXercesValidationErrorAsFatal, true);

  DefaultHandler* pHandler = new XMLInterp4Config(_config);
  pParser->setContentHandler(pHandler);
  pParser->setErrorHandler(pHandler);

  try {
    if (!pParser->loadGrammar("config/config.xsd", xercesc::Grammar::SchemaGrammarType,true)) {
      cerr << "!!! Plik grammar/actions.xsd, '" << endl;
      cerr << "!!! ktory zawiera opis gramatyki, nie moze zostac wczytany." << endl;
      return false;
    }
    pParser->setFeature(XMLUni::fgXercesUseCachedGrammarInParse,true);
    pParser->parse(sFileName);
  }
  catch (const XMLException& Exception) {
    char* sMessage = XMLString::transcode(Exception.getMessage());
    cerr << "Informacja o wyjatku: \n";
    cerr << "   " << sMessage << "\n";
    XMLString::release(&sMessage);
    return false;
  }
  catch (const SAXParseException& Exception) {
    char* sMessage = XMLString::transcode(Exception.getMessage());
    char* sSystemId = xercesc::XMLString::transcode(Exception.getSystemId());

    cerr << "Blad! " << endl;
    cerr << "    Plik:  " << sSystemId << endl;
    cerr << "   Linia: " << Exception.getLineNumber() << endl;
    cerr << " Kolumna: " << Exception.getColumnNumber() << endl;
    cerr << " Informacja: " << sMessage << endl;

    XMLString::release(&sMessage);
    XMLString::release(&sSystemId);
    return false;
  }
  catch (...) {
    cout << "Zgloszony zostal nieoczekiwany wyjatek!\n" ;
    return false;
  }

  delete pParser;
  delete pHandler;
  return true;
}

void ProgramInterpreter::AddObjectsToScene(){
  for (const auto& [objName, mobileObj] : _config.getObjectsList()) {
    _scene.AddMobileObj(objName);
    for (const auto& [mobileObjName, val] : mobileObj->getMobileMap()) {
      _scene.AddObjOperation(objName, mobileObjName, val);
    }
  }
}

void ProgramInterpreter::InitLibrary(){
  for(const std::string& element : _config.getLibNames()){
    std::cout << element << std::endl;
    if(!_set4LibInterface.CreateInterpCommand(element.c_str())){
      _set4LibInterface.RemoveInterpCommand(element.c_str());
    }
  }
}

void ProgramInterpreter::SendSceneState2Server(){
  std::string msg;

  msg += "Clear\n";
  for (const auto &rObj : _scene.GetMobileObjects()) {
    msg += "AddObj " + rObj.second->ConcatMessage();  
  }
  std::cout << msg;
  _sender.Send(msg.c_str());
}