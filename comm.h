#include<stdio.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>

void err_exit(char* str){
    perror(str);
    exit(-1);
}