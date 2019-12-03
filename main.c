#include "shell.h"
int main(int argc, char const *argv[]) {
  char args[1000];
  fgets(args, 1000, stdin);
  while(strcmp(args,"exit\n")!=0){
    int i;
    int command_num=0;
    char ** parse;
    char * command;
    for (i = 0; i < sizeof(args); i++) {
      if (strcmp(args[i]," ")==0){
        command_num++;
        strcpy(parse[command_num],command);
      }else{
        strcat(command,args[i]);
      }
    }
    i=0;
    for (i = 0; i < sizeof(parse) -1; i++) {
      if(strcmp(parse[i],"ls")==0){
        ls(parse[i+1]);
      }
      else{
        printf("Under construction\n");
      }
    }
  }
  return 0;
}
