#ifndef SERVER_HPP
#define SERVER_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <map>
#include <cstdlib>

#include "formats.h"

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
	std::map<std::string, FileBuffer> mWoot;
};

#endif