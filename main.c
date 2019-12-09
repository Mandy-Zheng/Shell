#include "shell.h"

int main(int argc, char const *argv[]) {
  char * args=calloc(sizeof(char),1000);
  while(strcmp(args,"exit")!=0){
    printf("/Shell$ " );
    fgets(args, 1000, stdin);
    args[strlen(args)-1]='\0';
    char ** commandmulti=parseMulti(args);
    printf("%s\n",commandmulti[0]);
    if(lengthArgs(commandmulti)>0){
      for (size_t i = 0; i < lengthArgs(commandmulti); i++) {
        if(!isRedirect(commandmulti[i])){
          executing(parse(commandmulti[i]));
	      }
      }
    }
  }
  return 0;
}
