#ifndef HELPER_H
#define HELPER_H

#include <string.h>
#include <stdio.h>
#include <stdbool.h>

char* replaceSubString(char* string, char* oldSub, char* newSub){

  static char buffer[4096];
  char *p;

  if(!(p = strstr(string, oldSub)))  
    return string;

  strncpy(buffer, string, p-string); 
  buffer[p-string] = '\0';

  sprintf(buffer+(p-string), "%s%s", newSub, p+strlen(oldSub));

  return buffer;

}

bool checkIfGit(char* cwd){
  DIR *d;
  struct dirent *dir;
  d = opendir(cwd);
  while ((dir = readdir(d)) != NULL) {
      if(strcmp(dir->d_name,".git") == 0){
        return true;
      }
  }
  return false;
}

#endif