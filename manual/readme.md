myshell(1)                                                                              General Commands Manual

NAME

        myshell - simple shell

OPERATIONS AND COMMANDS

        pwd - Print the current working directory.

        cd - Changes the working directory, if one is specified, otherwise if no working directory is specified then the current working directory is printed.

        clr - Clear all the contents on the screen.

        dir - List all the files in the current working directory (including hidden files).

        environ - List all the environment strings.

        echo - Echo all the string entered after the command argument.

        help - Display the manual.

ENVIRONMENT CONCEPTS [1]

        The environment is an array of strings. An array which contains information of the current state of your terminal in name-value pairs.
        This would include information such as the current user, your previous working directory, the current working directory, etc.
        When command like 'cd' is executed the name-value pairs would update to contain the updated information. 

        To view this information in this shell you execute the 'environ' command.
                [command]
        Replace [command] with 'environ' to view information on your current environment.

I/O REDIRECTION [2]

        Input Redirection
                Input redirection is taking input from a different source. 
                Input redirection can be applied with this terminal by the form:
                        [command] < [file]
                where [command] is the name of the command you want to execute and [file] is the name of the file from which you want to take inputs from.

        Output Redirection
                Output redirection is the opposite of input redirection.
                Where it redirects the output of a command into another file, or wherever you specify, instead of to standard output.
                Output redirection can be applied with this terminal by the form:
                        [command] > [file]
                Where [command] is the name of the command you want to execute and [file] is the name of the file you want to send your output.
                The use of only one '>' symbol is for truncating the output to the file.
 
                        [command] >> [file]
                Whereas with the use of two '>' symbols is for appending the output to the file.
 
PROCESS CONCEPT
        SOME TEXT

THE DIFFERENCES BETWEEN BACKGROUND AND FOREGROUND EXECUTION
        SOME TEXT


References:
[1] A. Robbins, "Bash Pocket Reference," O'Reilly Media, 2016. [Online]. Available: https://books.google.ie/books?hl=en&lr=&id=dzBCH3x6fYEC&oi=fnd&pg=PT7&dq=bash&ots=iXm-scjsFW&sig=vdaiZZqTVGr7ZhBonItTBEzXkuM&redir_esc=y#v=onepage&q=environment%20variables&f=false
[2] Y. Liu, Y. Yue, L. Guo, UNIX I/O System, I/O Redirection and Piping. In: UNIX Operating System. Springer, Berlin, Heidelberg, 2011, doi: 10.1007/978-3-642-20432-6_7.