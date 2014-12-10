#include "ListClient.hpp"
#include <fstream>
#include <chrono>
#include <thread>

ListClient::ListClient(std::string machName, unsigned int port, 
					   unsigned int key) : BaseClient(machName, port, key)
{
}

void ListClient::Init()
{
  BaseClient::Init();
}

int ListClient::Run()
{
  //Send type
  unsigned int type = htonl(LIST);
  send(BaseClient::mSocket, &type, 4, 0);
  
  ReadFiles();
  
  return mResponse;
}

void ListClient::ReadFiles()
{ 
    //Read bytes in file
	mBuffer = new char[5];
    recv(BaseClient::mSocket, mBuffer, 5, 0);
	mMessageSize = 0;
    memcpy(&mMessageSize, mBuffer, 4);
    mMessageSize = ntohl(mMessageSize);
	delete mBuffer;
  
    //std::cout << "File size = " << mFileSize << std::endl;
  
    //read filebuffer
	mBuffer = new char[mMessageSize];
    recv(BaseClient::mSocket, mBuffer, mMessageSize, 0);
	
	std::cout << "Files: " << std::endl;
	std::cout << mBuffer << std::endl;
	delete mBuffer;
	
	//Get the suceeded or failed message
	mBuffer = new char[5];
	recv(BaseClient::mSocket, mBuffer, 5, 0);
    memcpy(&mResponse, mBuffer, 4);
    mResponse = ntohl(mResponse); //Convert from network to host
	delete mBuffer;
}