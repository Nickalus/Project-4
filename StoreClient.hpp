#include "BaseClient.hpp"
#include "formats.h"

class StoreClient : private BaseClient
{
  public:
    StoreClient(std::string, unsigned int, unsigned int, std::string);
	
	void Init();
	void Run();
  private:
    void ReadFile();
    int Send();
  private:
    StoreRequest mStore;
	
	std::string mFilename;
	unsigned int mBytesInFile, mResponse;
	char mStoreResponse[5];
	char mFileBuffer[MAX];
};