#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/sysinfo.h>

typedef struct {
  char *data;
  int start;
  int end;

  char *out;
  int out_size;
} task_t;
/*Compressing file to RLE*/
void *compress(void *arg) {
  task_t *t = (task_t *)arg;
  
  int max_size = (t->end - t->start) * (sizeof(int) + 1);
  char *out = malloc(max_size);
  int k = 0;

  int i = t->start;
  while (i < t->end) {
    char c = t->data[i];
    int count = 0;
    /*counting same characters*/
    while (i < t->end && t->data[i] == c) {
      count++;
      i++;
    }
    /*store results*/
    *(int *)(out + k) = count;
      k += sizeof(int);
      out[k++] = c;
  }
  /*saving results to struct*/
  t->out = out;
  t->out_size = k;
  return NULL;
}

int main(int argc, char *argv[]) {
  if (argc < 2) return 1;
  /*looping through files*/
  for (int file_i = 1; file_i < argc; file_i++) {

    FILE *f = fopen(argv[file_i], "r");
      if (!f) continue;
      /*check file size*/
      fseek(f, 0, SEEK_END);
      int size = ftell(f);
      rewind(f);

      char *data = malloc(size);
      fread(data, 1, size, f);
      fclose(f);

      /*checking available cores to max out threads*/
      int cores_available = get_nprocs();

      int nthreads = cores_available;
      if (nthreads > size) nthreads = size;
      if (nthreads < 1) nthreads = 1;
      /*creating threads*/
      pthread_t threads[nthreads];
      task_t tasks[nthreads];
      /*every thread gets same amount size of original file*/
      int chunk = size / nthreads;

      for (int i = 0; i < nthreads; i++) {
        tasks[i].data = data;
        tasks[i].start = i * chunk;
        tasks[i].end = (i == nthreads - 1) ? size : (i + 1) * chunk;

        pthread_create(&threads[i], NULL, compress, &tasks[i]);
      }

      for (int i = 0; i < nthreads; i++) {
        pthread_join(threads[i], NULL);
      }
      /*writing output*/
      for (int i = 0; i < nthreads; i++) {
        fwrite(tasks[i].out, 1, tasks[i].out_size, stdout);
        free(tasks[i].out);
      }

      free(data);
  }

  return 0;
}
