#include "shell.h"
static int keepRunning = 1;
static int inTerminal = 1;
static void sighandler(int signo){
  if (inTerminal){
    char dir_path[512];
    set_color(14);
    getcwd(dir_path,sizeof(dir_path));
    printf("\n%s ",dir_path);
    set_color(13);
    printf("$ ");
    set_color(15);
    fflush(stdout);
  }
}
int main(int argc, char const *argv[]) {
  char * args=calloc(sizeof(char),1000);
  char dir_path[512];
  signal(SIGINT,sighandler);
  while(keepRunning){
    set_color(Cyan);
    getcwd(dir_path,sizeof(dir_path));
    printf("%s ",dir_path);
    set_color(Pink);
    printf("$ ");
    set_color(White);
    fgets(args, 1000, stdin);
    if(args[0] !='\n'){
      args[strlen(args)-1]='\0';
      char ** commandmulti=parseMulti(args, ";");
        if(lengthArgs(commandmulti)>0){
            for (size_t i =0 ; i< lengthArgs(commandmulti) && keepRunning;i++){
              if(strlen(commandmulti[i])>0){
                char ** command = parse(commandmulti[i]);
                inTerminal = 0;
                if(!isRedirect(args)){
                  if(!isPipe(commandmulti[i])){
                    executing(command,&keepRunning);
                  }
                }
              }
              inTerminal = 1;
            }
        }
    }
  }
  return 0;
}
