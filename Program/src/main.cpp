#include <iostream>
#include <sstream>
#include <dlfcn.h>
#include <cassert>
#include "Interp4Command.hh"
#include "MobileObj.hh"
#include <string>
#include <cstdio>
#include "ProgramInterpreter.hh"
#include <map>
#include <memory>

using namespace std;

int main(int argc, char **argv)
{
  if(argc < 2){
    cerr << "Not enough number of Parameters" << endl;
    return 1;
  }

  ProgramInterpreter programInterpreter;

  programInterpreter.ExecProgram(argv[1]);
  return 0;
}
