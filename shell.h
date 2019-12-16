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
char * strip(char * args, char sign);
char * truncs(char * args, char sign);
char ** parse(char * args);
char ** parseMulti(char * args,char * sign);
void executing(char ** command, int * keepRunning);
int isChangeDirectory(char ** command);
void changeDirectory(char ** command);
void set_color(unsigned char color);
int isPipe(char * command);
void performPipe(char * command1, char * command2);
void simpleRedirect(char * args,char sign);
int isRedirect(char * args);
void complexRedirect(char * args,char sign);
void transitiveRedirect(char * args, char firstsign);
