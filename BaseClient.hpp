#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <netdb.h>
#include <string>

class BaseClient
{
  public:
    BaseClient(std::string, unsigned int, unsigned int);
	
	void Init();
  protected:
    struct sockaddr_in mDest; //Protected so it can be accessed by derived classes
  private:
    unsigned int mSecretKey;
	
	char mKeyResponse[5];
	
	int mSocket;
	
	unsigned int mPort;
};