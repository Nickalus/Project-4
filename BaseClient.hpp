class BaseClient
{
  public:
    BaseClient(char **, unsigned int, unsigned int);
	
	void Init();
	void Run() = 0;
  private:
    struct sockaddr_in mDest;
	
	int mSocket;
	
	unsigned int mPort, mSecretKey;
}