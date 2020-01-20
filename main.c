
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include "functions/loop.h"

/*
  Function Declarations for builtin shell commands:
 */
int lush_cd(char **args);
int lush_help(char **args);
int lush_exit(char **args);
int lush_ls(char **args);
int lush_history(char **args);
int lush_mkdir(char **args);
int lush_rmdir(char **args);
int lush_touch(char **args);

int main(){
  lsh_loop();
  return 1;
}
