#include "server.hpp"

#include <iostream>

Server::Server(unsigned int key, unsigned int port) 
: mSecretKey(key), 
  mPort(port)
{
  //Socket used to listen for incoming connections
  mSocket = socket(AF_INET, SOCK_STREAM, 0);
  
  mSocksize = sizeof(struct sockaddr_in);
}

void Server::Init()
{
  //Clear the struct
  memset(&mServer, 0, sizeof(mServer));
  
  //Address family = Internet
  mServer.sin_family = AF_INET;
  
  //set our address to any interface
  mServer.sin_addr.s_addr = htonl(INADDR_ANY);
  
  //Set the server port number
  mServer.sin_port = htons(mPort);
  
  //Set all bits of the padding field to 0
  memset(mServer.sin_zero, '\0', sizeof(mServer.sin_zero)); 
  
  //bind serv information to mySocket
  bind(mSocket, (struct sockaddr *)&mServer, sizeof(struct sockaddr));
}

void Server::Run()
{
  //Start listening, allowing 1 pending connection
  listen(mSocket, 1);
  std::cout << "Listening..." << std::endl;
  
  mNewSocket = accept(mSocket, (struct sockaddr *)&mDestMachine, &mSocksize);
  
  while(mNewSocket)
  {
	//Get the packet
	int length = recv(mNewSocket, mPacketBuffer, mBufSize, 0);
	
	//NULL the data
	mPacketBuffer[length] = '\0';
	
	//Parse the packet/buffer
	ParsePacket();
	
	//Close the socket
	close(mNewSocket);
	
    mNewSocket = accept(mSocket, (struct sockaddr *)&mDestMachine, &mSocksize);
  }
}

void Server::ParsePacket()
{
  int status;
  //Check the key
  char key[4];
  memcpy(key, mPacketBuffer, 4);
  if(atoi(key) == mSecretKey)
  {
    //Check what the type
	char type[4];
	memcpy(type, mPacketBuffer+4, 4);
	
    switch(atoi(type)) 
    switch(atoi(type)) 
	{
      case STORE:
        status = Store();
      break;
      case RETRIEVE:
        status = Recieve();
      break;
      case DELETE:
        status = Delete();
      break;
      case LIST:
        status = List();
      break;
      default:
		std::cout << "Unknown type of request!" << std::endl;
		status = -1;
      break;
    }
  }
  else
  {
    //Key did not match
	status = -1;
  }
  //send(mNewSocket, msg.c_str(), msg.length(), 0);
}

int Server::Store()
{
  
}

int Server::Recieve()
{
}

int Server::Delete()
{
}

int Server::List()
{
}