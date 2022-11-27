#ifndef SENDER_HH
#define SENDER_HH

#include <thread>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "AccessControl.hh"
#include <unistd.h>
#include <string.h>
#include <vector>
#include <mutex>

constexpr int PORT = 6217;

class Sender {
  private:
    int _Socket;
    std::mutex _SenderMutex;
  public:
    int getSocket(){return _Socket;}
    int Send(const char *sMesg){
      ssize_t  IlWyslanych;
      ssize_t  IlDoWyslania = (ssize_t) strlen(sMesg);
      std::lock_guard<std::mutex> lockGurad{_SenderMutex};

      while ((IlWyslanych = write(_Socket,sMesg,IlDoWyslania)) > 0) {
        IlDoWyslania -= IlWyslanych;
        sMesg += IlWyslanych;
      }
      if (IlWyslanych < 0) {
        std::cerr << "*** Blad przeslania napisu." << std::endl;
      }
      return 0;
    }

    void Close(){
      std::cout << "Close\n" << std::endl;
      Send("Close\n");
    }

    bool OpenConnection(){
      struct sockaddr_in  DaneAdSerw;

      bzero((char *)&DaneAdSerw,sizeof(DaneAdSerw));

      DaneAdSerw.sin_family = AF_INET;
      DaneAdSerw.sin_addr.s_addr = inet_addr("127.0.0.1");
      DaneAdSerw.sin_port = htons(PORT);

      _Socket = socket(AF_INET,SOCK_STREAM,0);

      std::cout << "Port   :" << _Socket << std::endl;

      if (_Socket < 0) {
        std::cerr << "*** Blad otwarcia gniazda." << std::endl;
        return false;
      }

      if (connect(_Socket,(struct sockaddr*)&DaneAdSerw,sizeof(DaneAdSerw)) < 0){
        std::cerr << "*** Brak mozliwosci polaczenia do portu: " << PORT << std::endl;
        return false;
      }
      return true;
    }


};




#endif
