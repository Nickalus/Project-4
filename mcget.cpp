#include "GetClient.hpp"

int main(int argc, char *argv[])
{
  if(argc != 5)
  {
    std::cout << "Error! Not enough args!" << std::endl;
    std::cout << "mcget MachineName <port> <Key> <filename>" << std::endl;
	return -1;
  }
  
  GetClient mcget(std::string(argv[1]), 
				  atoi(argv[2]), 
				  atoi(argv[3]), 
                  std::string(argv[4]));
				  
  mcget.Init();
  return mcget.Run();
}