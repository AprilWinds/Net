#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<fcntl.h>

size_t readn(int fd, void* buf, size_t len){
    size_t count = len ;
    size_t res =0;
    while(count > 0){
        int rn = read(fd,buf,count);
        if(rn < 0){
            if(errno == EINTR){
                continue;
            }            
            return -1;
        }else if (rn == 0){
            break;
        }
        count -=rn;    
        res+=rn;
    }
    return res;
}
size_t readline(int fd, void* buf){
    size_t count = 0;
    while(1){
        int rn = read(fd,buf,1);
        if(rn == 0){
            break;
        }else if(rn == -1){
            return -1;
        }
        if(*(char*)buf == '\n'){
            break;
        }
        buf++;
        count++;
    }
    return count;
}


int main(){
    char b[1024];
    int fd = open("./1.txt",O_RDWR);
    printf("%d\n",readline(fd,b));
}