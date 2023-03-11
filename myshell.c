/*
Student Name: Renso Guilalas
Student ID: 21422182
********************************************************************
version: 1.0
date:    December 2003
author:  Ian G Graham
School of Information Technology
Griffith University, Gold Coast
ian.graham@griffith.edu.au
copyright (c) Ian G Graham, 2003. All rights reserved.
This code can be used for teaching purposes, but no warranty,
explicit or implicit, is provided.
*******************************************************************/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define MAX_BUFFER 1024                        // max line buffer
#define MAX_ARGS 64                            // max # args
#define SEPARATORS " \t\n"                     // token separators
extern char ** environ;                        // array of char *, terminated by NULL // from lab_04 

// print the curretn working directory.
void pwd() { // code from https://www.ibm.com/docs/en/zos/2.3.0?topic=functions-getcwd-get-path-name-working-directory
    char d[MAX_BUFFER];
    getcwd(d, sizeof(d));
    printf("%s\n", d);
}

// change the current default directory.
void cd_cmd(int argc, char ** args) {

    // if a directory is specified then change to that directory.
    char dir[MAX_BUFFER];
    char buffer[MAX_BUFFER];
    strcpy(dir, args[1]);
    chdir(dir);

    // This changes the environment after changing directory.
    char newdir[MAX_BUFFER];
    getcwd(newdir, sizeof(newdir));
    setenv("PWD", newdir, 1);
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


int main (int argc, char ** argv)
{
    char buf[MAX_BUFFER];                      // line buffer
    char * args[MAX_ARGS];                     // pointers to arg strings
    char ** arg;                               // working pointer thru args
    char * prompt = "-> " ;                    // shell prompt
    /* keep reading input until "quit" command or eof of redirected input */

    while(!feof(stdin)) { 
        /* get command line from input */
        fputs (prompt, stdout); // write prompt

        if(fgets (buf, MAX_BUFFER, stdin )) { // read a line
            /* tokenize the input into args array */
            arg = args;
            *arg++ = strtok(buf,SEPARATORS);   // change the inputs into tokens.

            while((*arg++ = strtok(NULL, SEPARATORS)));

            // last entry will be NULL 
            // this block of code is for the internal commands.
            if(args[0]) {

                if(!strcmp(args[0], "cd")) { // "cd" command
                    cd_cmd(argc, args);
                    continue;
                }

                if(!strcmp(args[0], "clr")) { // "clear" command
                    clr();
                    continue;
                }

                if(!strcmp(args[0], "dir")) { // "dir" command
                    dir(argc, args);
                    continue;
                }

                if(!strcmp(args[0], "environ")) { // "environ" command
                    environ_cmd();
                    continue;
                }

                if(!strcmp(args[0], "echo")) { // "echo" command
                    echo(argc, args);
                    continue;
                }

                if(!strcmp(args[0], "help")) { // "help" command
                    help();
                    continue;
                }

                if(!strcmp(args[0], "pause")) { // "pause" command
                    pause_cmd();
                    continue;
                }

                if(!strcmp(args[0], "pwd")) { // "pwd" command
                    pwd();
                    continue;
                }

                if(!strcmp(args[0],"quit")) {  // "quit" command
                    break;
                }

                /* else pass command onto OS (or in this instance, print them out) */
                arg = args;
                while(*arg) {
                    fprintf(stdout,"%s ",*arg++);
                    fputs("\n", stdout);
                }
            }
        }
    }
    return 0; 
}