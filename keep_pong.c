#include "keep.h"

#define MAXLINE 4096
#define KEEP_ALIVE_TIME 10
#define KEEP_ALIVE_INTERVAL 3
#define KEEP_ALIVE_PROBETIMES 3



int main(int argc, char** argv){
    if (argc !=  2){
        perr_ex("sleep arg error");
    }
    
    struct sockaddr_in ser;
    bzero(&ser,sizeof(ser));
    ser.sin_family = AF_INET;
    ser.sin_port = htons(54321);
    ser.sin_addr.s_addr=INADDR_ANY;

    int ser_fd = socket(AF_INET,SOCK_STREAM,0);
    bind(ser_fd,&ser,sizeof(ser));
    listen(ser_fd,5);
    

    struct sockaddr_in cli;
    socklen_t cli_len = sizeof(cli);
    int recv_fd = accept(ser_fd,&cli,&cli_len);

    messageObject msg;
    while(1){ 
        int n=read(recv_fd,&msg,sizeof(messageObject));
        if (n<0) perr_ex("read");
        if (n==0) perr_ex("cli close");

        if( ntohl(msg.type)  == MSG_PING){
            messageObject wr;
            wr.type = MSG_PONG;
            sleep(atoi(argv[1]));
            ssize_t rc = send(recv_fd,(char *)&wr,sizeof(wr),0);
            if(rc<0) perr_ex("send");
        }
    
    }

}