/*
Student Name: Renso Guilalas
Student ID: 2142218
******************************************************************
I understand that the University regards breaches of academic integrity and plagiarism as grave and serious.
I have read and understood the DCU Academic Integrity and Plagiarism Policy. I accept the penalties that may be imposed should I engage in practice or practices that breach this policy.

I have identified and included the source of all facts, ideas, opinions and viewpoints of others in the assignment references. Direct quotations, paraphrasing, discussion of ideas from books, journal articles, internet sources, module text, or any other source whatsoever are acknowledged and the sources cited are identified in the assignment references.

I declare that this material, which I now submit for assessment, is entirely my own work and has not been taken from the work of others save and to the extent that such work has been cited and acknowledged within the text of my work.
******************************************************************/

#include "myshell.h"

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

// pause operation of the shell until "Enter" is pressed.
void pause_cmd() {
    printf("Press enter to continue...");
    while(getchar() != '\n'); // waiting for the user to press "enter"
}

// to execute ay external commands.
void external_cmd(char ** args) {
    pid_t pid = 0;
    int status;
    bool background = false; // for background execution

    for(int i = 0; args[i+1]; ++i) {
        if(!strcmp(args[i], "&")) {
            background = true;
            args[i] = NULL;
        }
    }

    pid = fork();
    if(pid == 0) {
        execvp(args[0], args); // executing the command specified 
    }
    if(pid < 0) {
        perror("Error!");
    }
    else{
        if(!background) { // wait for the child process to complete, unless it is run in the background.
            waitpid(pid, &status, 0);
        }
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
    bool background = false;

    // if I/O redirection is detected in the command line, the inputfile or outputfile is assigned accordingly and the operators are removed from the command line.
    // if background execution is detected, the background is set to true and the ampersand (&) is removed from the command line.
    for(int i = 0; args[i+1]; ++i) { 

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
        else if(!strcmp(args[i], "&")) { // if an '&' is in the line then background execution is set to true
            background = true;
            args[i] = NULL;
        }
    }

    if(inputfile != NULL || outputfile != NULL) {
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

                if(append) { // appending to the file
                    fp = fopen(outputfile, "a");
                }
                else { // truncating to the file
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
            int status;
 
            // wait for the child process to complete, unless it is run in the background.
            if(!background) {
                waitpid(pid, &status, 0);
            }
        }
    }
    else {
        // internal commands and external commands
        cmds(args, argc);
    }
}

// struct for the internal commands
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
    {"pause", pause_cmd}
};

void cmds(char ** args, int argc) { // the function that executes either the internal or external commands.
    for(int i = 0; i < sizeof(internal_cmds) / sizeof(Command); ++i) { // for loop that iterates through the tokens
        if(!(strcmp(args[0], internal_cmds[i].name))) { // if the first arg is equal to a command with the same name then that command is executed
            internal_cmds[i].func(args);
            return;
        }
    }
    external_cmd(args); // an external command is run if none of the internal commands are executed
}