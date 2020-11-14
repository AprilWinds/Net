#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>
#include<signal.h>




int main(){ 
    int listenfd = socket(AF_INET,SOCK_STREAM,0);

    struct sockaddr_in server_addr;
    bzero(&server_addr,sizeof(server_addr));
    server_addr.sin_port = htons(6666);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    int on = 1;
    setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));

    int er = bind(listenfd, &server_addr,sizeof(server_addr));
    if( er<0 ) {
         perror("bind"); exit(-1);
    }
    int er1 = listen(listenfd,5);
    if(er1< 0){
        perror("listen"); exit(-1);
    }

    struct sockaddr_in cli_addr;
    socklen_t cli_len = sizeof(cli_addr);
    int connfd = accept(listenfd,&cli_addr,&cli_len);

    char message[1024];   
    while(1){
        int n = read(connfd,message, 4);
        if(n<0){
            perror("read");
            exit(-1);
        } else if(n==0){
            perror("peep closed");
        }
        message[n] == '\0';
        printf("receive%s\n",message);
    }
}