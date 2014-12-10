#include "BaseClient.hpp"
#include "formats.h"

class DeleteClient : private BaseClient
{
  public:
    DeleteClient(std::string, unsigned int, unsigned int, std::string);
  
  void Init();
  void Run();
  private:
    void SendRequest();
    void DeleteFile();
  private:
    StoreRequest mStore;
  
  std::string mFilename;
  unsigned int mBytesInFile, mResponse;
  char mStoreResponse[5];
  char mFileBuffer[MAX];
};