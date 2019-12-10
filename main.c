#include "shell.h"

int main(int argc, char const *argv[]) {
  char * args=calloc(sizeof(char),1000);
  char dir_path[512];
  while(strcmp(args,"exit")!=0){

    printf("/Shell$ " );
    enum color c=DarkRed; 
    fgets(args, 1000, stdin); 
    args[strlen(args)-1]='\0';
    char ** commandmulti=parseMulti(args); 
     // set_color(c);
    int x=getchar();
    printf("\n[%d]\n",x);
    if(x==27){
      printf("yes");
      x=getchar();
      printf("\n[%d]\n",x);	
      if(x==91){
        printf("yes2");
	x=getchar();
	printf("\n[%d]\n",x);
        if(x==68){
	  printf("\nyes3");
          printf("\033[D");
       	}
      }
    }

    getcwd(dir_path,sizeof(dir_path));
    printf("%s/Shell$ ",dir_path);
    enum color c=DarkRed;
    fgets(args, 1000, stdin);
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
  return 0;
}
