#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  
  if (argc == 1) {
    printf("my-grep: searchterm [file ...]\n");
    exit (1);
  } else if (argc == 2) {
    /*When given empty string as search string, printed nothing and exit with 0*/
    if (argv[1][0] == '\0') {
      exit (0);
    }
    
    char *buffer;
    size_t size = 0;
    /*reading frotm stdin*/
    if (getline(&buffer, &size, stdin) != 1) {
      if (strstr(buffer, argv[1]) != NULL) {
          printf("%s", buffer);
        }
    }
    
    return 0;
  } else {
  
    if (argv[1][0] == '\0') {
      exit (0);
    }
    
    int x = 2;
    
    while (x < argc) {
  
      char *buffer;
      size_t size = 0;
      ssize_t read;
    
      FILE *fp = fopen(argv[x], "r");
      /*error if file open fails*/
      if (fp == NULL) {
        printf("my-grep: cannot open file\n");
        exit (1);
      }
      /*comparing if search word if found and printing lines when match found*/
      while ((read = getline(&buffer, &size, fp)) != -1) {
        if (strstr(buffer, argv[1]) != NULL) {
          printf("%s", buffer);
        }
      }
      
      free(buffer);
      fclose(fp);
      x = x + 1;
    
    }
    return 0;
  }

}
