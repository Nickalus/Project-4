#ifndef DELCLIENT_HPP
#define DELCLIENT_HPP

#include "BaseClient.hpp"
#include "formats.h"

class DelClient : public BaseClient
{
  public:
    DelClient(std::string, unsigned int, unsigned int, std::string);
	
	void Init();
	int Run();
  private:
    void SendRequest();
  private:
	unsigned int mResponse;
    std::string mFileName;
	
	char mPacketBuffer[3000];
};

#endif