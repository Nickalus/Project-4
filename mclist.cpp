#include "ListClient.hpp"

int main(int argc, char *argv[])
{
  if(argc != 4)
  {
    std::cout << "Error! Not enough args!" << std::endl;
    std::cout << "mclist MachineName <port> <Key>" << std::endl;
	return -1;
  }
  
  ListClient mclist(std::string(argv[1]), atoi(argv[2]), atoi(argv[3]));
				  
  mclist.Init();
  return mclist.Run();
}