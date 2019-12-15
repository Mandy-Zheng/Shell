#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <dirent.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
enum color {Black, DarkRed, DarkGreen, DarkYellow, DarkBlue, Purple, DarkCyan, LightGrey, DarkGrey, Red, Green, Yellow, Blue, Pink, Cyan, White};
int lengthArgs(char **command);
char ** parse(char * args);
void executing(char ** command, int * keepRunning);
char ** parseMulti(char * args,char * sign);
void simpleRedirect(char * args,char sign);
int isRedirect(char * args);
int isChangeDirectory(char ** command);
int changeDirectory(char ** command);
int isPipe(char ** command);
int performPipe(char * command1, char * command2);
char * strip(char * args, char sign);
void set_color(unsigned char color);
void complexRedirect(char * args,char sign);
void transitiveRedirect(char * args, char sign);
char * truncs(char * args, char sign);
void hybridRedirect(char * args, char sign);
int performPipeRecursive(char ** command, int lengthArgs);
