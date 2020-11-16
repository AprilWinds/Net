#include "../comm.h"
#include <poll.h>


int main(){
    int listen_fd = socket(AF_INET,SOCK_STREAM,0);
    int stdin_fd = STDIN_FILENO;

    struct sockaddr_in ser;
    bzero(&ser,sizeof(ser));
    ser.sin_addr.s_addr = INADDR_ANY;
    ser.sin_port = htons(50001);
    ser.sin_family = AF_INET;
    bind(listen_fd,&ser,sizeof(ser));
    listen(listen_fd,5);

    struct pollfd events[2];
    events[0].fd = listen_fd;
    events[0].events = POLLIN;    
    events[1].fd = stdin_fd;
    events[1].events = POLLIN;

    char b[1024] = {0};
    while(1){
        int readly = poll(events,2,2);
        
        if(readly > 0){
            for(int i=0; i<2; i++){
                if(events[i].revents & POLLIN){
                    if(events[i].fd == listen_fd){
                        struct sockaddr_in cli;
                        socklen_t cli_len;                
                        int a_fd = accept(events[i].fd,&cli,&cli_len);
                        printf("connection ..%d\n",a_fd);
                      //  printf("con_ip: %s\n",inet_ntoa(cli.sin_addr));
                      //  printf("con_port:%u\n",ntohs(cli.sin_port));
                    }else{
                        
                        int n = read(events[i].fd,b,10);
                        b[n] = 0;
                        printf("%s\n",b);
                    }
                
                }
                
            }
        }
    }
    

}