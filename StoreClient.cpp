#include "StoreClient.hpp"
#include <fstream> 
#include <chrono>
#include <thread>

StoreClient::StoreClient(std::string name, unsigned int port, unsigned int key, 
                         std::string fn) : BaseClient(name, port, key), mFilename(fn)
{
  
}

void StoreClient::Init()
{
  BaseClient::Init();
}

void StoreClient::Run()
{ 
  //Send type
  unsigned int type = htonl(STORE);
  send(BaseClient::mSocket, &type, 4, 0);

  ReadFile();
  
  Send();
  
  recv(mSocket, mStoreResponse, 5, 0);
  memcpy(&mResponse, mStoreResponse, 4);
  
  std::cout << mResponse << std::endl;
}

void StoreClient::ReadFile()
{
  std::ifstream is(mFilename.c_str(), std::ifstream::binary);

  if(is) 
  {
    //get size of file:
    is.seekg (0, is.end);
    mBytesInFile = is.tellg();
    is.seekg (0, is.beg);

    char *buffer = new char[mBytesInFile];
	
    // read data as a block:
    is.read(buffer, mBytesInFile);

    is.close();

	memcpy(mFileBuffer, buffer, mBytesInFile);

    delete[] buffer;
  }
}

int StoreClient::Send()
{
  //Send fileName
  send(BaseClient::mSocket, mFilename.c_str(), mFilename.size(), 0);
  
  //Small delay
  std::chrono::milliseconds dura( 500 );
  std::this_thread::sleep_for( dura );
  
  //send bytesInFile
  mBytesInFile = htonl(mBytesInFile);
  send(BaseClient::mSocket, &mBytesInFile, sizeof(mBytesInFile), 0);
  
  //Small delay
  std::this_thread::sleep_for( dura );
  
  //send fileBuffer
  send(BaseClient::mSocket, mFileBuffer, MAX, 0);
}
