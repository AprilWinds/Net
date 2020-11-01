#include "keep.h"

#define MAXLINE 4096
#define KEEP_ALIVE_TIME 10
#define KEEP_ALIVE_INTERVAL 3
#define KEEP_ALIVE_PROBETIMES 3



int main(int argc, char** argv){
    if (argc !=  2){
        perr_ex("arg error");
    }
    
    struct sockaddr_in cli;
    bzero(&cli,sizeof(cli));
    cli.sin_family = AF_INET;
    cli.sin_port = htons(54321);
    inet_pton(AF_INET,argv[1],&cli.sin_addr);

    int con_fd = socket(AF_INET,SOCK_STREAM,0);
    bind(con_fd,&cli,sizeof(cli));
    int en = connect(con_fd,&cli,sizeof(cli));
    if(en < 0)  perr_ex("connect");

    char recv_line[MAXLINE +1 ];
    int n;
    fd_set readmask, allreads;

    struct timeval tv;
    int heatbeats = 0;
    tv.tv_sec = KEEP_ALIVE_TIME;
    tv.tv_usec = 0;
    
    messageObject msg;
    FD_ZERO(&allreads);
    FD_SET(con_fd,&allreads);

    while(1){ 
        readmask = allreads;
        int rc = select(con_fd+1, &readmask,NULL,NULL,&tv);
        if (rc < 0) perr_ex("select failed");
        if (rc == 0) {
            if(++heatbeats > KEEP_ALIVE_PROBETIMES)
                perr_ex("con");
            printf("sending heaetbeat #%d\n",heatbeats);
            msg.type = htonl(MSG_PING);
            rc = send(con_fd,&msg,sizeof(msg),0);
            if (rc < 0) perr_ex("send");
            tv.tv_usec = KEEP_ALIVE_INTERVAL;
            continue;
        }

        if (FD_ISSET(con_fd,&readmask)){
        
            n = read(con_fd,recv_line,MAXLINE);
            if (n < 0) perr_ex("read");
            printf("receive heartbeat\n");
            tv.tv_sec = KEEP_ALIVE_TIME;
            heatbeats = 0;
        }
    }

}