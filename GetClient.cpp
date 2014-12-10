#include "GetClient.hpp"
#include <fstream>

GetClient::GetClient(std::string machName, unsigned int port, unsigned int key, 
					 std::string f) : BaseClient(machName, port, key), mFileName(f) 
{
}

void GetClient::Init()
{
  BaseClient::Init();
}

int GetClient::Run()
{
  //Send type
  unsigned int type = htonl(RETRIEVE);
  send(BaseClient::mSocket, &type, 4, 0);
  
  SendRequest();
  
  return mResponse;
}

void GetClient::SendRequest()
{
  //Send fileName
  send(BaseClient::mSocket, mFileName.c_str(), mFileName.size(), 0);
  
  //Found file name
  recv(mSocket, mPacketBuffer, 5, 0);
  memcpy(&mResponse, mPacketBuffer, 4);
  mResponse = ntohl(mResponse); //Convert from network to host
  
  if(mResponse == 0)
  {
    //Read bytes in file
    recv(BaseClient::mSocket, mPacketBuffer, 5, 0);
	mFileSize = 0;
    memcpy(&mFileSize, mPacketBuffer, 4);
    mFileSize = ntohl(mFileSize);
  
    //std::cout << "File size = " << mFileSize << std::endl;
  
    //read filebuffer
    recv(BaseClient::mSocket, mFileBuffer, mFileSize, 0);
	 
	WriteFile();
	
	//Get the suceeded or failed message
	recv(BaseClient::mSocket, mPacketBuffer, 5, 0);
    memcpy(&mResponse, mPacketBuffer, 4);
    mResponse = ntohl(mResponse); //Convert from network to host
  }
  else
  {
    //Get the suceeded or failed message
	recv(BaseClient::mSocket, mPacketBuffer, 5, 0);
    memcpy(&mResponse, mPacketBuffer, 4);
    mResponse = ntohl(mResponse); //Convert from network to host
  }
}

void GetClient::WriteFile()
{
  //Our output file
  std::ofstream outfile(mFileName.c_str(), std::ofstream::binary);
  
  //write to outfile
  //std::cout << mFileBuffer << std::endl;
  outfile.write(mFileBuffer, mFileSize);
  
  //Close the file
  outfile.close();
}