/*
Student Name: Renso Guilalas
Student ID: 2142218
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "myshell.h"
#define MAX_BUFFER 1024                        // max line buffer
#define MAX_ARGS 64                            // max # args
#define SEPARATORS " \t\n"                     // token separators
extern char ** environ;                        // array of char *, terminated by NULL // from lab_04 


// print the current working directory.
void pwd() {
    char d[MAX_BUFFER];
    getcwd(d, sizeof(d));
    printf("%s\n", d);
}

// change the current default directory.
void cd_cmd(char ** args) {

    char dir[MAX_BUFFER];
    if(args[1] == NULL) { // if no directory is specified then print he cwd.
        strcpy(dir, ".");
    }
    else { // if a directory is specified then change to that directory.
        strcpy(dir, args[1]);
        chdir(dir);

        // This changes the environment after changing directory.
        char newdir[MAX_BUFFER];
        getcwd(newdir, sizeof(newdir));
        setenv("PWD", newdir, 1);
    }

    pwd();
}

// clear the screen.
void clr() {
    system("clear");
}

// list the contents of directory.
void dir(char ** args) {
    char dir[MAX_BUFFER];
    if(args[1] == NULL) {
        strcpy(dir, ".");
    }
    else {
        strcpy(dir, args[1]); // getting the directory from the args.
    }
    char command[MAX_BUFFER] = "ls -al ";
    strcat(command, dir);
    system(command);
}

// list all the environment strings.
void environ_cmd() {
    for(int i = 0; environ[i] != NULL; ++i) {
        printf("%s\n", environ[i]);
    }
}

// echo on the display followed by a new line.
void echo(char ** args) {
    char ** output = args;
    output += 1;
    while(*output) { // while there are still args after "echo", print them.
        printf("%s ", *output++);
    }
    printf("\n");
}

// display the user manual using the more filter.
void help() {
}

// pause operation of the shell until "Enter" is pressed.
void pause_cmd() {
    printf("Press enter to continue...");
    while(getchar() != '\n'); // waiting for the user to press "enter"
}

// [1] 
void external_cmd(char ** args) {
    pid_t pid = 0;
    int status;

    pid = fork();
    if(pid == 0) {
        execvp(args[0], args); // executing the command specified 
    }
    if(pid < 0) {
        perror("Error!");
    }
    else{
        waitpid(pid, &status, 0);
    }
}

/*
check for I/O redirection
if I/O redirection is present then execute with I/O redirection
else execute internal or external commands
*/
void io_redirection(int argc, char ** args) {
     // checking for I/O redirection
    char * inputfile = NULL;
    char * outputfile = NULL;
    int append = 0;

    for(int i = 0; args[i+1]; ++i) { // [1]

        if(!strcmp(args[i], "<")) { // input redirection
            inputfile = args[i+1];
            args[i] = NULL;
            break;
        }
        else if(!strcmp(args[i], ">")) { // output redirection by truncating
            outputfile = args[i+1];
            args[i] = NULL;
            break;
        }
        else if(!strcmp(args[i], ">>")) { // output redirection by appending
            outputfile = args[i+1];
            append = 1;
            args[i] = NULL;
            break;
        }
    }

    if(inputfile != NULL || outputfile != NULL) { // [1]
        // executing command with I/O redirection
        pid_t pid = fork();

        if(pid == -1) {
            perror("fork error");
        }
        else if(pid == 0) {
            //child process
            if(inputfile) {
                // input redirection
                FILE * fp = fopen(inputfile, "r");

                if(!fp) {
                    perror("input file open error");
                    exit(EXIT_FAILURE);
                }

                dup2(fileno(fp), STDIN_FILENO);
                fclose(fp);
            }

            if(outputfile) {
                // output redirection
                FILE * fp;

                if(append) {
                    fp = fopen(outputfile, "a");
                }
                else {
                    fp = fopen(outputfile, "w");
                }

                if(!fp) {
                    perror("output file open error");
                    exit(EXIT_FAILURE);
                }

                dup2(fileno(fp), STDOUT_FILENO);
                fclose(fp);
            }

            // execute command
            execvp(args[0], args);

            // if execvp returns, there was an error
            perror(args[0]);
            exit(EXIT_FAILURE);
        }
        else {
            // parent process
            int status;
            waitpid(pid, &status, 0);
        }
    }
    else {
        // internal commands and external commands
        cmds(args, argc);
    }
}

typedef struct {
    char * name;
    void (*func)(char ** argv);
} Command;

// an array of Command structs for internal commands
Command internal_cmds[] = {
    {"pwd", pwd},
    {"cd", cd_cmd},
    {"clr", clr},
    {"dir", dir},
    {"environ", environ_cmd},
    {"echo", echo},
    {"help", help},
    {"pause", pause_cmd}
};

void cmds(char ** args, int argc) {
    for(int i = 0; i < sizeof(internal_cmds) / sizeof(Command); ++i) {
        if(!(strcmp(args[0], internal_cmds[i].name))) {
            internal_cmds[i].func(args);
            return;
        }
    }
    external_cmd(args);
}

/*
References:
[1] segmentfault, "Creating Shell in C - Piping and External Commands", StackOverflow, Jul. 2021. [Online]. Available: https://stackoverflow.com/questions/68289675/creating-shell-in-c-piping-and-external-commands. [Accessed: Mar. 13, 2023].
*/