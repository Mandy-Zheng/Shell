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
  char * part=calloc(sizeof(char),1000);
  strcpy(part,args);
  for (size_t i = 0; part!=NULL; i++) {
    command[i]= strsep(&part," ");
    if (strlen(command[i])==0){
      command[i]=NULL;
    }else{
      command[i]=truncs(strip(command[i],' '), ' ');
    }
  }
  return command;
}

char ** parseMulti(char * args, char * sign){
  char ** multicommand=calloc(sizeof(char*),100);
  char * onecommand=calloc(sizeof(char),1000);
  strcpy(onecommand,args);
  for (size_t i = 0; onecommand != NULL; i++) {
    multicommand[i]=strsep(&onecommand,sign);
    multicommand[i]= truncs(strip(multicommand[i],' '),' ');
    if(strlen(multicommand[i])==0){
      i--;
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
  char ** command = parseMulti(args,&sign);
  if(fork()==0){
    if(sign=='>'){
      command[1]=truncs(strip(command[1],' '),' ');
      int into = open(command[1],O_WRONLY |O_TRUNC| O_CREAT, 0644);
      dup2(into, STDOUT_FILENO);
      char ** command2 = parse(command[0]);
      execvp(command2[0],command2);
    }else{
      int into = open(command[1],O_RDONLY | O_CREAT, 0644);
      dup2(into,STDIN_FILENO);
      char ** command2 = parse(strip(command[0],' '));
      execvp(command2[0],command2);
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
      int into = open(commandsecond[0],O_WRONLY | O_CREAT, 0644);
      int from = open(commandsecond[1],O_RDONLY,0644);
      dup2(into, STDOUT_FILENO);
      dup2(from, STDIN_FILENO);
      char ** command2 = parse(commandfirst[0]);
      execvp(command2[0],command2);
    }else{
      char ** commandsecond=parseMulti(commandfirst[1], ">");
      int into = open(strip(commandsecond[1],' '),O_WRONLY | O_CREAT, 0644);
      int from = open(strip(commandsecond[0],' '),O_RDONLY,0644);
      dup2(into, STDOUT_FILENO);
      dup2(from, STDIN_FILENO);
      char ** command2 = parse(commandfirst[0]);
      execvp(command2[0],command2);
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
      dup2(into, STDOUT_FILENO);
      char ** command2 = parse(command[0]);
      execvp(command2[0],command2);
    }else{
      wait(NULL);
    }
  }
}

void hybridRedirect(char * args, char sign){
  char ** command = parseMulti(args, "|");
  char ** command2=parseMulti(command[1], ">");
  command2[0]=truncs(strip(command2[0],' '),' ');
  command2[1]=truncs(strip(command2[1],' '),' ');
  char * pipeCommand[3];
  pipeCommand[0] = command[0];
  pipeCommand[1] = "|";
  pipeCommand[2] = command2[0];
  if(fork()==0){
    int into = open(command2[1],O_WRONLY | O_CREAT, 0644);
    dup2(into,STDOUT_FILENO);
    performPipe(pipeCommand,0);
  }
}

char * strip(char * args, char sign){
  int start=-1;
  for(size_t i = 0; i < strlen(args);i++){
    if(start==-1 && args[i]!=sign){
      start=0;
    }
    if(start!=-1){
      args[start]=args[i];
      start++;
      if(i==strlen(args)-1){
        args[start]='\0';
        return args;
      }
    }
  }
  return args;
}

char * truncs(char * args, char sign){
  int length=strlen(args)-1;
  for(size_t i = length; i >= 0;i--){
    if(args[i]==sign){
      args[i]='\0';
    }else{
      return args;
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

//how many max?
int isRedirect(char * args){
  int count=0;
  int pipe=isPipe(parse(args));
  char firstSign='\0';
  for (size_t i = 1; i < strlen(args)-1; i++) {
    if(args[i]=='>' && pipe){
      hybridRedirect(args, args[i]);
    }
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
int isPipe(char ** command){
  char * parsePreparation = calloc(sizeof(char *),100);
  char ** parsedCommand;
  int run = 0;
  printf("%d\n",lengthArgs(command));
  for (size_t i = 0; i < lengthArgs(command); i++) {
    strcat(parsePreparation,command[i]);
    if(!strcmp(command[i],"|")){
        run = 1;
    }
  }
  if (run){
    printf("YOO\n");
    printf("%s\n",parsePreparation);
    parsedCommand = parseMulti(parsePreparation, "|");
    free(parsePreparation);
    performPipeRecursive(parsedCommand,0);
    return 1;
  }
  return 0;
}
// char ** parsePipe(char ** args){
//   char ** command=calloc(sizeof(char *),100);
//   for (size_t i = 0, index = 0; args[i] != NULL; i++) {
//     if (strcmp(args[i],"|") != 0){
//       command[index] = args[i];
//       index++;
//     }
//   }
//   return command;
// }
int performPipeRecursive(char ** command, int lengthArgs){
  if (lengthArgs < 2){
    return 0;
  } else{
    performPipe(command[lengthArgs(command)-lengthArgs],command[lengthArgs(command)-lengthArgs]+1);
    performPipeRecursive(command,lengthArgs-1);
  }
}
int performPipe(char * command1, char * command2, int index){
    FILE * read;
    FILE * write;
    char transfer[1028][1028];

    read= popen(command1,"r");
    // if( p == NULL)
    // {
    //     printf("%s\n", );("Unable to open process");
    //     return 1;
    // }
    int stop = 0;
    int length = 0;
    for (size_t i = 0; !stop; i++) {
      if (fgets(transfer[i],sizeof(transfer[i]),read) == NULL){
        stop = 1;
      } else {
        //printf("%s\n",transfer[i]);
        length = i+1;
      }
    }
    pclose(read);
    write = popen(command2,"w");
    for (size_t i = 0; i < length; i++) {
      fprintf(write, "%s", transfer[i]);
    }
    pclose(write);
    return 1;
  }
void set_color(unsigned char color) {
  printf("\033[0;38;5;%hhum", color);
}
