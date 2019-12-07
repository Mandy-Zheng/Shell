#include "shell.h"
int lengthArgs(char **command){
  int i=0;
  int length=0;
  while(command[i]!=NULL){
    length++;
    i++;
  }
  return length;
}
char ** parse(char * args){
  char ** command=calloc(sizeof(char *),100);
  char * part=args;
  for (size_t i = 0; part!=NULL; i++) {
    command[i]= strsep(&part," ");
  }
  return command;
}
char ** parseMulti(char * args){
  char ** multicommand=calloc(sizeof(char*),100);
  char * onecommand=args;
  for (size_t i = 0; onecommand != NULL; i++) {
    multicommand[i]= strsep(&onecommand,";");
    if(multicommand[i][0]==' '){
      multicommand[i]= strsep(&multicommand[i]," ");
      printf(multicommand[i]);
    }
  }
  return multicommand;
}
void executing(char ** command){
  if(fork()==0){
    execvp(command[0],command);
  }else{
    wait(NULL);
  }
  printf("\n");
}
