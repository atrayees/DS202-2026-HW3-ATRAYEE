#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <divsufsort.h>

/* ================= TIMER ================= */
double now_seconds() {
    return (double)clock() / CLOCKS_PER_SEC;
}

/* ================= KASAI LCP ================= */
void build_LCP(const char *T, int *SA, int *LCP, int n) {
    int *rank = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
        rank[SA[i]] = i;

    int k = 0;

    for (int i = 0; i < n; i++) {
        if (rank[i] == n - 1) {
            k = 0;
            continue;
        }

        int j = SA[rank[i] + 1];

        while (i + k < n && j + k < n && T[i + k] == T[j + k])
            k++;

        LCP[rank[i]] = k;

        if (k > 0)
            k--;
    }

    free(rank);
}

/* ================= MAIN ================= */
int main(int argc, char **argv) {

    if (argc < 2) {
        printf("Usage: ./ds202_longest_repeat <input_file>\n");
        return 1;
    }

    /* ---------- READ FASTA FILE ---------- */
    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        printf("Error opening file\n");
        return 1;
    }

    long capacity = 70000000;   // safe for chrY
    char *T = (char *)malloc(capacity * sizeof(char));
    long n = 0;

    char buffer[1024];

    while (fgets(buffer, sizeof(buffer), fp)) {
        if (buffer[0] == '>') continue;  // skip FASTA header

        int len = strlen(buffer);

        for (int i = 0; i < len; i++) {
            if (buffer[i] == '\n' || buffer[i] == '\r')
                continue;

            T[n++] = buffer[i];
        }
    }

    fclose(fp);

    printf("Input length: %ld\n", n);

    /* ---------- BUILD SA ---------- */
    int *SA = (int *)malloc(n * sizeof(int));

    double t1 = now_seconds();
    divsufsort((unsigned char *)T, SA, n);
    double t2 = now_seconds();

    printf("SA construction time: %f seconds\n", t2 - t1);

    /* ---------- BUILD LCP ---------- */
    int *LCP = (int *)calloc(n, sizeof(int));

    double t3 = now_seconds();
    build_LCP(T, SA, LCP, n);
    double t4 = now_seconds();

    printf("LCP construction time: %f seconds\n", t4 - t3);

    /* ---------- FIND LONGEST REPEAT ---------- */
    double t5 = now_seconds();

    int max_lcp = 0;
    int idx = 0;

    for (long i = 0; i < n - 1; i++) {
        if (LCP[i] > max_lcp) {
            max_lcp = LCP[i];
            idx = i;
        }
    }

    double t6 = now_seconds();

    printf("Longest repeat length: %d\n", max_lcp);
    printf("Starting positions (0-based): %d , %d\n",
           SA[idx], SA[idx + 1]);

    printf("Identification time: %f seconds\n", t6 - t5);

    /* ---------- CLEANUP ---------- */
    free(SA);
    free(LCP);
    free(T);

    return 0;
}
