#include "DelClient.hpp"

int main(int argc, char *argv[])
{
  if(argc != 5)
  {
    std::cout << "Error! Not enough args!" << std::endl;
    std::cout << "mcdel MachineName <port> <Key> <filename>" << std::endl;
	return -1;
  }
  
  DelClient mcdel(std::string(argv[1]), 
				  atoi(argv[2]), 
				  atoi(argv[3]), 
                  std::string(argv[4]));
				  
  mcdel.Init();
  return mcdel.Run();
}