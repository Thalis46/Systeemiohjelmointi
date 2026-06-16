#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Linked list*/
typedef struct node {
  char *line;
  struct node *next;
} Node;

/*Pushing words or lines to linked list*/
void push (Node **top, char *line) {
  /*Malloc used to allocate memory*/
  Node *node = malloc(sizeof(Node));
  if (!node) {
    fprintf(stderr, "malloc failed");
    exit (1);
  }
  
  node->line = strdup(line);
  if (!node->line) {
    fprintf(stderr, "strdup failed");
    exit (1);
  }
  
  node->next = *top;
  *top = node;
}

/*Pop words or lines out of linked list*/
char *pop(Node **top) {
  if (*top == NULL)
    return NULL;
    
  Node *temp = *top;
  char *line = temp->line;
  *top = temp->next;
  free(temp);
  return line;
}

int main(int argc, char *argv[]) {
  /*One argument reading one line which user input and reverse words*/
  if(argc == 1) {
    
    char *line = NULL;
    size_t size = 0;
    Node *stack = NULL;
    
    fprintf(stdout, "Write your text: ");
    if (getline(&line, &size, stdin) != 1) {
      char *saveptr;
      char *token = strtok_r(line, " \t\r\n", &saveptr);
      
      while (token) {
        push(&stack, token);
        token = strtok_r(NULL, " \t\r\n", &saveptr);
      }
    }
    free(line);
    
   
    char *out;
      while ((out = pop(&stack)) != NULL) {
        fprintf(stdout, "%s\n", out);
        free(out);
      }

    
    
    return 0;
  } else {
    /*Reading input file*/
    FILE *fp = fopen(argv[1], "r");
    
    if (fp == NULL) {
      fprintf(stderr, "error: cannot open file '%s'\n", argv[1]);
      exit(1);
    }
    
    Node *stack = NULL;
    char *line = NULL;
    size_t size = 0;
    ssize_t read;
    
    while ((read = getline(&line, &size, fp)) != -1) {
      push(&stack, line);
    }
    
    free(line);
    fclose(fp);
    /*print on the screen*/
    if(argc == 2) {
      
      char *out;
      while ((out = pop(&stack)) != NULL) {
        fprintf(stdout, "%s", out);
        free(out);
      }
      
      return 0;
      /*print on the file*/
    } else if(argc == 3) {
      /*Compare input and output files*/
      if (strcmp(argv[1], argv[2]) == 0) {
        fprintf(stderr, "Input and output file must differ\n");
        exit(1);
      }
    
      FILE *fpw = fopen(argv[2], "w");
      
      if (fpw == NULL) {
        fprintf(stderr, "error: cannot open file '%s'\n", argv[2]);
        exit(1);
      }
      
      char *out;
      while ((out = pop(&stack)) != NULL) {
        fprintf(fpw, "%s", out);
        free(out);
      }
      
      return 0;
      
    } else {
      fprintf(stderr, "usage: reverse <input> <output>\n");
      exit(1);
    }
  
  }
  
}
