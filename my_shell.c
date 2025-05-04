#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<readline/readline.h>
#include<readline/history.h>

#define MAX_ARGS 64

int main()
{
    while(1){
        char* input = readline("> ");
        if(!input){
            break;
        }
        if(strlen(input)==0){
            free(input);
            continue;
        }

        add_history(input);
        /*Save input to history for arrow keys*/

        //Parse input into arguments
        char* args[MAX_ARGS];
        int arg_count=0;
        char *token = strtok(input," ");
        while(token && arg_count < MAX_ARGS-1)
        {
            args[arg_count++]=token;
            token= strtok(NULL," ");
        }
        args[arg_count]=NULL;

        //Built-in command: exit
        if(strcmp(args[0],"exit")==0){
            free(input);
            break;
        }

        //Built in cd command
        if(strcmp(args[0],"cd")==0){
            if(args[1]){
                if(chdir(args[1])!=0){
                    perror("cd");
                }
            }else{
                fprintf(stderr,"cd: expected argument\n");
            }
            free(input);
            continue;
        }

        //External command
        pid_t pid=fork();
        if(pid==0){
            execvp(args[0],args);
            perror("execvp failed");
            exit(1);
        }else if(pid>0){
            wait(NULL);
        }else{
            perror("fork failed");
        }

        free(input);
    }
    return 0;
}