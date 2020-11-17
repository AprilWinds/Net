

#include<errno.h>
#include<assert.h>
#include<string.h>
#include "../comm.h"
#include <sys/epoll.h>

static void usage(const char* proc)
{
	assert(proc);
	printf("usage: %s [ip] [port]\n",proc);
}
 
static int set_nonblock(int fd)
{
	int fl = fcntl(fd,F_SETFL);
	fcntl(fd,F_SETFL,fl|O_NONBLOCK);
}
 
int my_read(int fd,char* buf,int len)
{
	assert(buf);
	ssize_t total = 0;
	ssize_t s = 0;
	while((s = read(fd,&buf[total],len - 1 - total)) > 0&&errno != EAGAIN)
	{
		total += s;
	}
 
	return total;
}
 
int start_up(char* ip,int port)
{
	assert(ip);
	assert(port > 0);
 
	int sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock < 0)
	{
		perror("socket");
		exit(1);
	}
	
	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(port);
	local.sin_addr.s_addr = inet_addr(ip);
 
	if(bind(sock,(struct sockaddr*)&local,sizeof(local)) < 0)
	{
		perror("bind");
		exit(2);
	}
 
	if(listen(sock,5) < 0)
	{
		perror("listen");
		exit(3);
	}
 
	return sock;
}
 
int main(int argc,char* argv[])
{
	if(argc != 3)
	{
		usage(argv[0]);
		return 1;
	}
	int listen_sock = start_up(argv[1],atoi(argv[2]));
    struct sockaddr_in cli;
    socklen_t cli_len = sizeof(cli);
    
    int rc = accept(listen_sock,&cli,&cli_len);
    printf("%d\n",rc);
    while(1){
        
    }
}
