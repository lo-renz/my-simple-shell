/*
Student Name: Renso Guilalas
Student ID: 21422182
*******************************************************************
version: 1.0
date:    December 2003
author:  Ian G Graham
School of Information Technology
Griffith University, Gold Coast
ian.graham@griffith.edu.au
copyright (c) Ian G Graham, 2003. All rights reserved.
This code can be used for teaching purposes, but no warranty,
explicit or implicit, is provided.
*******************************************************************
I understand that the University regards breaches of academic integrity and plagiarism as grave and serious.
I have read and understood the DCU Academic Integrity and Plagiarism Policy. I accept the penalties that may be imposed should I engage in practice or practices that breach this policy.

I have identified and included the source of all facts, ideas, opinions and viewpoints of others in the assignment references. Direct quotations, paraphrasing, discussion of ideas from books, journal articles, internet sources, module text, or any other source whatsoever are acknowledged and the sources cited are identified in the assignment references.

I declare that this material, which I now submit for assessment, is entirely my own work and has not been taken from the work of others save and to the extent that such work has been cited and acknowledged within the text of my work.
*******************************************************************/

#include "myshell.h"

int main (int argc, char ** argv)
{
    char buf[MAX_BUFFER];                      // line buffer
    char * args[MAX_ARGS];                     // pointers to arg strings
    char ** arg;                               // working pointer thru args
    char prompt[MAX_BUFFER];                   // shell prompt
    /* keep reading input until "quit" command or EOF of redirected input */

    // to check if there is a batchfile,
    // check if a command line argument is provided
    if (argc > 1) {
        // open the batchfile and read it
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

            io_redirection(argc, args); // the function which checks for I/O redirection, as well as running either the internal or external commands
        }
        // close the batchfile
        fclose(batchfile);
    }
    else {
        // this code is to get the absolute path for the readme file
        // used for the help command
        char abpath[MAX_BUFFER]; // the absolute path for help()
        getcwd(abpath, sizeof(abpath));
        char command[MAX_BUFFER] = "";
        strcat(command, "cat ");
        strcat(command, abpath);
        strcat(command, "/../manual/readme.md | more -p"); // command for the help page, which pipes the contents of readme.md into the more command, displaying the contents of the file in the terminal window. 

        while(!feof(stdin)) { 
            /* get command line from input */
            sprintf(prompt, "%s%s ", getcwd(NULL, 0), " ->"); // adding the cwd to the prompt
            fputs(prompt, stdout); // write prompt

            if(fgets (buf, MAX_BUFFER, stdin)) { // read a line
                // tokenize the input into args array
                arg = args;
                *arg++ = strtok(buf,SEPARATORS); // change the inputs into tokens.

                while((*arg++ = strtok(NULL, SEPARATORS))); // last entry will be NULL

                if(!strcmp(args[0], "help")) { // implementation of help command for the manual
                    system(command);
                }

                io_redirection(argc, args); // the function which checks for I/O redirection, as well as running either the internal or external commands
            }
        }
        return 0;
    }
}