#include "StoreClient.hpp"

int main(int argc, char *argv[])
{
  if(argc != 5)
  {
    std::cout << "Error! Not enough args!" << std::endl;
    std::cout << "mcput MachineName <port> <Key> <filename>" << std::endl;
	return -1;
  }
  
  StoreClient mcPut(std::string(argv[1]), atoi(argv[2]), atoi(argv[3]), std::string(argv[4]));
  
  mcPut.Init();
  
  mcPut.Run();
}