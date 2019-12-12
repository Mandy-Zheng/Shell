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
void executing(char ** command, int * keepRunning){
  if(strcmp(command[0],"exit") == 0){
    * keepRunning = 0;
  }
  else if (!isChangeDirectory(command)){
    if(fork()==0){
      if(execvp(command[0],command) == -1){
        printf("%s: command not found\n",command[0]);
        exit(0);
      }
    }else{
      wait(NULL);
    }
  }
}
void simpleRedirect(char * args,char sign){
  char ** command = redirect_parse(args,&sign);
  if(sign=='>'){
    if(fork()==0){
      int into = open(truncs(strip(command[1],' '),' '),O_WRONLY | O_CREAT, 0644);
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
      char ** command2 = parse(strip(command[0],' '));
      execvp(command2[0],command2);
    }else{
      wait(NULL);
    }
  }
}

void transitiveRedirect(char * args, char firstsign){
  char ** commandfirst = redirect_parse(args,&firstsign);
  if(firstsign=='>'){
    if(fork()==0){
      char ** commandsecond=parse(commandfirst[1], "<");
      commandsecond[0]=truncs(strip(commandsecond[0],' '),' ')
      commandsecond[1]=truncs(strip(commandsecond[1],' '),' ')
      int into = open(commandsecond[0],O_WRONLY | O_CREAT, 0644);
      int from = open(commandsecond[1],O_RDONLY,0644);
      dup2(into, STDOUT_FILENO);
      dup2(from, STDIN_FILENO);
      char ** command2 = parse(commandfirst[0]);
      execvp(command2[0],command2);
    }else{
      wait(NULL);
    }
  }else{
    if(fork()==0){
      char ** commandsecond=redirect_parse(commandfirst[1], ">");
      int into = open(strip(commandsecond[1],' '),O_WRONLY | O_CREAT, 0644);
      int from = open(strip(commandsecond[0],' '),O_RDONLY,0644);
      dup2(into, STDOUT_FILENO);
      dup2(from, STDIN_FILENO);
      char ** command2 = parse(commandfirst[0]);
      execvp(command2[0],command2);
    }else{
      wait(NULL);
    }
  }
}

void complexRedirect(char * args,char sign){
  char ** command = redirect_parse(args,">>");
  if(sign=='>'){
    if(fork()==0){
      int into = open(command[1],O_WRONLY | O_APPEND | O_CREAT, 0644);
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

char ** redirect_parse(char * args, char * sign){
  char ** multicommand=calloc(sizeof(char*),100);
  char * onecommand=args;
  for (size_t i = 0; onecommand != NULL; i++) {
    multicommand[i]=strsep(&onecommand,sign);
    if(multicommand[i][0]==' '){
      int len=strlen(multicommand[i]);
      for (size_t j=0;j<len-1;j++){
      	multicommand[i][j]= multicommand[i][j+1];
      }
      multicommand[i][len-1]='\0';
    }
    if(strlen(multicommand[i])==0){
      i--;
    }
  }
  return multicommand;
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

char * truncs(char * args, char sign){
  int start=-1;
  int length=strlen(args);
  for(size_t i = 0; i < length;i++){
    if(args[i]==sign){
      args[i]='\0';
    }else{
      i=-2;
    }
  }
  return args;
}



int isChangeDirectory(char ** command){
    if(!strcmp(command[0],"cd")){
      changeDirectory(command);
      return 1;
    }
    return 0;
}

int changeDirectory(char ** command){
  if (lengthArgs(command) > 2){
    printf("cd: too many arguments");
    return 1;
  }
  else if (chdir(command[1]) != 0){
    printf("cd: %s: No such file or directory\n",command[1]);
    return 1;
  }
  else{
    return 1;
  }
  return 0;
}

int isPipe(char ** command){
  for (size_t i = 0; i < lengthArgs(command); i++) {
    if(!strcmp(command[0],"|")){
      //performPipe(command, 0);
      return 1;
    }
  }
  return 0;
}
// void performPipe(char ** command, int index){
// }
//how many max?
int isRedirect(char * args){
  int count=0;
  char firstSign='\0';
  for (size_t i = 1; i < strlen(args)-1; i++) {
    if(args[i]=='>' && args[i+1]=='>'|| args[i]=='<' && args[i+1]=='>'){
      complexRedirect(args,args[i]);
      return 1;
    }
    if(args[i]=='>' || args[i]=='<'){
      if(firstSign!='<'&&firstSign!='>'){
        firstSign=args[i];
      }
      count++;
    }
 }
 if(firstSign=='<' ||firstSign=='>'){
   if(count>1){
     transitiveRedirect(args,firstSign);
     return 1;
   }
   simpleRedirect(args,firstSign);
   return 1;
 }

  return 0;
}
void set_color(unsigned char color) {
  printf("\033[0;38;5;%hhum", color);
}
