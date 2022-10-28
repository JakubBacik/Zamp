#include <iostream>
#include <sstream>
#include <dlfcn.h>
#include <cassert>
#include "Interp4Command.hh"
#include "MobileObj.hh"
#include <string>
#include <cstdio>
#include "LibInterface.hh"
#include <map>
#include <memory>

using namespace std;

bool ExecPreprocesor(const char* NameOfFile, istringstream &IStrm4Cmds){
    constexpr int sizeOfLine = 500;
    string cmd4Preproc = "cpp -P ";
    char line[sizeOfLine];
    ostringstream oTmpStrm;

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


int main(int argc, char **argv)
{
  if(argc < 2){
    cerr << "Not enough number of Parameters" << endl;
    return 1;
  }

  istringstream IStrm4Cmds;

  if(!ExecPreprocesor(argv[1], IStrm4Cmds)){
    cerr <<" Problem with ExecPreprocesor "<< endl;
  }

  cout << IStrm4Cmds.str() << endl;
/*
  std::shared_ptr<LibInterface> tmp =  std::make_unique<LibInterface>(LibInterface{"Move"});
  tmp->LibInterfaceInit();
  mapToInterface[{"Move"}] = tmp;
*/
  return 0;
}
