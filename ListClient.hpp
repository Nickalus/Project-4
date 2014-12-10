#ifndef LISTCLIENT_HPP
#define LISTCLIENT_HPP

#include "BaseClient.hpp"
#include "formats.h"

class ListClient : public BaseClient
{
  public:
    ListClient(std::string, unsigned int, unsigned int);
	
	void Init();
	int Run();
  private:
    void ReadFiles();
  private:
	unsigned int mMessageSize, mResponse;
	char *mBuffer;
};

#endif