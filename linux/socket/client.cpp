#include "common.h"
using namespace std;
int main()
{
    //获取socket
   int client_fd = socket(AF_INET, SOCK_STREAM, 0);
   //初始化sockadd_in
   struct sockaddr_in addr;
   addr.sin_family = AF_INET;
   addr.sin_port = htons(8001);
   addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(connect(client_fd, (const struct sockaddr*)&addr, sizeof(addr)) != 0)
    {
        cout << "connect error!" << endl;;
        exit(0);
    }

    char buf[512];
    int ret;
    int real_size;
    //连接成功，开始读写数据
    while(1)
    {
        if(fgets(buf, sizeof(buf), stdin) == NULL)
        {
            cerr << "get data from stdin error!" << endl;;
            break;
        }

        real_size = write(client_fd, buf, sizeof(buf));
        if(real_size < 0)
        {
            cerr << "write error!" << endl;
        }

        memset(buf, 0, sizeof(buf));
       
        real_size = read(client_fd, buf, sizeof(buf));
        if(real_size < 0)
        {
            cerr << "read error! " << endl;;
        }

        cout << buf;
    }
    return 0;
}
