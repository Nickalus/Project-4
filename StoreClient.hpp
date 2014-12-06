#include "BaseClient.hpp"
#include "formats.h"

class StoreClient : public BaseClient
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
};