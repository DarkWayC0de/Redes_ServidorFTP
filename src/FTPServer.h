#if !defined FTPServer_H
#define FTPServer_H

#include <iostream>
#include <list>


#include "ClientConnection.h"

class FTPServer {
public:
  FTPServer(int port = 21);
  void run();
  void stop();

private:
  int port;
  int msock;
  std::list<ClientConnection*> connection_list;
};

#endif