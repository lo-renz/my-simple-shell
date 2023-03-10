#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define MAX_BUFFER 1024                        // max line buffer
#define MAX_ARGS 64                            // max # args
#define SEPARATORS " \t\n"                     // token separators

// change the current default directory.
void cd() {
}

// clear the screen.
void clr() {
    system("clear");
}

// list the contents of directory.
void dir(char ** args) {
    char dir[MAX_BUFFER];
    strcpy(dir, args[1]); // getting the directory from the args.
    char command[MAX_BUFFER] = "ls -al ";
    strcat(command, dir);
    system(command);
}

// list all the environment strings.
void environ() {
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

// print the curretn working directory.
void pwd() { // code from https://www.ibm.com/docs/en/zos/2.3.0?topic=functions-getcwd-get-path-name-working-directory
    char d[1024];
    getcwd(d, sizeof(d));
    printf("%s\n", d);
}


int main (int argc, char ** argv)
{
    char buf[MAX_BUFFER];                      // line buffer
    char * args[MAX_ARGS];                     // pointers to arg strings
    char ** arg;                               // working pointer thru args
    char * prompt = "-> " ;                     // shell prompt
    /* keep reading input until "quit" command or eof of redirected input */

    while (!feof(stdin)) { 
        /* get command line from input */
        fputs (prompt, stdout); // write prompt

        if (fgets (buf, MAX_BUFFER, stdin )) { // read a line
            /* tokenize the input into args array */
            arg = args;
            *arg++ = strtok(buf,SEPARATORS);   // change the inputs into tokens.

            while ((*arg++ = strtok(NULL,SEPARATORS)));

            // last entry will be NULL 
            // this block of code is for the internal commands.
            if (args[0]) {

                if (!strcmp(args[0], "cd")) { // "cd" command
                    cd();
                    continue;
                }

                if (!strcmp(args[0], "clr")) { // "clear" command
                    clr();
                    continue;
                }

                if (!strcmp(args[0], "dir")) { // "dir" command
                    dir(args);
                    continue;
                }

                if (!strcmp(args[0], "environ")) { // "environ" command
                    environ();
                    continue;
                }

                if (!strcmp(args[0], "echo")) { // "echo" command
                    echo(args);
                    continue;
                }

                if (!strcmp(args[0], "help")) { // "help" command
                    help();
                    continue;
                }

                if (!strcmp(args[0], "pause")) { // "pause" command
                    pause_cmd();
                    continue;
                }

                if (!strcmp(args[0], "pwd")) { // "pwd" command
                    pwd();
                    continue;
                }

                if (!strcmp(args[0],"quit")) {  // "quit" command
                    break;
                }

                /* else pass command onto OS (or in this instance, print them out) */
                arg = args;
                while (*arg) {
                    fprintf(stdout,"%s ",*arg++);
                    fputs ("\n", stdout);
                }
            }
        }
    }
    return 0; 
}