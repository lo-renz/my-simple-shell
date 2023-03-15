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
            *arg++ = strtok(buf,SEPARATORS); // change the inputs into tokens.

            while((*arg++ = strtok(NULL, SEPARATORS))); // last entry will be NULL

            io_redirection(argc, args);
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
                *arg++ = strtok(buf,SEPARATORS); // change the inputs into tokens.

                while((*arg++ = strtok(NULL, SEPARATORS))); // last entry will be NULL

                io_redirection(argc, args);
            }
        }
        return 0;
    }
}