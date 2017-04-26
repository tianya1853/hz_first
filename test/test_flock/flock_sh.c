#include <stdio.h>  
#include <stdlib.h>  
#include <sys/file.h>  
#include <unistd.h>  //sleep


#define MAX_SIZE 100  
  
int main()  
{  
    FILE *fp;  
  
    int i;  
  
    char str[MAX_SIZE];  
  
    fp = fopen("hello.txt","r");  
  
    if(fp == NULL)  
    {  
        printf("open file error!\n");  
        exit(1);  
    }  
  
    i = fileno(fp);  
  
     if(-1 == flock(i,LOCK_SH))  
     {  
         printf("failing to lock!\n ");  
     }  
  
     if(0 == flock(i,LOCK_SH))  
     {  
         printf("lock success!\n");  
     }  
  
     fread(str,MAX_SIZE,1,fp);  
  
     printf("%s\n",str);  
  
     sleep(20);  
  
     fclose(fp);  
  
     flock(i,LOCK_UN);  
  
    return 0;  
}  
