#include "shell.h"

int main(int argc, char const *argv[]) {
  char * args=calloc(sizeof(char),1000);
  while(strcmp(args,"exit")!=0){
    printf("/Shell$ " );
    fgets(args, 1000, stdin);
    args[strlen(args)-1]='\0';
    char ** command=parse(args);
    printf("%d\n",lengthArgs(command));
    if(lengthArgs(command)>0){
      executing(command);
    }
  }
  return 0;
}
