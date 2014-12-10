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
  
  //mDest.sin_addr.s_addr = inet_addr(mAddy);
  
  //Set the port number
  mDest.sin_port = htons(mPort);
  
  if(connect(mSocket, (struct sockaddr *)&mDest, sizeof(struct sockaddr)) == -1)
  {
    //Error connecting
	std::perror("connect");
    exit(1);
  }
  else
  {
    //std::cout << "Connected!" << std::endl;

    // convert and send
    unsigned int network_byte_order = htonl(mSecretKey);
  
    //Send the key
    send(mSocket, &network_byte_order, 4, 0);
  }
}