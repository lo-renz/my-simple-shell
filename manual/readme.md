NAME

        myshell - simple shell

OPERATIONS AND COMMANDS

        pwd - Print the current working directory.

        cd - Changes the working directory.
                cd [directory path]
                The current working directory will be changed to the one specified (if it exists).
                If no directory path is specified then the current working directory will be printed.

        clr - Clear all the contents on the screen.

        dir - List all the files in the current working directory (including hidden files).

        environ - List all the environment strings.

        echo - Echo all the string entered after the command argument.
                echo [string]

        help - Display the manual.
                To exit the manual either press 'enter' until the EOF is reached or press 'q'.

ENVIRONMENT CONCEPTS [1]

        The environment is an array of strings. An array which contains information of the current state of your terminal in name-value pairs.
        This would include information such as the current user, your previous working directory, the current working directory, etc.
        When command like 'cd' is executed the name-value pairs would update to contain the updated information. 

        An example of what this will look like:
                USER = The name of the current user that is logged in.
                HOME = The home directory.
                PWD = The current working directory.
                OLDPWD = The previous working directory.

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
 
PROCESS CONCEPT [3]

        The process concept of a shell refers to how the shell manages and interacts with processes on the system. 
        The shell creates a new process to execute a command when a user issues a command to the shell.
        The shell can then manage and control the processes it creates, including starting, stopping, and monitoring their execution.

THE DIFFERENCES BETWEEN BACKGROUND AND FOREGROUND EXECUTION [4]

        Background execution refers to a process that is not visible to the user, performing tasks that do not require immediate attention, and has lower priority for resource allocation and CPU time.
        Foreground execution refers to a process that is visible to the user, actively running, and has a higher priority for resource allocation and CPU time.

        In this shell, background execution an ampersand (&) at the end of the command line will make the command run in the background.


References:
[1] A. Robbins, "Bash Pocket Reference," O'Reilly Media, 2016. [Online]. Available: https://books.google.ie/books?hl=en&lr=&id=dzBCH3x6fYEC&oi=fnd&pg=PT7&dq=bash&ots=iXm-scjsFW&sig=vdaiZZqTVGr7ZhBonItTBEzXkuM&redir_esc=y#v=onepage&q=environment%20variables&f=false
[2] Y. Liu, Y. Yue, L. Guo, UNIX I/O System, I/O Redirection and Piping. Springer, Berlin, Heidelberg, 2011, doi: 10.1007/978-3-642-20432-6_7.
[3] A. Silberschatz, P. B. Galvin, and G. Gagne, Operating System Concepts, 10th ed. Hoboken, NJ, USA: John Wiley & Sons, Inc., 2018.
[4] E. Walia, OPERATING SYSTEM CONCEPTS, 2nd ed. New Delhi: Kanna Book Publishing Co., 2019. [Online]. Available: https://books.google.ie/books?id=saoEEAAAQBAJ&printsec=copyright&source=gbs_pub_info_r#v=onepage&q&f=false

Acknowledgement of the DCU Academic Integrity Policy:
I understand that the University regards breaches of academic integrity and plagiarism as grave and serious.
I have read and understood the DCU Academic Integrity and Plagiarism Policy. I accept the penalties that may be imposed should I engage in practice or practices that breach this policy.

I have identified and included the source of all facts, ideas, opinions and viewpoints of others in the assignment references. Direct quotations, paraphrasing, discussion of ideas from books, journal articles, internet sources, module text, or any other source whatsoever are acknowledged and the sources cited are identified in the assignment references.

I declare that this material, which I now submit for assessment, is entirely my own work and has not been taken from the work of others save and to the extent that such work has been cited and acknowledged within the text of my work.