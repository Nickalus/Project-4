#include "DeleteClient.hpp"
#include <fstream>

DeleteClient::DeleteClient(std::string machName, unsigned int port, unsigned int key, 
					 std::string f) : BaseClient(machName, port, key), mFileName(f) 
{
}

void DeleteClient::Init()
{
  BaseClient::Init();
}

void DeleteClient::Run()
{
  //Send type
  unsigned int type = htonl(RETRIEVE);
  send(BaseClient::mSocket, &type, 4, 0);
  
  SendRequest();
}

void DeleteClient::SendRequest()
{
  //Send fileName
  send(BaseClient::mSocket, mFileName.c_str(), mFileName.size(), 0);
  
  //Recieve found file name
  recv(mSocket, mPacketBuffer, 5, 0);
  memcpy(&mGetResponse, mPacketBuffer, 4);
  mGetResponse = ntohl(mGetResponse); //Convert from network to host
  
  if(mGetResponse)
  {
    //Read bytes in file
    recv(BaseClient::mSocket, mPacketBuffer, 5, 0);
	mFileSize = 0;
    memcpy(&mFileSize, mPacketBuffer, 4);
    mFileSize = ntohl(mFileSize);
  
    std::cout << "File size = " << mFileSize << std::endl;
  
    //read filebuffer
    recv(BaseClient::mSocket, mFileBuffer, mFileSize, 0);
	
	DeleteFile();
	
  // TODO: Not sure how to transfer error messages afted delete function
	//Get the suceeded or failed message
	recv(BaseClient::mSocket, mPacketBuffer, 5, 0);
    memcpy(&mGetResponse, mPacketBuffer, 4);
    mGetResponse = ntohl(mGetResponse); //Convert from network to host
  }
  else
  {
    //Get the suceeded or failed message
	recv(BaseClient::mSocket, mPacketBuffer, 5, 0);
    memcpy(&mGetResponse, mPacketBuffer, 4);
    mGetResponse = ntohl(mGetResponse); //Convert from network to host
  }
}

void DeleteClient::DeleteFile()
{
  delete BaseClient;
}