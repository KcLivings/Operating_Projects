#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_BUFFER_SIZE 12
#define MAX_MESSAGE_SIZE 1024

char buffer[MAX_BUFFER_SIZE];
int buffer_index = 0;
int buffer_count = 0;
FILE* fp;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_producer = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_consumer = PTHREAD_COND_INITIALIZER;

void* producer(void* arg) {
    char c;
    while ((c = fgetc(fp)) != EOF) {
        pthread_mutex_lock(&mutex);

        while (buffer_count == MAX_BUFFER_SIZE) {
            // Buffer is full, wait for consumer to consume
            pthread_cond_wait(&cond_producer, &mutex);
        }

        buffer[buffer_index] = c;
        buffer_index = (buffer_index + 1) % MAX_BUFFER_SIZE;
        buffer_count++;

        pthread_cond_signal(&cond_consumer);
        pthread_mutex_unlock(&mutex);
    }

    pthread_mutex_lock(&mutex);
    // Signal consumer that producer has finished
    pthread_cond_signal(&cond_consumer);
    pthread_mutex_unlock(&mutex);

    return NULL;
}

void* consumer(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);

        while (buffer_count == 0) {
            // Buffer is empty, wait for producer to produce
            pthread_cond_wait(&cond_consumer, &mutex);

            // Check if producer has finished
            if (feof(fp)) {
                pthread_mutex_unlock(&mutex);
                return NULL;
            }
        }

        char c = buffer[(buffer_index - buffer_count + MAX_BUFFER_SIZE) % MAX_BUFFER_SIZE];
        buffer_count--;

        pthread_cond_signal(&cond_producer);
        pthread_mutex_unlock(&mutex);

        printf("%c", c); // Print the character
        fflush(stdout); // Flush stdout to ensure immediate printing
    }
}

int main() {
    if ((fp = fopen("message.txt", "r")) == NULL) {
        printf("ERROR: can't open message.txt!\n");
        return 1;
    }

    pthread_t producer_thread, consumer_thread;

    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    fclose(fp);

    return 0;
}
