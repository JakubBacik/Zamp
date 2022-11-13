#ifndef SENDER_HH
#define SENDER_HH

#include "Scene.hh"
#include <thread>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "AccessControl.hh"
#include <unistd.h>
#include <string.h>
#include <vector>

constexpr int PORT = 6217;

class Sender {

  int _Socket;
  public:
    int Send(const char *sMesg);
    bool OpenConnection();
    int Close();
};

#endif
