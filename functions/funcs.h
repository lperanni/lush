#ifndef FUNCS_H
#define FUNCS_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <dirent.h> 
#include <string.h>


int lush_cd(char **args);
int lush_help(char **args);
int lush_exit(char **args);
int lush_ls(char **args);
int lush_clear(char **args);
int lush_history(char **args);
int lush_mkdir(char **args);
int lush_rmdir(char **args);
int lush_touch(char **args);


char *builtin_str[] = {
  "cd",
  "help",
  "exit",
  "ls",
  "clear",
  "history",
  "mkdir",
  "rmdir",
  "touch"
};

int (*builtin_func[]) (char **) = {
  &lush_cd,
  &lush_help,
  &lush_exit,
  &lush_ls,
  &lush_clear,
  &lush_history
};

int lsh_num_builtins() {
  return sizeof(builtin_str) / sizeof(char *);
}

int lush_history(char **args){
  char* status;
  char input[255];
  int counter = 1;
  FILE *history;
  history = fopen("functions/history.txt", "r");
  
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
  d = opendir(".");
  if (d) {
    while ((dir = readdir(d)) != NULL) {
      if((dir->d_name != ".") && (dir->d_name != "..")){
        printf("\033[22;35m%s\033[0m ", dir->d_name);
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
  } else {
    if (chdir(args[1]) != 0) {
      perror("lush");
    }
  }
  return 1;
}

int lush_help(char **args)
{
  int i;
  printf("Stephen Brennan's LSH\n");
  printf("Type program names and arguments, and hit enter.\n");
  printf("The following are built in:\n");

  for (i = 0; i < lsh_num_builtins(); i++) {
    printf("  %s\n", builtin_str[i]);
  }

  printf("Use the man command for information on other programs.\n");
  return 1;
}

int lush_exit(char **args)
{
  return 0;
}


#endif