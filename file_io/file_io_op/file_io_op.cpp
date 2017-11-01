#include <iostream>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

using namespace std;

int main()
{
    //定义缓存空间.
    char buf[10] = {0};
    int flags;
    int ret;

    if(flags = fcntl(STDIN_FILENO, F_GETFL, 0) < 0)
    {
        perror("fcnt1 error!\n");
    }
    //flags |= O_NONBLOCK;

    if(fcntl(STDIN_FILENO, F_SETFL, flags) < 0)
    {
        perror("fnct1 error!\n");
    }

    while(1)
    {
        sleep(1);
        ret = read(STDIN_FILENO, buf, sizeof(buf));
        if(ret < 0)
        {
            perror("read error!\n");
        }
        cout << "ret = " << ret << endl; 
        
        ret = write(STDOUT_FILENO, buf, sizeof(buf));
        if(ret < 0)
        {
            perror("write error!\n");
        }
        memset(buf, 0, sizeof(buf));
        
    }
    return 0;
}
