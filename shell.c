#include "shell.h"
int lengthArgs(char **command){
  int i=0;
  int length=0;
  while(strcmp(command[i],"\0")!=0){
    length++;
  }
  return length;
}
char ** parse(char * args){
  char ** command=calloc(sizeof(char *),100);
  int i=0;
  char * part;
  while ((part=strsep(&args," "))!=NULL){
    command[i]=part;
    i++;
  }
  command[i]="\0";
  return command;
}
void executing(char ** command){
  if(fork()==0){
    execvp(command[0],command);
  }else{
    wait(NULL);
  }
}
