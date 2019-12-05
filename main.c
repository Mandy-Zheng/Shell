#include "shell.h"

int main(int argc, char const *argv[]) {
  char args[1000];
  fgets(args, 1000, stdin);
  while(strcmp(args,"exit\n")!=0){
    if(lengthArgs(args)>0){
      parse(args);
    }
  }
  return 0;
}
