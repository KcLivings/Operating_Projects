#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define MAX 1024

int total = 0;
int n1, n2;
char *s1, *s2;
FILE *fp;
pthread_mutex_t total_mutex; // Mutex to protect the total count

// Function to read input strings from file
int readf(FILE *fp)
{
    if ((fp = fopen("strings.txt", "r")) == NULL)
    {
        printf("ERROR: can't open string.txt!\n");
        return 0;
    }

    s1 = (char *)malloc(sizeof(char) * MAX);
    if (s1 == NULL)
    {
        printf("ERROR: Out of memory!\n");
        return -1;
    }

    s2 = (char *)malloc(sizeof(char) * MAX);
    if (s2 == NULL)
    {
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
    return 1;
}

// Function to count number of substrings
void *num_substring(void *arg)
{
    int id = *((int *)arg);
    int i, j, k;
    int count;
    int start = id * (n1 - n2 + 1) / 4; // Divide the work among threads
    int end = (id + 1) * (n1 - n2 + 1) / 4;

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
                pthread_mutex_lock(&total_mutex);
                total++; /*find a substring in this step*/
                pthread_mutex_unlock(&total_mutex);
            }
        }
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    int count;
    pthread_t threads[4]; // Array to store thread IDs
    int thread_ids[4];    // Array to store thread IDs
    pthread_mutex_init(&total_mutex, NULL); // Initialize mutex

    readf(fp);

    // Create 4 threads
    for (int i = 0; i < 4; i++)
    {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, num_substring, &thread_ids[i]);
    }

    // Join all threads
    for (int i = 0; i < 4; i++)
    {
        pthread_join(threads[i], NULL);
    }

    printf("The number of substrings is: %d\n", total);

    // Clean up
    free(s1);
    free(s2);
    pthread_mutex_destroy(&total_mutex);
    return 1;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define MAX 1024

int total = 0;
int n1, n2;
char *s1, *s2;
FILE *fp;
pthread_mutex_t total_mutex; // Mutex to protect the total count

// Function to read input strings from file
int readf(FILE *fp)
{
    if ((fp = fopen("strings.txt", "r")) == NULL)
    {
        printf("ERROR: can't open string.txt!\n");
        return 0;
    }

    s1 = (char *)malloc(sizeof(char) * MAX);
    if (s1 == NULL)
    {
        printf("ERROR: Out of memory!\n");
        return -1;
    }

    s2 = (char *)malloc(sizeof(char) * MAX);
    if (s2 == NULL)
    {
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
    return 1;
}

// Function to count number of substrings
void *num_substring(void *arg)
{
    int id = *((int *)arg);
    int i, j, k;
    int count;
    int start = id * (n1 - n2 + 1) / 4; // Divide the work among threads
    int end = (id + 1) * (n1 - n2 + 1) / 4;

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
                pthread_mutex_lock(&total_mutex);
                total++; /*find a substring in this step*/
                pthread_mutex_unlock(&total_mutex);
            }
        }
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    int count;
    pthread_t threads[4]; // Array to store thread IDs
    int thread_ids[4];    // Array to store thread IDs
    pthread_mutex_init(&total_mutex, NULL); // Initialize mutex

    readf(fp);

    // Create 4 threads
    for (int i = 0; i < 4; i++)
    {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, num_substring, &thread_ids[i]);
    }

    // Join all threads
    for (int i = 0; i < 4; i++)
    {
        pthread_join(threads[i], NULL);
    }

    printf("The number of substrings is: %d\n", total);

    // Clean up
    free(s1);
    free(s2);
    pthread_mutex_destroy(&total_mutex);
    return 1;
}

