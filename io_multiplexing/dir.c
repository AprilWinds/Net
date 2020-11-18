#include<stdio.h>
#include<dirent.h>
#include<unistd.h>
#include<fcntl.h>

int main(){
    DIR*  dir_str = opendir("./");
    struct dirent* d;
    while( (d = readdir(dir_str))!= NULL){  
        printf(d->d_name);
        switch(d->d_type){
            case DT_LNK : printf(" link"); break;
            case DT_REG : printf(" regular"); break;
            case DT_DIR : printf(" dirent");
        }
        
        printf("\n");

    }
}