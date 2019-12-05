#include "shell.h"

int main(int argc, char const *argv[]) {
  char * args=calloc(sizeof(char),1000);
  args="dummy";
  while(strcmp(args,"exit")!=0){
    printf("%s\n","/Shell$" );
    fgets(args, 1000, stdin);
    args[strlen(args)-1]='\0';
    char ** command=parse(args);
    if(lengthArgs(command)>0){
      int i=0;
      executing(command);
    }
  }
  return 0;
}
