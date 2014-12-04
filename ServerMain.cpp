#include "server.hpp"

int main(int argc, char *argv[])
{
  unsigned int secretKey = atoi(argv[2]);
  unsigned int port = atoi(argv[1]);
  
  Server myCloud(secretKey, port);
  myCloud.Init();
  myCloud.Run();
}