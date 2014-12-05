#include "BaseClient.hpp"
#include "formats.h"

class StoreClient : public BaseClient
{
  public:
    StoreClient(char **, unsigned int, unsigned int, char *);
	
	void Init();
	void Run();
  private:
    StoreRequest mStore;
};