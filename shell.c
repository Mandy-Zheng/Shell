#include "shell.h"

void ls(char * args){
  DIR * opened;
  char path[1000];
  strcpy(path,args);
  opened=opendir(path);
  int size=0;
  char directories[1000]="";
  char files[1000]="";
  if(opened!=NULL){
      struct dirent * read=readdir(opened);
      while(read != NULL){
        struct stat readfile;
        char newpath[2000]="";
        strcpy(newpath,path);
        strcat(newpath,"/");
        strcat(newpath,read->d_name);
        int items=stat(newpath, &readfile);
        if(items==-1){
          printf("Error: %s\n",strerror(errno));
        }else{
          if((readfile.st_mode & S_IFMT) == S_IFDIR){
            strcat(directories,"\n\t");
            strcat(directories,read->d_name);
          }else{
            strcat(files,"\n\t");
            strcat(files,read->d_name);
          }
        }
        size+=readfile.st_size;
        //printf("\n %s: %d", );
        read=readdir(opened);
      }
}
