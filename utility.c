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
void dir(int argc, char ** args) {
    char dir[MAX_BUFFER];
    if(argc == 1) {
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
void echo(int argc, char ** args) {
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
References:
[1] segmentfault, "Creating Shell in C - Piping and External Commands", StackOverflow, Jul. 2021. [Online]. Available: https://stackoverflow.com/questions/68289675/creating-shell-in-c-piping-and-external-commands. [Accessed: Mar. 13, 2023].
*/