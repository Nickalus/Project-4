#include "server.hpp"
#include <iostream>
#include <cstdlib>

int main(int argc, char *argv[])
{
  if(argc != 3)
  {
    std::cout << "Usage: mycloud_server <port> <key>" << std::endl;
	return -1;
  }

  unsigned int secretKey = atoi(argv[2]);
  unsigned int port = atoi(argv[1]);
  
  Server myCloud(secretKey, port);
  myCloud.Init();
  myCloud.Run();
}