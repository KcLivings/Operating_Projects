#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

#define MAX 1024
int total = 0;
int n1, n2;
char *s1, *s2;
FILE *fp;
int num_threads = 4; // Number of threads to use

// Struct to pass parameters to thread function
struct ThreadData {
    int id; // Thread ID
    int start; // Start index for substring search
    int end; // End index for substring search
};

// Thread function to count substrings
void *count_substring(void *arg) {
    struct ThreadData *data = (struct ThreadData *)arg;
    int i, j, k;
    int count;
    for (i = data->start; i <= data->end; i++) {
        count = 0;
        for (j = i, k = 0; k < n2; j++, k++) { // Search for the next string of size of n2
            if (*(s1 + j) != *(s2 + k)) {
                break;
            } else {
                count++;
            }
            if (count == n2) {
                total++; // Find a substring in this step
            }
        }
    }
    pthread_exit(NULL);
}

int readf(FILE *fp) {
    if ((fp = fopen("strings.txt", "r")) == NULL) {
        printf("ERROR: can't open string.txt!\n");
        return 0;
    }
    s1 = (char *)malloc(sizeof(char) * MAX);
    if (s1 == NULL) {
        printf("ERROR: Out of memory!\n");
        return -1;
    }
    s2 = (char *)malloc(sizeof(char) * MAX);
    if (s2 == NULL) {
        printf("ERROR: Out of memory\n");
        return -1;
    }
    /*read s1 s2 from the file*/
    s1 = fgets(s1, MAX, fp);
    s2 = fgets(s2, MAX, fp);
    n1 = strlen(s1) - 1; /*length of s1*/
    n2 = strlen(s2) - 1; /*length of s2*/
    if (s1 == NULL || s2 == NULL || n1 < n2) /*when error exit*/
        return -1;
}

int main(int argc, char *argv[]) {
    int count;
    pthread_t threads[num_threads];
    struct ThreadData threadData[num_threads];

    readf(fp);

    // Divide the substring search among threads
    int chunk_size = n1 / num_threads;
    int remainder = n1 % num_threads;
    int start = 0;
    int end;
    for (int i = 0; i < num_threads; i++) {
        end = start + chunk_size - 1;
        if (remainder > 0) {
            end++;
            remainder--;
        }
        threadData[i].id = i;
        threadData[i].start = start;
        threadData[i].end = end;
        pthread_create(&threads[i], NULL, count_substring, &threadData[i]);
        start = end + 1;
    }

    // Wait for threads to finish
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("The number of substrings is: %d\n", total);
    return 1;
}
