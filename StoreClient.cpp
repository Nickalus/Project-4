#include "StoreClient.hpp"
#include <fstream> 

StoreClient::StoreClient(std::string name, unsigned int port, unsigned int key, 
                         std::string fn) : BaseClient(name, port, key)
{
  mStore.fileName = fn.c_str();
}

void StoreClient::Init()
{
  BaseClient::Init();
}

void StoreClient::Run()
{ 
  //Send type
  unsigned int type = htonl(STORE);
  send(BaseClient::mSocket, &network_byte_order, 4, 0);
  
  //ReadFile();
  
  //if(!Send())
  //{
    //Error on sending...
	//std::cout << "Error: Something went wrong!" << std::endl;
  //}
  
  //std::cout << "Closing socket" << std::endl;
  //close(mSocket);
}

void StoreClient::ReadFile()
{
  std::ifstream is(mStore.fileName, std::ifstream::binary);
  
  if(is) 
  {
    //get length of file:
    is.seekg(0, is.end);
    mStore.bytesInFile = is.tellg();
    is.seekg(0, is.beg);
	
	char *buffer = new char[mStore.bytesInFile];
	
	std::cout << "Reading file..." << std::endl;
	
	// read data as a block:
    is.read(buffer, mStore.bytesInFile);
	
	if(is)
	{
      std::cout << "File read successfully." std::endl;
	}
    else
	{
      std::cout << "Error: Whole file could not be read" << std::endl;
	}
	
    is.close();

    //copy buffer to struct
	memcpy(mStore.fileBuffer, buffer, mStore.bytesInFile + 1);

    delete[] buffer;
  }
}

int StoreClient::Send()
{
  //Convert things to network byte order
  mStore.secretKey = htonl(mSecretKey);
  mStore.type = htonl(STORE);
  mStore.bytesInFile = htonl(mStore.bytesInFile);
  
  //Convert struct to byte array
  char *cTemp;
  cTemp = (char*)&mStore;
  
  //Send
  send(mSocket, cTemp, strlen(cTemp), 0);
  
  //Read response and return
  char buffer[4 + 1]; //1 added for the NULL terminator
  int len = recv(mSocket, buffer, 4, 0);
  
  return atoi(buffer);
}