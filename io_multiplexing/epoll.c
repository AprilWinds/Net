#include "../comm.h"
#include <sys/epoll.h>


int main(){

    int listen_fd = socket(AF_INET,SOCK_STREAM,0);
    int stdin_fd = STDIN_FILENO;

    struct sockaddr_in ser;
    ser.sin_addr.s_addr = AF_INET;
    ser.sin_port = htons(8888);
    ser.sin_family = AF_INET;
    bind(listen_fd,&ser,sizeof(ser));
    listen(listen_fd,3);


    int epoll_fd = epoll_create(0); 
    
    struct epoll_event listen_ev;
    listen_ev.data.fd = listen_fd;
    listen_ev.events = EPOLLIN;

    struct epoll_event stdin_ev;
    listen_ev.data.fd = stdin_fd;
    listen_ev.events = EPOLLIN;
   
    epoll_ctl(epoll_fd,EPOLL_CTL_ADD,listen_fd,&listen_ev);
    epoll_ctl(epoll_fd,EPOLL_CTL_ADD,stdin_fd,&stdin_ev);
    
    
    struct epoll_event* ev_set;

    while(1){
        int n = epoll_wait(epoll_fd,ev_set,2,3);
        if ( n==0 ) printf("time out process\n");
        if (n >0){
            for(int i= 0; i<n;i++){
                if(ev_set[i].data.fd ==listen_fd){
                    struct sockaddr_in cli;
                    socklen_t cli_len = sizeof(cli);
                    accept(listen_fd,&cli,&cli_len);
                    printf("conn\n");
                }
            }
            
        }
    }
}
