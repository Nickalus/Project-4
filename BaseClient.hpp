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
    int mSocket; //Protected so it can be accessed by derived classes
  private:
    unsigned int mPort, mSecretKey;
	char mAddy[128];
	
	struct sockaddr_in mDest; 
};