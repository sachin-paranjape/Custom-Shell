#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

#define MAX_CMD_LEN 1024
#define MAX_ARGS 64

int main()
{
    char input[MAX_CMD_LEN];

    while(1){
        printf("> ");
        fflush(stdout);

        if(!fgets(input,MAX_CMD_LEN,stdin)){
            break;
        }

        //Remove newline
        input[strcspn(input,"\n")]=0;

        //Skip empty input
        if(strlen(input)==0)
            continue;
        
        //Tokenize input into args[]
        char* args[MAX_ARGS];
        int arg_count=0;
        char *token = strtok(input," ");

        while(token!=NULL && arg_count < MAX_ARGS-1)
        {
            args[arg_count++]=token;
            token= strtok(NULL," ");
        }
        args[arg_count]=NULL;

        //Built-in command: exit
        if(strcmp(args[0],"exit")==0){
            break;
        }

        //Built in cd command
        if(strcmp(args[0],"cd")==0){
            if(args[1]==NULL){
                fprintf(stderr,"cd:expected argument\n");
            }
            else{
                if(chdir(args[1])!=0){
                    perror("cd");
                }
            }
            continue;
        }

        //Fork and exec for external commands
        pid_t pid=fork();

        if(pid==0){
            execvp(args[0],args);
            perror("execvp failed");
            exit(1);
        }else if(pid > 0){
            wait(NULL);
        }else{
            perror("fork failed");
        }
    }

    return 0;
}