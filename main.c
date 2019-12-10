#include "shell.h"

int main(int argc, char const *argv[]) {
  char * args=calloc(sizeof(char),1000);
  char dir_path[256];
  while(strcmp(args,"exit")!=0){
    currentDirectory(dir_path);
    printf("/Shell$ " );
    enum color c=DarkRed;
    fgets(args, 1000, stdin);
    args[strlen(args)-1]='\0';
    char ** commandmulti=parseMulti(args);
    if(lengthArgs(commandmulti)>0){
      set_color(c);
      for (size_t i = 0; i < lengthArgs(commandmulti); i++) {
        char ** command = parse(commandmulti[i]);
        if(!isRedirect(commandmulti[i]) &&
           !isChangeDirectory(command)){
             executing(command);
	      }
      }
    }
  }
  return 0;
}
