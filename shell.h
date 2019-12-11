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
void executing(char ** command);
char ** parseMulti(char * args);
void simpleRedirect(char * args,char sign);
char ** redirect_parse(char * args, char* sign);
int isRedirect(char * args);
int isChangeDirectory(char ** command);
int changeDirectory(char ** command);
int isPipe(char ** command);
int performPipe(char ** command, int index);
char * strip(char * args, char sign);
void set_color(unsigned char color);
void complexRedirect(char * args,char sign);
