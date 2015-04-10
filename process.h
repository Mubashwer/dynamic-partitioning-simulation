/**
  * Name: Mubashwer Salman Khurshid
  * Username: mskh
  * StudentID: 601738
  *
  * Library for process queue and process-in-memory list
  */
#ifndef _PROCESS_INCLUDED_
#define _PROCESS_INCLUDED_


#define MAX_LINE_SIZE 255

typedef struct process
{
    int pid; /* process id */
    int size; /* size of process */
    int start; /* starting position w.r.t memory */
    int order; /* a relative order of entry into memory */
    int swapped; /* number of times it process is swapped out of memory */
    struct process *next; 

} process_t;


/*****************************************************************************/
/* Prototypes for process queue functions */
/*****************************************************************************/

int process_empty(); /* checks if queue is empty or not */
process_t *make_pq_node(int pid, int size); /* makes a queue node */
int process_enqueue(process_t *node); /* inserts node into queue */
process_t *process_dequeue(); /* removes earliest node from queue */
void load_into_queue(char *filename); /* load processes into queue from file */


/*****************************************************************************/
/* Prototypes for process-in-memory list function */
/*****************************************************************************/

int memory_empty(); /* checks if memory is empty or not */
void load_into_memory(process_t *node, int start); /* add process to memory */
process_t *evict(); /* remove a process from memory */
int give_numprocesses(); /* gives the number of processes in memory */
double give_memusage(); /* gives the percentage of memory usage */
void free_memory(); /* deallocates dynamically allocated memory */

#endif
