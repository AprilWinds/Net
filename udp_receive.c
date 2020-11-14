#include "comm.h"


int main(){

    int listen_fd = socket(AF_INET,SOCK_DGRAM,0);

    struct sockaddr_in ser;
    bzero(&ser,sizeof(ser));
    ser.sin_addr.s_addr  = INADDR_ANY;
    ser.sin_family = AF_INET;
    ser.sin_port = htons(7777);
    
    bind(listen_fd,&ser,sizeof(ser));

    
    char msg[1024] = {0};
    while(1){
        //int n = recvfrom(rec_fd,msg,10,0,NULL,NULL);
        int n = recv(listen_fd,msg,2,0);
        if(n<0) err_exit("rec");
        printf("%d\n",n);
        if(n >0){
            msg[n] = '\0';
            printf("receive %s\n",msg);
        }
        sleep(4);
    }
}   