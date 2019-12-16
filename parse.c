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

char * strip(char * args, char sign){
  int start=-1;
  for(size_t i = 0; i < strlen(args);i++){
    if(start==-1 && args[i]!=sign){
      start=0;
    }
    if(start!=-1){
      args[start]=args[i];
      start++;
      if(i==strlen(args)-1){
        args[start]='\0';
        return args;
      }
    }
  }
  return args;
}

char * truncs(char * args, char sign){
  int length=strlen(args)-1;
  for(size_t i = length; i >= 0;i--){
    if(args[i]==sign){
      args[i]='\0';
    }else{
      return args;
    }
  }
  return args;
}

char ** parse(char * args){
  char ** command=calloc(sizeof(char *),100);
  char * part=calloc(sizeof(char),1000);
  strcpy(part,args);
  for (size_t i = 0; part!=NULL; i++) {
    command[i]= strsep(&part," ");
    if (strlen(command[i])==0){
      command[i]=NULL;
      i--;
    }else{
      command[i]=truncs(strip(command[i],' '), ' ');
    }
  }
  free(part);
  return command;
}

char ** parseMulti(char * args, char * sign){
  char ** multicommand=calloc(sizeof(char*),100);
  char * onecommand=calloc(sizeof(char),1000);
  strcpy(onecommand,args);
  for (size_t i = 0; onecommand != NULL; i++) {
    multicommand[i]=strsep(&onecommand,sign);
    multicommand[i]= truncs(strip(multicommand[i],' '),' ');
    if(strlen(multicommand[i])==0){
      multicommand[i] = NULL;
      i--;
    }
  }
  free(onecommand);
  return multicommand;
}
