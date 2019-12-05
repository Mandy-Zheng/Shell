#include "shell.h"
int lengthArgs(char * args[]){
  char ** command=calloc(sizeof(char *)*100);
  command=strsep(args," ");
  int i=0;
  int length=0;
  while(command[i]!="\0"){
    length++;
  }
  return length;
}
void parse(char * args[]){
  char ** command=calloc(sizeof(char *)*100);
  command=strsep(args," ");
  if(fork()==0){
    execvp(command[0],command);
  }else{
    wait(NULL);
  }
}
