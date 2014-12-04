const int MAX = 102400; //100kb

typedef enum {STORE, RETRIEVE, DELETE, LIST};

typedef struct myFile
{
  char fileBuffer[MAX]; //100kb buffer
} mFile;

typedef struct StoreRequest
{
  unsigned int secretKey; //Network byte order
  unsigned int type = STORE; //Network byte order
  //null terminated character string starting at the beginning of the buffer
  char fileName[81]; 
  unsigned int bytesInFile; //Network byte order
  char fileBuffer[MAX]; //100kb buffer
};

unsigned int StoreResponse = 0;

typedef struct RetrieveRequest
{ 
  unsigned int secretKey; //Network byte order
  unsigned int type; //Network byte order
  //null terminated character string starting at the beginning of the buffer
  char fileName[81];
};

typedef struct RetrieveResponse
{
  unsigned int status; //Network byte order
  unsigned int bytesInFile; //Network byte order
  char fileBuffer[MAX]; //100kb buffer
};

typedef struct DeleteRequest
{
  unsigned int secretKey; //Network byte order
  unsigned int type; //Network byte order
  //null terminated character string starting at the beginning of the buffer
  char fileName[81]; 
};

unsigned int DeleteResponse = 0;