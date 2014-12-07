#ifndef FORMATS_H
#define FORMATS_H

const int MAX = 102401; //100kb

enum {STORE, RETRIEVE, DELETE, LIST};

struct FileBuffer
{
  char fileBuffer[MAX]; //100kb buffer
};

struct StoreRequest
{
  //null terminated character string starting at the beginning of the buffer
  char fileName[81]; 
  unsigned int bytesInFile; //Network byte order
  char fileBuffer[MAX]; //100kb buffer
};

struct RetrieveRequest
{ 
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
  unsigned int type; //Network byte order
  //null terminated character string starting at the beginning of the buffer
  char fileName[81]; 
};

struct ListRequest
{
  unsigned int type; //Network byte order
  //null terminated character string starting at the beginning of the buffer
  char fileName[81]; 
};

struct ListResponse
{
  unsigned int status; //Network byte order
  unsigned int bytesInFile; //Network byte order
  char fileBuffer[MAX]; //100kb buffer
};

#endif