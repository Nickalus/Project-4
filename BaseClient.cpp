#include "BaseClient.hpp"

BaseClient::BaseClient(char **name, unsigned int port, unsigned int key) 
: mPort(port),
  mSecretKey(key)
{
  mSocket = socket(AF_INET, SOCK_STREAM, 0);
}

void BaseClient::Init()
{
  //Zero out the struct
  memset(&mDest, 0, sizeof(mDest));
  mDest.sin_family = AF_INET;
  //Set the host address
  mDest.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
  //Set the port number
  mDest.sin_port = htons(PORTNUM);
  
  int c = connect(mSocket, (struct sockaddr *)&mDest, sizeof(struct sockaddr));
  if(c == -1)
  {
    //Error connecting
  }
  else
  {
    std::cout << "Connected!" << std::endl;
  }
}