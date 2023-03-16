/*
Student Name: Renso Guilalas
Student ID: 2142218
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>
#define MAX_BUFFER 1024                        // max line buffer
#define MAX_ARGS 64                            // max # args
#define SEPARATORS " \t\n"                     // token separators
extern char ** environ;                        // array of char *, terminated by NULL // from lab_04 

void pwd();
void cd_cmd(char ** args);
void clr();
void dir(char ** args);
void environ_cmd();
void echo();
void help();
void pause_cmd();
void external_cmd();
void io_redirection(int argc, char ** args);
void cmds(char ** args, int argc);