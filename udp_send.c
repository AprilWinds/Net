#include<stdio.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<string.h>


int main(){
    
    int req_fd = socket(AF_INET,SOCK_DGRAM,0);

    struct sockaddr_in req;
    inet_pton(AF_INET,"127.0.0.1",&req.sin_addr.s_addr);
    req.sin_port = htons(7777);
    req.sin_family = AF_INET;

    connect(req_fd,&req,sizeof(req));
    while(1){
        //sendto(req_fd,"123",3,0,NULL,NULL);
        send(req_fd,"123",3,0);
        sleep(2);
    }
}