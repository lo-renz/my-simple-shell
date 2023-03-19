/*
Student Name: Renso Guilalas
Student ID: 2142218
******************************************************************
I understand that the University regards breaches of academic integrity and plagiarism as grave and serious.
I have read and understood the DCU Academic Integrity and Plagiarism Policy. I accept the penalties that may be imposed should I engage in practice or practices that breach this policy.

I have identified and included the source of all facts, ideas, opinions and viewpoints of others in the assignment references. Direct quotations, paraphrasing, discussion of ideas from books, journal articles, internet sources, module text, or any other source whatsoever are acknowledged and the sources cited are identified in the assignment references.

I declare that this material, which I now submit for assessment, is entirely my own work and has not been taken from the work of others save and to the extent that such work has been cited and acknowledged within the text of my work.
******************************************************************/

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
void pause_cmd();
void external_cmd();
void io_redirection(int argc, char ** args);
void cmds(char ** args, int argc);