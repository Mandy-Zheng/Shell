#include "shell.h"

/*======== int isRedirect(char * args) ==========
Inputs:  char * args
Returns: 1 if there was sometype of redirection in the command or 0 if there was none
Depending on what signs are in args (e.g. >, <, >>...), it calls on the appropriate function to execute the correct redirection
====================*/
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

/*======== void simpleRedirect(char * args,char sign) ==========
Inputs:  char * args, char * sign
Returns: N/A
Create a file to write, truncate, and create and write to stdout if sign is > and then execute the command in args
Create a file to read into stdin if the sign is < and execute the command in args
====================*/
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

/*======== void transitiveRedirect(char * args, char sign) ==========
Inputs:  char * args, char * sign
Returns: N/A
Create a file to write, truncate, and creat and write to stdout and read from stdin if firstsign is > and then execute the command in args
Create a file to write, truncate, and creat and write to stdout and read from stdin and to determine which one to read from and which one to read to depends on firstsign and then execute the command in args
====================*/
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

/*======== void complexRedirect(char * args,char sign) ==========
Inputs:  char * args, char * sign
Returns: N/A
Create a file to write, append, and create and write to stdout if sign is > and then execute the command in args
====================*/
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

/*======== void saveRedirect(int* redirects) ==========
Inputs: int* redirects
Returns: N/A
Saves STDIN_FILENO,STDOUT_FILENO,STDERR_FILENO to restore file stream later
====================*/
void saveRedirect(int* redirects) {
  redirects[0] = dup(STDIN_FILENO);
  redirects[1] = dup(STDOUT_FILENO);
  redirects[2] = dup(STDERR_FILENO);
}

/*======== void restoreRedirect(int* redirects) ==========
Inputs: int* redirects
Returns: N/A
restore STDIN_FILENO,STDOUT_FILENO,STDERR_FILENO file stream
====================*/
void restoreRedirect(int* redirects) {
  dup2(redirects[0], STDIN_FILENO);
  dup2(redirects[1], STDOUT_FILENO);
  dup2(redirects[2], STDERR_FILENO);
  close(redirects[0]);
  close(redirects[1]);
  close(redirects[2]);
}
