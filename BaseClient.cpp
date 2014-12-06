#include "BaseClient.hpp"

BaseClient::BaseClient(std::string name, unsigned int port, unsigned int key) 
: mPort(port),
  mSecretKey(key)
{
  if((mSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  {
    std::perror("socket");
    exit(1);
  }
  
  //Clear struct
  memset(&mDest, 0, sizeof(mDest)); 
  
  //Code borrowed from notes
  char **pp; /* or dotted decimal IP addr */
  struct in_addr addr;
  struct hostent *hostp;
  if(inet_aton(name.c_str(), &addr) != 0)
  {
    hostp = gethostbyaddr((const char *)&addr, sizeof(addr), AF_INET);
  }
  else
  {
    hostp = gethostbyname(name.c_str());
  }

  for (pp = hostp->h_addr_list; *pp != NULL; pp++) 
  {
    addr.s_addr = ((struct in_addr *)*pp)->s_addr;
    //std::cout << "address: " << inet_ntoa(addr) << std::endl;
	
	//IP address of system
	inet_pton(AF_INET, inet_ntoa(addr), &(mDest.sin_addr));
	
	break; //Only need first
  }
}

void BaseClient::Init()
{
  //std::cout << "Connecting..." << std::endl;
  
  mDest.sin_family = AF_INET;
  //Set the port number
  mDest.sin_port = htons(mPort);
  
  int c = connect(mSocket, (struct sockaddr *)&mDest, sizeof(struct sockaddr));
  if(c == -1)
  {
    //Error connecting
	std::perror("connect");
    exit(1);
  }
  else
  {
      //std::cout << "Connected!" << std::endl;
	
      uint32_t network_byte_order;

      // convert and send
      //std::cout << "Sending key: " << mSecretKey << std::endl;
      network_byte_order = htonl(mSecretKey);
  
      send(mSocket, &network_byte_order, 4, 0);

      //Get the key
	  recv(mSocket, mKeyResponse, 5, 0);
	  uint32_t response;
      memcpy(&response, mKeyResponse, 4);
  
      if(ntohl(response) == 0) //Key did not match
      {
        std::cout << "Key did not match! Exiting" << std::endl;
        exit(1);
      }
	  else if(ntohl(response) == 1) //Key matched
	  {
	    //std::cout << "Key did match!" << std::endl;
	  }
  }
}