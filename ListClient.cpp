#include "ListClient.hpp"
#include <fstream>
#include <vector>

ListClient::ListClient(std::string machName, unsigned int port, unsigned int key, 
					 std::string f) : BaseClient(machName, port, key), std::vector<string> mFileNames(f) 
{
}

void ListClient::Init()
{
  BaseClient::Init();
}

void ListClient::Run()
{
  //Send type
  unsigned int type = htonl(RETRIEVE);
  send(BaseClient::mSocket, &type, 4, 0);
  
  SendRequest();
}

void ListClient::SendRequest()
{
  // Would a request need to be sent? Various solutions didn't work and
  // make me believe it isn't necessary but I realize it sounds stupid

}

void ListClient::ListFiles()
{
  //Our output file
  std::ofstream outfile(mFileName.c_str(), std::ofstream::binary);
  
  //write to outfile
  std::cout << mFileBuffer << std::endl;
  outfile.write(mFileBuffer, mFileSize);
  
  //Close the file
  outfile.close();
}