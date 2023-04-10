/*
list-forming.c:
Each thread generates a data node, attaches it to a global list. This is
reapeated for K times.
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
#define K 200 // genreate a data node for K times in each thread

struct Node
{
    int data;
    struct Node* next;
};

struct list
{
    struct Node * header;
    struct Node * tail;
};

struct list *List;
_Atomic(struct Node*) head; // Head of the Michael-Scott queue

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

void * producer_thread( void *arg)
{
    bind_thread_to_cpu(*((int*)arg));//bind this thread to a CPU
    struct Node * ptr;
    int counter = 0;
    /* generate and attach K nodes to the global list */
    while( counter < K )
    {
        ptr = generate_data_node();
        if( NULL != ptr )
        {
            struct Node* head_snapshot = atomic_load(&head); // Snapshot of the head of the queue
            ptr->data = 1; // generate data

            /* Attach the generated node to the global list using Michael-Scott Queue */
            do {
                ptr->next = head_snapshot;
            } while (!atomic_compare_exchange_weak(&head, &head_snapshot, ptr));

            ++counter;
        }
    }
}

int main(int argc, char* argv[])
{
    int i, num_threads;
    int NUM_PROCS;//number of CPU
    int* cpu_array = NULL;
    struct Node *tmp,*next;
    struct timeval starttime, endtime;

    if(argc == 1){
        printf("ERROR: please provide an input arg (the number of threads)\n");
        exit(1);
    }
    num_threads = atoi(argv[1]); //read num_threads from user
    pthread_t producer[num_threads];
    NUM_PROCS = sysconf(_SC_NPROCESSORS_CONF);//get number of CPU

    if( NUM_PROCS > 0)
    {
        cpu_array = (int *)malloc(NUM_PROCS*sizeof(int));
        if( cpu_array == NULL )
        {
            printf("Allocation failed!\n");
            exit(0);
        }
        else
        {
            for( i = 0; i < NUM_PROCS; i++)
                cpu_array[i] = i;
        }
    }

    List = (struct list *)malloc(sizeof(struct list));
