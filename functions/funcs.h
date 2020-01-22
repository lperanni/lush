#ifndef FUNCS_H
#define FUNCS_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h> 
#include <string.h>
#include <limits.h>
#include <pwd.h>
#include "lib/helper.h"


int lush_cd(char **args);
int lush_help(char **args);
int lush_exit(char **args);
int lush_ls(char **args);
int lush_clear(char **args);
int lush_history(char **args);
int lush_clhist(char **args);
int lush_pwd();
int lush_mkdir(char **args);
int lush_rmdir(char **args);
int lush_rm(char **args);
int lush_touch(char **args);
int lush_cat(char **args);


char *builtin_str[] = {
  "cd",
  "help",
  "exit",
  "ls",
  "clear",
  "history",
  "clhist",
  "pwd",
  "mkdir",
  "touch",
  "rm",
  "rmdir",
  "cat",
};

int (*builtin_func[]) (char **) = {
  &lush_cd,
  &lush_help,
  &lush_exit,
  &lush_ls,
  &lush_clear,
  &lush_history,
  &lush_clhist,
  &lush_pwd,
  &lush_mkdir,
  &lush_touch,
  &lush_rm,
  &lush_rmdir,
  &lush_cat
};

int lsh_num_builtins() {
  return sizeof(builtin_str) / sizeof(char *);
}

int lush_rm(char **args){
  int result = remove(args[1]);
  if(result != -1){
    return 1;
  }
  printf("Couldn't delete file");
  return 1;
}

int lush_rmdir(char **args){
  int result = 0;
  if(args[1]){
    result = rmdir(args[1]);
    if(result == -1){
      printf("Directory is not empty man");
    }
  }else{
    printf("Cant delete");  
  }
  return 1;
}

int lush_touch(char **args){
  FILE* newFile;
  newFile = fopen(args[1], "w");
  fclose(newFile);
  return 1;
}

int lush_mkdir(char **args){
  int result = 0;
  if(args[1]){
    result = mkdir(args[1], 0777);
  }
  return 1;
}

int lush_clhist(char **args){
  FILE *history;
  char buffer[100];
  int cx;
  const char* s = getenv("HOME");
  cx = snprintf ( buffer, 100, "%s/Documents/history.txt", s);
  history = fopen(buffer, "w");
  fputs("", history);
  fclose(history);
  return 1;
}

int lush_pwd(char **args){
  char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL) 
    {
      printf("%s", cwd);
    } 
    else {
      printf("Error");
    }

    return 1;
  
}

int lush_history(char **args){
  char* status;
  char input[255];
  int counter = 1;
  FILE *history;
  char buffer[100];
  int cx;
  const char* s = getenv("HOME");
  cx = snprintf ( buffer, 100, "%s/Documents/history.txt", s);
  history = fopen(buffer, "r");
  
  do 
  {
    status = fgets(input, 255, history);
    if(status != 0){
      printf("%d. %s", counter, input);
    }
    counter++;
  } while(status);

  fclose(history);
  return 1;

}

int lush_ls(char **args){
  DIR *d;
  struct dirent *dir;
  if(args[1]){
    d = opendir(args[1]);
  }
  else{
    d = opendir(".");
  }
  if (d) {
    while ((dir = readdir(d)) != NULL) {
      if(strcmp(dir->d_name,".") != 0 && strcmp(dir->d_name, "..") != 0 ){
        if(countWords(dir->d_name) == 1){
          printf("\033[22;32m%s\033[0m ", dir->d_name);
        }
        else {
          printf("'\033[22;32m%s\033[0m' ", dir->d_name);
        }
      }
    }
    closedir(d);
  }
  printf("\n");
  return(1);
}

int lush_clear(char **args){
  system("@cls||clear");
  return(1);
}


int lush_cd(char **args)
{
  if (args[1] == NULL) {
    fprintf(stderr, "lush: expected argument to \"cd\"\n");
  }
  else if(strstr(args[1], "~") != NULL){
    char* s = getenv("HOME");
    char* result = replaceSubString(args[1],"~", s);
    if (chdir(result) != 0) {
      perror("lush");
    }
  }
  else {
    if (chdir(args[1]) != 0) {
      perror("lush");
    }
  }
  return 1;
}

int lush_help(char **args)
{
  int i;
  printf("Luciano Peranni's LUSH\n");
  printf("Type program names and arguments, and hit enter.\n");
  printf("The following are built in:\n");

  for (i = 0; i < lsh_num_builtins(); i++) {
    printf("  %s\n", builtin_str[i]);
  }

  printf("Use the man command for information on other programs.\n");
  return 1;
}

int lush_cat(char **args){
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    
    fp = fopen(args[1], "r");
    if (fp == NULL)
        return 1;

    while ((read = getline(&line, &len, fp)) != -1) {
        printf("%s", line);
    }

    fclose(fp);
    if (line)
        free(line);
    return 1;
}

int lush_exit(char **args)
{
  return 0;
}


#endif