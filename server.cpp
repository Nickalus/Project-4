#include "server.hpp"

#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>
#include <iterator>
#include <chrono>
#include <thread>

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
	recv(mNewSocket, mPacketBuffer, 4, 0);
    
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
      status = -1; //error
    break;
  }
  
  //Send response
  send(mNewSocket, &status, sizeof(status), 0);
}

bool Server::CheckKey()
{
  return(ntohl(mRecievedKey) == mSecretKey);
}

void Server::GetFileName()
{
  //Clear the buffer
  memset(mPacketBuffer, '\0', sizeof(mPacketBuffer)); 

  //Read filename
  int r = recv(mNewSocket, mPacketBuffer, 81, 0);
  if(r == -1)
  {
    perror("recv");
	exit(1);
  }

  mPacketBuffer[81] = '\0';
  memcpy(&mF.name, mPacketBuffer, 81);
  
  std::cout << "Filename = " << mF.name << std::endl;
}

int Server::Store()
{ 
  std::cout << "Request Type = put" << std::endl;
  
  GetFileName();
 
  //Read bytes in file
  recv(mNewSocket, mPacketBuffer, 4, 0);
  mF.fileSize = 0;
  memcpy(&mF.fileSize, mPacketBuffer, 4);
  mF.fileSize = ntohl(mF.fileSize);
  
  //read filebuffer
  recv(mNewSocket, mF.fileBuffer, mF.fileSize, 0);
  
  if(CheckKey())
  {
    if(mWoot.size() == 0) //Only if the vector is empty
	{  
	  mWoot.push_back(mF);
	}
	else
	{
      //Check if the file name already exists
      for(unsigned int i = 0; i < mWoot.size(); i++)
      {
	    if(!strcmp(mWoot[i].name, mF.name)) //If it does
	    {
	      //Replace the file data
		  strcpy(mWoot[i].fileBuffer, mF.fileBuffer);
	    }
	    else //If it doesn't
	    {
	      mWoot.push_back(mF);
	    }
      }
	}
  }
  
  //Find the file in the vector
  if(mWoot.size() != 0)
  {
    for(unsigned int i = 0; i < mWoot.size(); i++)
    {
      if(!strcmp(mWoot[i].name, mF.name) && CheckKey()) //if lhs is equal to rhs.
	  {
	    //std::cout << mWoot[i].name << " " << mWoot[i].fileSize << " " << mWoot[i].fileBuffer << std::endl;
        std::cout << "Operation Status = success" << std::endl;
	    std::cout << "--------------------------" << std::endl;
	    return 0; //succeeded 
	  }
    }
  }
  
  //Wasn't found
  std::cout << "Operation Status = error" << std::endl;
  std::cout << "--------------------------" << std::endl;
  return -1;
}

int Server::Recieve()
{
  std::cout << "Request Type = get" << std::endl;

  GetFileName();
  
  //Search for filename
  for(unsigned int i = 0; i < mWoot.size(); i++) 
  {
    if(!strcmp(mWoot[i].name, mF.name) && CheckKey()) //if lhs is equal to rhs.
	{
	  //Send found message (to keep from breaking code...)
	  unsigned int one = htonl(0);
	  send(mNewSocket, &one, sizeof(one), 0);
	  
	   //Small delay
	  std::chrono::milliseconds dura(500);
      std::this_thread::sleep_for(dura);
	  
      //send bytesInFile
      unsigned int s = htonl(mWoot[i].fileSize);
      send(mNewSocket, &s, sizeof(mWoot[i].fileSize), 0);
	  
      //Another delay
      std::this_thread::sleep_for(dura);
  
      //send fileBuffer
      send(mNewSocket, mWoot[i].fileBuffer, MAX, 0);
	  
      std::cout << "Operation Status = success" << std::endl;
	  std::cout << "--------------------------" << std::endl;
	  return 0; //succeeded 
	}
  }
  
  //Didn't find the file
  std::cout << "Operation Status = error" << std::endl;
  std::cout << "--------------------------" << std::endl;
  return -1;
}

int Server::Delete()
{
  std::cout << "Request Type = del" << std::endl;

  GetFileName();
  
  //Loop till file name is found, delete that index
  for(unsigned int i = 0; i < mWoot.size(); i++)
  {
    if(!strcmp(mWoot[i].name, mPacketBuffer) && CheckKey())
	{
	  mWoot.erase(mWoot.begin() + i);
	  
	  std::cout << "Operation Status = success" << std::endl;
	  std::cout << "--------------------------" << std::endl;
	  
	  return 0;
	}
  }
  
  std::cout << "Operation Status = error" << std::endl;
  std::cout << "--------------------------" << std::endl;
  return -1;
}

int Server::List()
{
  std::cout << "Request Type = list" << std::endl;
  std::cout << "Filename = NONE" << std::endl;
  
  if(CheckKey())
  {
    std::string listString;
    for(unsigned int i = 0; i < mWoot.size(); i++)
    {
      //Convert the name to a string
      listString = std::string(mWoot[i].name);
	
	  //Add a newline char to the end
	  listString += '\n'; 
    }
  
    //send size of the string
    unsigned int stringSize = listString.size();
    send(mNewSocket, &stringSize, sizeof(stringSize), 0);
  
    //Small delay
    std::chrono::milliseconds dura(500);
    std::this_thread::sleep_for(dura);
  
    //Send the message/string
    send(mNewSocket, listString.c_str(), sizeof(listString), 0);
	
    std::cout << "Operation Status = success" << std::endl;
    std::cout << "--------------------------" << std::endl;
	  
    return 0;
  }
  else
  {
    std::cout << "Operation Status = error" << std::endl;
    std::cout << "--------------------------" << std::endl;
    return -1;
  }
}