#include "shell.h"

int main(int argc, char const *argv[]) {
  char * args=calloc(sizeof(char),1000);
  fgets(args, 1000, stdin);
  printf("%s\n",args);
  while(strcmp(args,"exit\n")!=0){
    char ** command=parse(args);
    printf("%d\n",lengthArgs(command));
    if(lengthArgs(command)>0){
      printf("sad\n");
      int i=0;
      for (i = 0; i < lengthArgs(command); i++) {
        printf("%d, %s \n",i,command[i]);
      }
      executing(command);
    }
    fgets(args, 1000, stdin);
  }
  return 0;
}
