#include "shell.h"

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

int isChangeDirectory(char ** command){
    if(!strcmp(command[0],"cd")){
      changeDirectory(command);
      return 1;
    }
    return 0;
}

void changeDirectory(char ** command){
  if (lengthArgs(command) > 2){
    printf("cd: too many arguments");
  }
  else if (chdir(command[1]) != 0){
    printf("cd: %s: No such file or directory\n",command[1]);
  }
}

void set_color(unsigned char color) {
  printf("\033[0;38;5;%hhum", color);
}
void saveRedirect(int* redirects) {
  redirects[0] = dup(STDIN_FILENO);
  redirects[1] = dup(STDOUT_FILENO);
  redirects[2] = dup(STDERR_FILENO);
}

void restoreRedirect(int* redirects) {
  dup2(redirects[0], STDIN_FILENO);
  dup2(redirects[1], STDOUT_FILENO);
  dup2(redirects[2], STDERR_FILENO);
  close(redirects[0]);
  close(redirects[1]);
  close(redirects[2]);
}
