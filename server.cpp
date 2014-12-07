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
  
  //Start listening, allowing 1 pending connection
  listen(mSocket, 1);
}

void Server::Run()
{
  mNewSocket = accept(mSocket, (struct sockaddr *)&mDestMachine, &mSocksize);

  while(mNewSocket)
  {
	//Get the packet, only 4 bytes
	int length = recv(mNewSocket, mPacketBuffer, 4, 0);
    
    //Get the key
    memcpy(&mRecievedKey, mPacketBuffer, 4);
    std::cout << "Secret Key = " << ntohl(mRecievedKey) << std::endl;
	
	//Check the type of request
	Type();
	
	//Close the socket
	close(mNewSocket);
	
    mNewSocket = accept(mSocket, (struct sockaddr *)&mDestMachine, &mSocksize);
	
	//Clear the buffer
	//Set all bits of the padding field to 0
    memset(mPacketBuffer, '\0', sizeof(mPacketBuffer)); 
  }
}

void Server::Type()
{
  //Get the type packet, only 4 bytes
  recv(mNewSocket, mPacketBuffer, 4, 0);
  
  //Check what the type
  int type;
  memcpy(&type, mPacketBuffer, 4);
  
  int status;
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
  
  //Send response
  send(mNewSocket, &status, sizeof(status), 0);
}

bool Server::CheckKey()
{
  return(ntohl(mRecievedKey) == mSecretKey);
}

int Server::Store()
{
  std::cout << "Request Type = put" << std::endl;
  
  //Read filename
  int r = recv(mNewSocket, mPacketBuffer, 81, 0);
  if(r == -1)
  {
    perror("recv");
	exit(1);
  }
  char fiName[81];
  mPacketBuffer[81] = '\0';
  memcpy(&mF.name, mPacketBuffer, 81);
  //mF.name = fiName;
  std::cout << "Filename = " << mF.name << std::endl;
 
  //Read bytes in file
  recv(mNewSocket, mPacketBuffer, 4, 0);
  unsigned int bytesInFile = 0;
  memcpy(&bytesInFile, mPacketBuffer, 4);
  bytesInFile = ntohl(bytesInFile);
  
  //read filebuffer
  recv(mNewSocket, mPacketBuffer, MAX, 0);
  memcpy(&mF.fileBuffer, mPacketBuffer, bytesInFile);
  
  if(CheckKey())
  {
    mWoot.push_back(mF);
  }
  
  //Find the file in the vector
  for(auto i : mWoot)
  {
    if(strcmp(mF.name, i.name) == 0 && CheckKey())  //if lhs is equal to rhs.
	{
	  std::cout << "Operation Status = success" << std::endl;
	  std::cout << "--------------------------" << std::endl;
	  return 1; //succeeded 
	}
	else
	{
	  std::cout << "Operation Status = error" << std::endl;
	  std::cout << "--------------------------" << std::endl;
	  return 0;
	}
  }
}

int Server::Recieve()
{
  std::cout << "Request Type = get" << std::endl;
}

int Server::Delete()
{
  std::cout << "Request Type = del" << std::endl;
}

int Server::List()
{
  std::cout << "Request Type = list" << std::endl;
}