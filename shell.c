#include "shell.h"
int lengthArgs(char **command){
  int i=0;
  int length=0;
  while(strcmp(command[i],"\0")!=0){
    length++;
    i++;
  }
  return length;
}
char ** parse(char * args){
  char ** command=calloc(sizeof(char *),100);
  char * part=strsep(&args, " ");
  command[0]=part;
  int i=1;
  part=strsep(&args, " ");
  while (part!=NULL){
    command[i]=part;
    i++;
    part=strsep(&args," ");
  }
  command[i]="\0";
  return command;
}
void executing(char ** command){
  if(fork()==0){
    execvp(command[0],command);
  }else{
    printf("before\n");
    wait(NULL);
    printf("after\n");
  }
}
