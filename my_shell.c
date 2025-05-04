#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

#define MAX_CMD_LEN 1024

int main()
{
    char command[MAX_CMD_LEN];

    while(1){
        printf("> ");
        fflush(stdout);

        if(!fgets(command,MAX_CMD_LEN,stdin)){
            break;
        }

        command[strcspn(command,"\n")]=0;

        if(strcmp(command,"exit")==0){
            break;
        }
        
        pid_t pid = fork();
        if(pid == 0){
            //Child process
            execlp(command,command,(char*)NULL);
            perror("execlp failed");
            exit(1);
        }else{
            //Parent process
            wait(NULL);
        }
    }

    return 0;
}