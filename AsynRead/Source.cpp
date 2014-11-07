#include"aSynRead.h"

void readFile(int )//signal handle function
{
    printf("load file success!\n");
}

int main(int __argc, char** __argv)
{
    char buff[255];
    size_t readed_size;

    signal(SIGINT, readFile);
    aSynRead("asynread.txt", buff, 255, &readed_size, NULL);
    
    //do some other things...
    for(size_t i = 0; i < 100000; ++i)
    {
        for(size_t j = 0; j < 100000; ++j)
        {
            size_t ans = 123123 * 213321;
        }
    }
    //do some other things...

    buff[readed_size] = '\0';
    printf("read %d byte(s): %s\n", readed_size, buff);
    return 0;
}