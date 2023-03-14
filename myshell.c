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
#include <sys/wait.h>
#include "myshell.h"
#define MAX_BUFFER 1024                        // max line buffer
#define MAX_ARGS 64                            // max # args
#define SEPARATORS " \t\n"                     // token separators
extern char ** environ;                        // array of char *, terminated by NULL // from lab_04 

int main (int argc, char ** argv)
{
    char buf[MAX_BUFFER];                      // line buffer
    char * args[MAX_ARGS];                     // pointers to arg strings
    char ** arg;                               // working pointer thru args
    char prompt[MAX_BUFFER];                    // shell prompt
    /* keep reading input until "quit" command or EOF of redirected input */

    // to check if there is a batchfile
    // check if a command line argument is provided
    if (argc > 1) {
        // open the batch file
        FILE *batchfile = fopen(argv[1], "r");
        if (batchfile == NULL) {
            perror("Failed to open batchfile");
            return 1;
        }
        // read lines from batchfile until EOF is reached
        while(fgets(buf, MAX_BUFFER, batchfile)) {
            // tokenize the input into args array
            arg = args;
            *arg++ = strtok(buf,SEPARATORS);   // change the inputs into tokens.

            while((*arg++ = strtok(NULL, SEPARATORS))); // last entry will be NULL

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
                // internal commands
                if(args[0]) {

                    if(!strcmp(args[0], "cd")) { // "cd" command
                        cd_cmd(args);
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

                    else {
                        external_cmd(args);
                        continue;
                    }
                }
            }
        }
        // close the batchfile
        fclose(batchfile);
    }
    else {
        while(!feof(stdin)) { 
            /* get command line from input */
            sprintf(prompt, "%s%s ", getcwd(NULL, 0), " ->"); // adding the cwd to the prompt
            fputs(prompt, stdout); // write prompt

            if(fgets (buf, MAX_BUFFER, stdin)) { // read a line
                // tokenize the input into args array
                arg = args;
                *arg++ = strtok(buf,SEPARATORS);   // change the inputs into tokens.

                while((*arg++ = strtok(NULL, SEPARATORS))); // last entry will be NULL

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
                    // internal commands
                    if(args[0]) {

                        if(!strcmp(args[0], "cd")) { // "cd" command
                            cd_cmd(args);
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

                        else {
                            external_cmd(args);
                            continue;
                        }
                    }
                }

            }
        }
        return 0;
    }
}

/*
References:
[1] Craig Estey, "Redirecting I/O in a custom shell program written in C", StackOverflow, Oct. 2018. [Online]. Available: https://stackoverflow.com/questions/52939356/redirecting-i-o-in-a-custom-shell-program-written-in-c. [Accessed: Mar. 14, 2023].
*/