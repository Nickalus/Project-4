#include "DelClient.hpp"

DelClient::DelClient(std::string machName, unsigned int port, unsigned int key, 
					 std::string f) : BaseClient(machName, port, key), mFileName(f) 
{
}

void DelClient::Init()
{
  BaseClient::Init();
}

int DelClient::Run()
{
  //Send type
  unsigned int type = htonl(DELETE);
  send(BaseClient::mSocket, &type, 4, 0);
  
  SendRequest();
  
  return mResponse;
}

void DelClient::SendRequest()
{
  //Send fileName
  send(BaseClient::mSocket, mFileName.c_str(), mFileName.size(), 0);
  
  //Get the response
  recv(BaseClient::mSocket, mPacketBuffer, 5, 0);
  memcpy(&mResponse, mPacketBuffer, 4);
  mResponse = ntohl(mResponse); //Convert from network to host
}