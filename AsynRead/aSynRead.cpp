#include"aSynRead.h"

void readFile(void* asyn_read_struct)
{
    aSynReadStruct* file_info = (aSynReadStruct *)asyn_read_struct;
    size_t size = fread(file_info->buff, 1, file_info->buff_size, file_info->file);
    if(errno != 0)
    {
        fprintf(stderr, "Error reading file: %s\n", strerror(errno));
        fclose(file_info->file);
        exit(errno);
    }
    if(file_info->readed_size != NULL)
    {
        *file_info->readed_size = size;//return readed bytes
    }
    if(file_info->call_back != NULL)
    {
        file_info->call_back(file_info->file);//invoke call-back function
    }
    fclose(file_info->file);
    raise(SIGINT);//raise a interruption to infor main thread read filesuccess
}

bool aSynRead(const char * file,
              char * buff, 
              size_t buff_size, 
              size_t * readed_size,
              ReadCB call_back)
{
    FILE *file_handle = fopen(file, "r");
    if(file_handle == NULL)
    {
        fprintf(stderr, "Error open file: %s\n", strerror(errno));
        return false;
    }
    else
    {
        aSynReadStruct file_info = {file_handle, buff, buff_size, readed_size, call_back};
        _beginthread(readFile, 0, &file_info);//create a new thread and start it to read file
        return true;
    }
}