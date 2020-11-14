#include<stdio.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<string.h>

int main(){

    int listen_fd = socket(AF_INET,SOCK_DGRAM,0);

    struct sockaddr_in ser;
    bzero(&ser,sizeof(ser));
    ser.sin_addr.s_addr  = INADDR_ANY;
    ser.sin_family = AF_INET;
    ser.sin_port = htons(7777);
    
    bind(listen_fd,&ser,sizeof(ser));
    listen(listen_fd,5);
    struct sockaddr_in cli;
    socklen_t cli_len = sizeof(cli);
    int rec_fd = accept(listen_fd,&cli,&cli_len);
    
    char msg[1024] = {0};
    while(1){
        int n = recvfrom(rec_fd,msg,10,0,&cli,&cli_len);
        if(n >0){
            msg[n] = '\0';
            printf("receive %s\n",msg);
        }
        sleep(4);
    }
}   