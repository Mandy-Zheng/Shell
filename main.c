#include "shell.h"
static int  keepRunning;
static void sighandler(int signo){
  char  c; int go = 1;
  printf("OUCH, did you hit Ctrl-C?\n"
         "Do you really want to quit? [y/n] ");
  c = getchar();
  do {
    printf("%s\n",c);
    if (c == 'n' || c == 'N'){
      go = 0;
    } else if((c == 'y' || c == 'Y')){
      printf("WUTHTE");
      keepRunning = 0;
      go = 0;
    }
    c = getchar();
  } while (go);
}
int main(int argc, char const *argv[]) {
  keepRunning = 1;
  char * args=calloc(sizeof(char),1000);
  char dir_path[512];
  signal(SIGINT,sighandler);
  while(keepRunning){
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
          char ** command = parse(commandmulti[i]);
          if(!isRedirect(commandmulti[i]) &&
             !isPipe(command)){
               executing(command);
          }
        }
      }
    }
  }
  return 0;
}
