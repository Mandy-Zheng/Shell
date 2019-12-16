#include "shell.h"

int isRedirect(char * args){
  int count=0;
  int pipe = 0;
  for (size_t i = 0; i < strlen(args); i++) {
    if(args[i] == '|'){
      pipe = 1;
    }
  }
  char firstSign='\0';
  for (size_t i = 1; i < strlen(args)-1; i++) {
    if(args[i]=='>' && args[i+1]=='>'){
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

void simpleRedirect(char * args,char sign){
  char ** command = parseMulti(args,&sign);
  if(fork()==0){
    if(sign=='>'){
      command[1]=truncs(strip(command[1],' '),' ');
      int into = open(command[1],O_WRONLY |O_TRUNC| O_CREAT, 0644);
      if (into<0 ){
        printf("eee%s\n",strerror(into));
      }else{
        dup2(into, STDOUT_FILENO);
        char ** command2 = parse(command[0]);
        execvp(command2[0],command2);
      }
    }else{
      int into = open(command[1],O_RDONLY | O_CREAT, 0644);
      if (into<0) {
        printf("fff%s\n",strerror(into));
      }else{
        dup2(into,STDIN_FILENO);
        char ** command2 = parse(strip(command[0],' '));
        execvp(command2[0],command2);
      }
    }
  }else{
    wait(NULL);
  }
}

void transitiveRedirect(char * args, char firstsign){
  char ** commandfirst = parseMulti(args,&firstsign);
  if(fork()==0){
    if(firstsign=='>'){
      char ** commandsecond=parseMulti(commandfirst[1], "<");
      commandsecond[0]=truncs(strip(commandsecond[0],' '),' ');
      commandsecond[1]=truncs(strip(commandsecond[1],' '),' ');
      int into = open(commandsecond[0],O_WRONLY | O_TRUNC | O_CREAT, 0644);
      int from = open(commandsecond[1],O_RDONLY,0644);
      if (into<0){
        printf("ggg%s\n",strerror(into));
      }else if(from <0){
        printf("hhh%s\n",strerror(from));
      }
      else{
        dup2(into, STDOUT_FILENO);
        dup2(from, STDIN_FILENO);
        char ** command2 = parse(commandfirst[0]);
        execvp(command2[0],command2);
      }
    }else{
      char ** commandsecond=parseMulti(commandfirst[1], ">");
      int into = open(strip(commandsecond[1],' '),O_WRONLY | O_TRUNC | O_CREAT, 0644);
      int from = open(strip(commandsecond[0],' '),O_RDONLY,0644);
      if (into<0){
        printf("aaa%s\n",strerror(from));
      }else if(from <0){
        printf("bbb%s\n",strerror(from));
      }else{
        dup2(into, STDOUT_FILENO);
        dup2(from, STDIN_FILENO);
        char ** command2 = parse(commandfirst[0]);
        execvp(command2[0],command2);
      }
    }
  }else{
    wait(NULL);
  }
}


void complexRedirect(char * args,char sign){
  char ** command = parseMulti(args,">>");
  if(sign=='>'){
    if(fork()==0){
      int into = open(command[1],O_WRONLY | O_APPEND | O_CREAT, 0644);
      if (into<0){
        printf("ccc%s\n",strerror(into));
      }else{
        dup2(into, STDOUT_FILENO);
        char ** command2 = parse(command[0]);
        execvp(command2[0],command2);
      }
    }else{
      wait(NULL);
    }
  }
}
