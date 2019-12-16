#include "shell.h"

/*======== void executing(char ** command, int * keepRunning) ==========
Inputs:  char ** command, int * keepRunning
Returns: N/A
Executes command given by command and prints command not found if invalid command
If command is to exit, turn keeprunning to 0 (false)
====================*/
void executing(char ** command, int * keepRunning){
  if(strcmp(command[0],"exit") == 0){
    * keepRunning = 0;
  }
  else if (!isChangeDirectory(command)){
    if(fork()==0){
      if(execvp(command[0],command) == -1){
        printf("%s: command not found\n",command[0]);
        exit(0);
      }
    }else{
      wait(NULL);
    }
  }
}

/*======== int isChangeDirectory(char ** command) ==========
Inputs:  char ** command
Returns: 1 if the command is cd, 0 otherwise
Checks if the first element of the command list is "cd"
====================*/
int isChangeDirectory(char ** command){
    if(!strcmp(command[0],"cd")){
      changeDirectory(command);
      return 1;
    }
    return 0;
}

/*======== void changeDirectory(char ** command) ==========
Inputs:  char ** command
Returns: N/A
Uses chdir to change change directory
Uses lengthArgs(command) and chdir's return value to return appropriate error messages
====================*/
void changeDirectory(char ** command){
  if (lengthArgs(command) > 2){
    printf("cd: too many arguments");
  }
  else if (chdir(command[1]) != 0){
    printf("cd: %s: No such file or directory\n",command[1]);
  }
}
/*======== void set_color(unsigned char color) ==========
Inputs:  char * args, char * sign
Returns: N/A
changes color of text to the one dictated by unsigned char color
====================*/
void set_color(unsigned char color) {
  printf("\033[0;38;5;%hhum", color);
}
