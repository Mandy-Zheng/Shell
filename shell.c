#include "shell.h"
int lengthArgs(char **command){
  int i=0;
  int length=0;
  while(command[i]!=NULL){
    length++;
    i++;
  }
  return length;
}
char ** parse(char * args){
  char ** command=calloc(sizeof(char *),100);
  char * part=args;
  for (size_t i = 0; part!=NULL; i++) {
    command[i]= strsep(&part," ");
    if (strlen(command[i])==0){
      command[i]=NULL;
    }else{
      strip(command[i],' ');
    }
  }
  return command;
}
char ** parseMulti(char * args){
  char ** multicommand=calloc(sizeof(char*),100);
  char * onecommand=args;
  for (size_t i = 0; onecommand != NULL; i++) {
    multicommand[i]=strsep(&onecommand,";");
    if(multicommand[i][0]==' '){
      int len=strlen(multicommand[i]);
      for (size_t j=0;j<len-1;j++){
      	multicommand[i][j]= multicommand[i][j+1];
      }
      multicommand[i][len-1]='\0';
    }
  }
  return multicommand;
}
void executing(char ** command){
  if(fork()==0){
    execvp(command[0],command);
  }else{
    wait(NULL);
  }
  printf("\n");
}
void simpleRedirect(char * args,char sign){
  char ** command = redirect_parse(args,sign);
  if(sign=='>'){
    if(fork()==0){
      int into = open(command[1],O_WRONLY | O_CREAT, 0644);
      dup2(into, STDOUT_FILENO);
      char ** command2 = parse(command[0]);
      execvp(command2[0],command2);
    }else{
      wait(NULL);
    }
  }else{
    if(fork()==0){
      int into = open(command[1],O_RDONLY, 0644);
      dup2(into,STDIN_FILENO);
      char ** command2 = parse(command[0]);
      execvp(command2[0],command2);
    }else{
      wait(NULL);
    }
  }
}
char ** redirect_parse(char * args, char sign){
  char ** command=calloc(sizeof(char *),100);
  char * part=args;
  for (size_t i = 0; part!=NULL; i++) {
    command[i]= strsep(&part,&sign);
    if (strlen(command[i])==0){
      command[i]=NULL;
     }
    if(i!=0){
       strip(command[i],' ');
     }
   }
  return command;
}
char * strip(char * args, char sign){
  int start=-1;
  for(size_t i = 0; i < strlen(args);i++){
    if(args[i]==sign){
      start=i;
    }
    if(i>start && start!=-1){
      args[i-1]=args[i];
      if(i==strlen(args)-1){
        args[i]='\0';
      }
    }
  }
  return args;
}
//how many max?
int isRedirect(char * args){
  for (size_t i = 1; i < strlen(args)-1; i++) {
    if(args[i]=='>' || args[i]=='<'){
      simpleRedirect(args,args[i]);
      return 1;
    }
    /*int gr=0;
    int ls=0;
    int grgr=0;
    int lsls=0;
    int and=0;
    int gr2=0;
    int grgr2=0;
    if(args[i]=='>' && args[i+1]=='>' && args[i-1]=='2'){
      grgr2++;
    }else if(args[i]=='>' && args[i-1]=='2'){
      gr2++;
    }else if(args[i]=='>' && args[i+1]=='>'){
      grgr++;
    }else if(args[i]=='<' && args[i+1]=='<'){
      lsls++;
    }else if(args[i]=='>' && args[i+1]=='>'){
      grgr++;
    }else if(args[i]=='&' && args[i+1]=='>'){
      and++;
    }else if(args[i]=='>'){
      gr++;
    }else if(args[i]=='<'){
      ls++;
    }
  }
  if(gr+grgr+gr2+grgr2+ls+lsls+and==0){
    return 0;
  }else{
    if(gr+grgr+gr2+grgr2+ls+lsls+and==1){
      if(gr>0){
        simpleRedirect()
      }
      if(gr2>0){
        errRedirect()
      }
      if(grgr>0){
        complexRedirect()
      }
      if(grgr2>0){
        errRedirect()
      }
      if(ls>0){
        simpleRedirect()
      }
      if(lsls>0){
        complexRedirect()
      }
      if(and>0){
        specialRedirect()
      }

    }else{
*/
 }
  return 0;
}
