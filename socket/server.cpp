#include "common.h"

using namespace std;
void SetNonblock(int socket_fd)
{
    int flags = fcntl(socket_fd, F_GETFL, 0);
    if(flags < 0)
    {
        perror("get socket_fd flags error!");
        exit(0);
    }

    if(fcntl(socket_fd, F_SETFL, flags | O_NONBLOCK) < 0 )
    {
        perror("set socket_fd flags error!");
        exit(0);
    }
}

int main()
{ 
    //获取socket
    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    //初始化sockadd_in
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8001);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
   

    //bind服务端端口号和sockaddr_in结构。
    if(bind(listen_fd,(const struct sockaddr*)&addr, sizeof(addr)) == -1)
    {
        cout << "bind socket error!" << endl;
    }

    //监听端口。
    if(listen(listen_fd,SOMAXCONN) == -1)
    {
        cout << "listen socket error!" << endl;
    }

    struct sockaddr_in client_addr;

    char buf[512];
    int read_bytes;
    int write_bytes;
    socklen_t socket_len = sizeof(client_addr);
    while(true)
    {
        int client_fd = accept(listen_fd, (struct sockaddr*)&client_addr, &socket_len);
        if(client_fd == -1)
        {
            cerr << "accpet error..." << endl;
        }
        
        cout << "test flags" << endl;
        cout << "Client info: " << inet_ntoa(client_addr.sin_addr) << ":" << ntohs(client_addr.sin_port) << endl;
        
        memset(buf, 0, sizeof(buf));
        while((read_bytes = read(client_fd, buf, sizeof(buf))) > 0)
        {
            cout << buf << endl;
            
            write_bytes = write(client_fd, buf, read_bytes);
            if(write_bytes < 0)
            {
                cerr << "write error!" << endl;
            }
            memset(buf, 0, sizeof(buf));
        }
        if(read_bytes == 0)
        {
            cerr << "client connect closed..." << endl;
            close(client_fd);
        }
        else if(read_bytes == -1)
        {
            cerr << "read bytes error!" << endl;
        }
        
    }
    close(listen_fd);
    //接受客户端的连接。
    return 0;
}
