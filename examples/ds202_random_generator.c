#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    long n = 62460029;
    FILE *fp = fopen("randomDNA.fasta", "w");

    if (!fp) {
        printf("Error opening file\n");
        return 1;
    }

    srand(time(NULL));

    fprintf(fp, ">random_dna\n");

    char bases[] = {'A','C','G','T'};

    for (long i = 0; i < n; i++) {
        fputc(bases[rand() % 4], fp);
        if ((i + 1) % 60 == 0)
            fputc('\n', fp);
    }

    fclose(fp);
    printf("Random DNA generated.\n");
    return 0;
}
