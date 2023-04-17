/*
list-forming.c:
Each thread generates a data node, attaches it to a global list. This is
repeated for K times.
There are num_threads threads. The value of "num_threads" is input by the
student.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/param.h>
#include <sched.h>

#define K 200 // generate a data node for K times in each thread

struct Node
{
    int data;
    struct Node* next;
};

struct list
{
    struct Node *header;
    struct Node *tail;
};

pthread_mutex_t mutex_lock;
struct list *List;
int num_threads;
int NUM_PROCS;
int* cpu_array = NULL;

void bind_thread_to_cpu(int cpuid) {
    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(cpuid, &mask);
    if (sched_setaffinity(0, sizeof(cpu_set_t), &mask)) {
        fprintf(stderr, "sched_setaffinity");
        exit(EXIT_FAILURE);
    }
}

struct Node* generate_data_node()
{
    struct Node *ptr;
    ptr = (struct Node *)malloc(sizeof(struct Node));
    if( NULL != ptr ){
        ptr->next = NULL;
    }
    else {
        printf("Node allocation failed!\n");
    }
    return ptr;
}

void * producer_thread(void *arg)
{
    bind_thread_to_cpu(*((int*)arg)); // bind this thread to a CPU
    struct Node *ptr;
    int counter = 0;
    
    /* generate and attach K nodes to the global list */
    while (counter < K) {
        ptr = generate_data_node();
        if (NULL != ptr) {
            pthread_mutex_lock(&mutex_lock); // acquire lock before accessing critical region
            ptr->data = 1; // generate data
            /* attach the generated node to the global list */
            if (List->header == NULL) {
                List->header = List->tail = ptr;
            }
            else {
                List->tail->next = ptr;
                List->tail = ptr;
            }
            pthread_mutex_unlock(&mutex_lock); // release lock after accessing critical region
            counter++;
        }
    }
}

int main(int argc, char* argv[])
{
    int i;
    struct Node *tmp, *next;
    struct timeval starttime, endtime;
    
    if (argc == 1) {
        printf("ERROR: please provide an input arg (the number of threads)\n");
        exit(1);
    }
    num_threads = atoi(argv[1]); // read num_threads from user
    
    pthread_t producer[num_threads];
    NUM_PROCS = sysconf(_SC_NPROCESSORS_CONF); // get number of CPU
    
    if (NUM_PROCS > 0) {
        cpu_array = (int *)malloc(NUM_PROCS * sizeof(int));
        if (cpu_array == NULL) {
            printf("Allocation failed!\n");
            exit(0);
        }
        else {
            for (i = 0; i < NUM_PROCS; i++)
                cpu_array[i] = i;
        }
    }
    
    pthread_mutex_init(&mutex_lock, NULL);
    List = (struct list *)malloc(sizeof(struct list));
    
    if (NULL == List) {
        printf("End here\n");
        exit(0);
    }
    
    List->header = List->tail = NULL;
    gettimeofday(&starttime, NULL); // get program start time
    
    for (i = 0; i < num_threads; i++) {
        pthread_create(&producer[i], NULL, producer_thread, (void *)&cpu_array[i % NUM_PROCS]);
    }
    
    for (i = 0; i < num_threads; i++) {
        pthread_join(producer[i], NULL);
    }
    
    gettimeofday(&endtime, NULL); // get program end time
    double elapsed_time = (endtime.tv_sec - starttime.tv_sec) * 1000.0 + (endtime.tv_usec - starttime.tv_usec) / 1000.0;
    
    printf("Generated %d data nodes in %d threads in %.2f ms\n", K * num_threads, num_threads, elapsed_time);
    
    /* Clean up */
    tmp = List->header;
    while (tmp != NULL) {
        next = tmp->next;
        free(tmp);
        tmp = next;
    }
    free(List);
    pthread_mutex_destroy(&mutex_lock);
    if (cpu_array != NULL) {
        free(cpu_array);
    }
    
    return 0;
}
