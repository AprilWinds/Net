
#include "../comm.h"
#include <signal.h>

void  handle(){
    printf("receive sigpipe\n");
}




int main(int argc, char** argv){
    if(argc < 3){
        err_exit("ip port");
    }

    signal(SIGPIPE,handle);
    int req_fd = socket(AF_INET,SOCK_STREAM,0);

    struct sockaddr_in cli;
    bzero(&cli,sizeof(cli));
    inet_pton(AF_INET,argv[2],&cli.sin_addr);
    cli.sin_port = htons(atoi(argv[3]));
    cli.sin_family = AF_INET;
    int e = connect(req_fd,&cli,sizeof(cli));
    if(e <0) perror("connect");

    while(1){
       int n = send(req_fd,"abcdefg",7,0);
       if(n <= 0) perror("wr");
       sleep(2);
    }    
}
