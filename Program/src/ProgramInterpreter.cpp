#include "ProgramInterpreter.hh"


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
    std::istringstream IStrm4Cmds;
    if(!ExecPreprocesor(fileNameProg, IStrm4Cmds)){
        std::cerr <<" Problem with ExecPreprocesor "<< std::endl;
        return false;
    };

    std::string lineFromCmd;
    _set4LibInterface.Set4LibInterfaceInit();


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
        createCmdFor->PrintCmd();
        createCmdFor->ExecCmd(nullptr, 0);
    }


    return true;
}