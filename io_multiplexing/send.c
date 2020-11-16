
#include "../comm.h"
#include <signal.h>

void  handle(){
    printf("receive sigpipe\n");
}




int main(){

    signal(SIGPIPE,handle);
    int req_fd = socket(AF_INET,SOCK_STREAM,0);

    struct sockaddr_in cli;
    bzero(&cli,sizeof(cli));
    inet_pton(AF_INET,"127.0.0.1",&cli.sin_addr);
    cli.sin_port = htons(8000);
    cli.sin_family = AF_INET;
    int e = connect(req_fd,&cli,sizeof(cli));
    if(e <0) perror("connect");

    while(1){
       int n = send(req_fd,"abc",3,0);
       if(n <= 0) perror("wr");
       sleep(2);
    }    
}
