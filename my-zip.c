#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    /*checking right amout of files*/
    if (argc < 2) {
        fprintf(stderr, "my-zip: file1 [file2 ...]\n");
        exit(1);
    }

    FILE *fp;
    int prev = -1;
    int curr;
    int count = 0;
    /*looping through all files if multiple*/
    for (int i = 1; i < argc; i++) {

        fp = fopen(argv[i], "r");
        /*check if file opens*/
        if (fp == NULL) {
            fprintf(stderr, "my-zip: cannot open file\n");
            exit(1);
        }
        /*counting same consecutive characters*/
        while ((curr = fgetc(fp)) != EOF) {

            if (prev == -1) {
                prev = curr;
                count = 1;
            }
            else if (curr == prev) {
                count++;
            }
            else {
                fwrite(&count, sizeof(int), 1, stdout);
                fwrite(&prev, sizeof(char), 1, stdout);
                prev = curr;
                count = 1;
            }
        }

        fclose(fp);
    }
    /*last characters added to file*/
    if (prev != -1) {
        fwrite(&count, sizeof(int), 1, stdout);
        fwrite(&prev, sizeof(char), 1, stdout);
    }

    return 0;
}

