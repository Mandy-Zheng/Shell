#include "shell.h"

int isPipe(char * command){
  char ** parsedCommand;
  int run = 0;
  for (size_t i = 0; i < strlen(command) ; i++) {
    if(command[i] == '|'){
      parsedCommand = parseMulti(command, "|");
      char pipeFirst[1000];
      strcpy(pipeFirst,parsedCommand[0]);
      for (size_t j = 1; j < lengthArgs(parsedCommand)-1; j++) {
        strcat(pipeFirst," | ");
        strcat(pipeFirst,parsedCommand[j]);
      }
      performPipe(pipeFirst,parsedCommand[lengthArgs(parsedCommand)-1]);
      return 1;
    }
  }
  return 0;
}

void performPipe(char * command1, char * command2){
    FILE * read;
    FILE * write;
    char transfer[1028][1028];
    int stop = 0;
    int length = 0;
    read= popen(command1,"r");
    write = popen(command2,"w");

    for (size_t i = 0; !stop; i++) {
      if (fgets(transfer[i],sizeof(transfer[i]),read) == NULL){
        stop = 1;
      } else {
        length = i+1;
      }
    }
    pclose(read);


    for (size_t i = 0; i < length; i++) {
      fprintf(write, "%s", transfer[i]);
    }
    pclose(write);

  }
