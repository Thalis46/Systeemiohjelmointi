#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 50

int main(int argc, char *argv[]) {
  /*Exit with return code 0 when no files*/
  if (argc == 1) {
    return 0;
  } else {
  
    int x = 1;
    /*looping through all files one at the time*/
    while (x < argc) {
  
      char buffer[BUFSIZE];
    
      FILE *fp = fopen(argv[x], "r");
      /*Error and exit if not able open the file*/
      if (fp == NULL) {
        perror("my-cat: cannot open file\n");
        exit (1);
      }
      /*looping through all lines in file*/
      while (fgets(buffer, BUFSIZE, fp) != NULL) {
        printf("%s", buffer);
      }
      
      fclose(fp);
      x = x + 1;
    
    }
    return 0;
  }
}
