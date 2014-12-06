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
	//Get the packet, only 4 bytes + 1 for the NULL
	int length = recv(mNewSocket, mPacketBuffer, 5, 0);
	
	//NULL the last of the buffer
	mPacketBuffer[length] = '\0';
    
	//Check if the keys equal each other and send respons
	unsigned int response = htonl(CheckKey());
	send(mNewSocket, &response, 4, 0);
	
	//Close the socket
	close(mNewSocket);
	
    mNewSocket = accept(mSocket, (struct sockaddr *)&mDestMachine, &mSocksize);
  }
}

void Server::Type()
{
  //Get the type packet, only 4 bytes + 1 for the NULL
  recv(mNewSocket, mPacketBuffer, 5, 0);
  
  //NULL the last of the buffer
  mPacketBuffer[length] = '\0';
  
  //Check what the type
  int type;
  memcpy(type, mPacketBuffer, 4);

  switch(ntohl(type)) 
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
      status = 0;
    break;
  }
}

bool Server::CheckKey()
{
  //Get the key
  memcpy(&mRecievedKey, mPacketBuffer, 4);
  
  return (ntohl(mRecievedKey) == mSecretKey);
}

int Server::Store()
{
  std::cout << "Store!" << std::endl;
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