#ifndef GETCLIENT_HPP
#define GETCLIENT_HPP

#include "BaseClient.hpp"
#include "formats.h"

class GetClient : public BaseClient
{
  public:
    GetClient(std::string, unsigned int, unsigned int, std::string);
	
	void Init();
	int Run();
  private:
    void SendRequest();
    void WriteFile();
  private:
	unsigned int mFileSize, mResponse;
    std::string mFileName;
	
	char mPacketBuffer[3000];
	char mFileBuffer[3000];
};

#endif