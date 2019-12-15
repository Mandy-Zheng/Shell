# Shell

### Features

#### Basic Features:

######  -Reads input and multiple commands separated by ;
######  -parses the line to separate the command from its arguments and different commands from each other (based on ;)
######  -executes basic commands of execvp
######  -exiting shell (type in exit)
######  -cd into different directories
######  -simple redirection of > and <
######  -simple pipes (use of one pipe)

#### Additional Features we successfully implemented:

######  -Added Color (USE BLACK BACKGROUND TO SEE THE COLORS) to shell
######  -Can put additional spaces before, after and even in the middle of flagged commands (e.g. "ls   -a")
######  -Error handling (would show command not found)
######  - >> redirection works
######  -Two simple redirection together works :  xxx > yyy < zzz and xxx< yyy >zzz
######  -Pipe and simple redirection combo works (e.g. ls | wc > inputfile)
######  -infinite piping works

#### Additional Features we tried to implement:

#### Persisting Bugs in our program:

#### Headers for all functions:

##### int main(int argc, char const *argv[]);
##### static void sighandler(int signo);
##### int lengthArgs(char **command);
##### char ** parse(char * args);
##### void executing(char ** command, int * keepRunning);
##### char ** parseMulti(char * args,char * sign);
##### void simpleRedirect(char * args,char sign);
##### int isRedirect(char * args);
##### int isChangeDirectory(char ** command);
##### int changeDirectory(char ** command);
##### int isPipe(char ** command);
##### char ** parsePipe(char ** args);
##### int performPipe(char ** command, int index);
##### char * strip(char * args, char sign);
##### void set_color(unsigned char color);
##### void complexRedirect(char * args,char sign);
##### void transitiveRedirect(char * args, char sign);
##### char * truncs(char * args, char sign);
##### void hybridRedirect(char * args, char sign);











