#include "../comm.h"
#include <sys/epoll.h>
#include <signal.h>

void pipe_handler(){
    printf("capture pipe signal,exit\n");
    err_exit("pipe");
}


int start_server(const char* ip_str, uint8_t port){
    struct sockaddr_in ser;
    inet_pton(AF_INET,ip_str,&ser.sin_addr);
    ser.sin_port = htons(port);
    ser.sin_family = AF_INET;

    int listen_fd = socket(AF_INET,SOCK_STREAM,0);
    if( listen_fd < 0 ) 
        err_exit("socket");
    
    if( bind(listen_fd,&ser, sizeof(ser))<0 )
        err_exit("bind");

    if( listen(listen_fd,128)<0)
        err_exit("listen");
    return listen_fd;
}


int main(int argc, char** argv){
    if(argc != 3){
        printf("plz input [ip] [port]\n"); 
        err_exit("arg");
    }
    int listen_fd = start_server(argv[1],atoi(argv[2]));
    struct epoll_event ev[128];

    ev[0].data.fd = listen_fd;
    ev[0].events = EPOLLIN;
    
    int ep_fd = epoll_create(0);
    epoll_ctl(ep_fd,EPOLL_CTL_ADD,listen_fd,&ev[0]);

    while(1){
        
        int ep_n = epoll_wait(ep_fd,&ev,128,-1);
        if( ep_n<0 )
            err_exit("epoll_wait");

        for(int i=0; i<ep_n; i++){
            int ev_fd = ev[i].data.fd;
            
            if(ev[i].events & EPOLLIN){
                if(ev_fd == listen_fd){
                    struct sockaddr_in cli;
                    socklen_t cli_len = sizeof(cli);
                    int new_fd = accept(listen_fd,&cli,&cli_len);
                    if( new_fd <0 )
                        err_exit("accept");
                    else
                        printf("receive connection\n");
                    
                    struct epoll_event new_ev;
                    new_ev.data.fd = new_fd;
                    new_ev.events = EPOLLIN | EPOLLET;  
                    epoll_ctl(ep_fd,EPOLL_CTL_ADD,new_fd,&new_ev);
                }else{
                    char buf[1024] = {0};
                    int rn = read(ev_fd,buf,3);
                    if(rn<0)
                        err_exit("read");
                    buf[rn] = 0;
                    printf("receive: %s\n",buf);
                }
            }

        }
        
    }
}