#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    if (argc < 2) {
        fprintf(stderr, "my-unzip: file1 [file2 ...]\n");
        exit(1);
    }

    FILE *fp;
    int count;
    char ch;
    /*looping through files*/
    for (int i = 1; i < argc; i++) {

        fp = fopen(argv[i], "r");
        /*error if file open fails*/
        if (fp == NULL) {
            fprintf(stderr, "my-unzip: cannot open file\n");
            exit(1);
        }
        /*looping through one file*/
        while (fread(&count, sizeof(int), 1, fp) == 1) {

            if (fread(&ch, sizeof(char), 1, fp) != 1) {
                break;
            }
            /*printing each character from zipped file*/
            for (int j = 0; j < count; j++) {
                printf("%c", ch);
            }
        }

        fclose(fp);
    }

    return 0;
}
