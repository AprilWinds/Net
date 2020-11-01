#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/select.h>
#include <fcntl.h>
typedef struct {
    uint32_t type;
    char data[1024];
} messageObject;

void perr_ex(const char* p){
    perror(p);
    exit(1);
}


#define MSG_PING  1
#define MSG_PONG  2
#define MSG_TYPE1 11
#define MSG_TYPE2 21