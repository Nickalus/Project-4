const int MAX = 102400; //100kb

enum {STORE, RETRIEVE, DELETE, LIST};

struct myFile
{
  char fileBuffer[MAX]; //100kb buffer
} mFile;

 struct StoreRequest
{
  unsigned int secretKey; //Network byte order
  unsigned int type = STORE; //Network byte order
  //null terminated character string starting at the beginning of the buffer
  char fileName[81]; 
  unsigned int bytesInFile; //Network byte order
  char fileBuffer[MAX]; //100kb buffer
};

unsigned int StoreResponse = 0;

struct RetrieveRequest
{ 
  unsigned int secretKey; //Network byte order
  unsigned int type; //Network byte order
  //null terminated character string starting at the beginning of the buffer
  char fileName[81];
};

struct RetrieveResponse
{
  unsigned int status; //Network byte order
  unsigned int bytesInFile; //Network byte order
  char fileBuffer[MAX]; //100kb buffer
};

struct DeleteRequest
{
  unsigned int secretKey; //Network byte order
  unsigned int type; //Network byte order
  //null terminated character string starting at the beginning of the buffer
  char fileName[81]; 
};

unsigned int DeleteResponse = 0;