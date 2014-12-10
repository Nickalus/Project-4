#include "BaseClient.hpp"
#include "formats.h"
#include <vector>

class GetClient : public BaseClient
{
  public:
    GetClient(std::string, unsigned int, unsigned int, std::string);
	
	void Init();
	void Run();
  private:
    void SendRequest();
    void ListFiles();
  private:
	unsigned int mFileSize, mGetResponse;
    std::vector<string> mFileNames;
	
	char mPacketBuffer[3000];
	char mFileBuffer[3000];
};

#endif