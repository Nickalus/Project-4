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
  
  struct hostent *he;
  struct in_addr **addr_list;
  
  switch(inet_pton(AF_INET, name.c_str(), &mDest)) 
  {
    case -1:            //There was an error 
      perror("IP error");
	  exit(-1);
    break;
    case 0:            //Input isn't a valid IP address, must be a DNS
      if((he = gethostbyname(name.c_str())) == NULL) 
      {
        // get the host info
        herror("gethostbyname");
        exit(1);
      }
    break;
    case 1:            //Valid IP address
      he = gethostbyaddr(&mDest, sizeof(mDest), AF_INET);
	  
	  if((he == NULL))
      {
        // get the host info
        herror("gethostbyaddr");
        exit(1);
      }
    break;
    default:            // Note the colon, not a semicolon
      //std::cout<<"Error, bad input, quitting\n";
	  exit(1);
    break;
  }
  
  addr_list = (struct in_addr **) he->h_addr_list;
     
  for(int i = 0; addr_list[i] != NULL; i++) 
  {
    std::cout << "Connecting..." << std::endl;
    //Return the first one;
    strcpy(mAddy , inet_ntoa(*addr_list[i]) );
    break;
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