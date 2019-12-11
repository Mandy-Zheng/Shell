#include "shell.h"
static void sighandler(int signo){
  char dir_path[512];
  set_color(14);
  getcwd(dir_path,sizeof(dir_path));
  printf("\n%s",dir_path);
  printf("\n$ ");
  set_color(15);
  fflush(stdout);
}
int main(int argc, char const *argv[]) {
  char * args=calloc(sizeof(char),1000);
  char dir_path[512];
  signal(SIGINT,sighandler);
  while(args!="exit\n"){
    set_color(Cyan);
    getcwd(dir_path,sizeof(dir_path));
    printf("%s\n$ ",dir_path);
    set_color(White);
    fgets(args, 1000, stdin);
    if(args[0] !='\n'){
      args[strlen(args)-1]='\0';
      char ** commandmulti=parseMulti(args);
      if(lengthArgs(commandmulti)>0){

        for (size_t i =0 ; i< lengthArgs(commandmulti);i++){
          strip(commandmulti[i],' ');
          if(strlen(commandmulti[i])>0){
            char ** command = parse(commandmulti[i]);
            if(!isRedirect(commandmulti[i]) &&
             !isPipe(command)){
               executing(command);
             }
          }
        }
      }
    }
  }
  return 0;
}
