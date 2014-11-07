#include<stdio.h>
#include<process.h>
#include<errno.h>
#include<string.h>
#include<signal.h>

typedef size_t (*ReadCB)(FILE* hd);//call-back function

typedef struct 
{
    FILE* file;
    char * buff; 
    size_t buff_size; 
    size_t* readed_size;
    ReadCB call_back;
}aSynReadStruct;

bool aSynRead(const char * file,
              char * buff, 
              size_t buff_size, 
              size_t * readed_size,
              ReadCB call_back);