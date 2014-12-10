#include "BaseClient.hpp"
#include "formats.h"

class StoreClient : private BaseClient
{
  public:
    StoreClient(std::string, unsigned int, unsigned int, std::string);
	
	void Init();
	int Run();
  private:
    void ReadFile();
    void Send();
  private:
    StoreRequest mStore;
	
	std::string mFilename;
	unsigned int mBytesInFile, mResponse;
	char mStoreResponse[4];
	char mFileBuffer[MAX];
};