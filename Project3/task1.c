#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define MAX 1024

int total = 0;
int n1, n2;
char *s1, *s2;
FILE *fp;
pthread_mutex_t mutex;

void readf(FILE *fp)
{
    if ((fp = fopen("strings.txt", "r")) == NULL)
    {
        printf("ERROR: can't open string.txt!\n");
        exit(1);
    }

    s1 = (char *)malloc(sizeof(char) * MAX);
    if (s1 == NULL)
    {
        printf("ERROR: Out of memory!\n");
        exit(1);
    }

    s2 = (char *)malloc(sizeof(char) * MAX);
    if (s2 == NULL)
    {
        printf("ERROR: Out of memory\n");
        exit(1);
    }

    /*read s1 s2 from the file*/
    s1 = fgets(s1, MAX, fp);
    s2 = fgets(s2, MAX, fp);
    n1 = strlen(s1) - 1; /*length of s1*/
    n2 = strlen(s2) - 1; /*length of s2*/
    if (s1 == NULL || s2 == NULL || n1 < n2) /*when error exit*/
    {
        printf("ERROR: Invalid input!\n");
        exit(1);
    }
}

void *num_substring(void *arg)
{
    int thread_id = *((int *)arg);
    int i, j, k;
    int count;
    int chunk_size = (n1 - n2 + 1) / 4; // divide the work among 4 threads
    int start = thread_id * chunk_size;
    int end = (thread_id == 3) ? (n1 - n2 + 1) : (start + chunk_size);

    for (i = start; i < end; i++)
    {
        count = 0;
        for (j = i, k = 0; k < n2; j++, k++)
        { /*search for the next string of size of n2*/
            if (*(s1 + j) != *(s2 + k))
            {
                break;
            }
            else
                count++;
            if (count == n2)
            {
                pthread_mutex_lock(&mutex);
                total++; /*find a substring in this step*/
                pthread_mutex_unlock(&mutex);
            }
        }
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    int count;
    pthread_t threads[4];
    int thread_ids[4];
    pthread_mutex_init(&mutex, NULL);

    readf(fp);

    for (int i = 0; i < 4; i++)
    {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, num_substring, &thread_ids[i]);
    }

    for (int i = 0; i < 4; i++)
    {
        pthread_join(threads[i], NULL);
    }

    count = total;
    printf("The number of substrings is: %d\n", count);

    pthread_mutex_destroy(&mutex);
    return 0;
}
