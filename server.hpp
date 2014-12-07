#ifndef SERVER_HPP
#define SERVER_HPP

#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <vector>
#include <cstdlib>
#include <string>

#include "formats.h"

struct Files
{
  char name[81];
  char fileBuffer[102401]; //100kb buffer
};

const unsigned int mBufSize = 3000;

class Server
{
  public:
    Server(unsigned int, unsigned int);
	
	void Init();
	void Run();
  private:
    bool CheckKey();
	void Type();
	
	int Store();
	int Recieve();
	int Delete();
	int List();
  private:
    unsigned int mSecretKey, mRecievedKey, mPort;
	
	int mSocket, mNewSocket;
	
	struct sockaddr_in mServer, mDestMachine;
	
	socklen_t mSocksize;
	
	char mPacketBuffer[mBufSize + 1];
	
	//Map holding file names, and buffer holding the file data
	Files mF;
	std::vector<Files> mWoot;
};

#endif