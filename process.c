/**
  * Name: Mubashwer Salman Khurshid
  * Username: mskh
  * StudentID: 601738
  *
  * Library for process queue and process-in-memory list
  */


#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "process.h"


/*****************************************************************************/
/* Variables and Functions of process queue */
/*****************************************************************************/


/* root for process queue */
process_t *pq_head = NULL;


int process_empty()
{
    return (pq_head == NULL);
}


process_t *make_pq_node(int pid, int size)
{
    process_t *node = malloc(sizeof(process_t));
    node->size = size;
    node->pid = pid;
    node->swapped = 0;
    node->next = NULL;
    return node;
}


int process_enqueue(process_t *node)
{
    /* if process is swapped out thrice, it is no longer needed */
    if(node->swapped >= MAX_SWAP)
    {
        free(node);
        return 0;
    }
    if(process_empty())
    {
        pq_head = node;
        return 1;
    }
    process_t *current = pq_head;
    while(current->next != NULL)
        current = current->next;
    current->next = node;
    return 1;
}


process_t *process_dequeue()
{
    if(process_empty())
        return NULL;
    process_t *out = pq_head;
    pq_head = pq_head->next;
    out->next = NULL;
    return out;
}


void load_into_queue(char *filename)
{
    int pid, size;
    char line[MAX_LINE_SIZE + 1];
    
    /* open file and read it line by line */   
    FILE *input_file = fopen(filename, "r");
    if(input_file == NULL)
    {
        printf("Error opening file %s\n", filename);
        exit(EXIT_FAILURE);
    }
    
    while(fgets(line, sizeof(line), input_file))
    {
        /* read formatted data and inser into queue*/
        sscanf(line,"%d %d", &pid, &size);
        process_enqueue(make_pq_node(pid, size));
    }
    fclose(input_file);
    return;
}

/*****************************************************************************/
/* Variables and Functions of memory-in-process list */
/*****************************************************************************/


/* root for process-in-memory list */
process_t *mem_head = NULL;
/* total memory size to be given by user */
int mem_size = 0;
/* global order of entry of process into memory */
int order = 0;


int memory_empty()
{
    return (mem_head == NULL);
}


void load_into_memory(process_t *node, int start)
{
    node->next = NULL;
    if(memory_empty())
    {
        mem_head = node;
        node->start = 0; /* starting position is 0 when memory is empty */
        node->order = order++; /* increment relative order/time of entry */
        return;
    }

    process_t *current = mem_head;
    while(current->next != NULL)
        current = current->next;
    
    node->start = start;
    node->order = order++;
    current->next = node;
    return;
}


/*void print_memory()
{
    process_t *c = mem_head;
    while(c != NULL)
    {
        printf("pid = %d start = %d, size = %d\n", c->pid, c->start, c->size);
        c = c->next;
    }

}*/


process_t *evict()
{
    
    process_t *current = mem_head;
    process_t *previous = mem_head;
    process_t *out = mem_head;
    process_t *out_prev = NULL;
    while(current != NULL)
    {
        /* if a biger process is found.. */
        if(current->size >= out->size)
            /* or an earlier process if they are of the same size */
            if(current->size > out->size || current->order < out->order)
            {
                out_prev = previous;
                /*then the process is to be evicted */
                out = current;
            }
        
        previous = current;
        current =  current->next;
    };
    
    out->swapped++; 
   

    /* if the first item is to be evicted */
    if(out == mem_head)
    {
        mem_head = mem_head->next; 
        out->next = NULL;
        return out;
    }
    out_prev->next = out->next; 
    out->next = NULL;
    return out;
}

int give_numprocesses()
{
    int num = 0;

    process_t *current = mem_head;
    while(current != NULL)
    {
        num++;
        current = current->next;
    }
    return num;
}


double give_memusage()
{
    double used = 0;

    process_t *current = mem_head;
    while(current != NULL)
    {
        used += current->size;
        current = current->next;
    }
    /* rounds up the percentage of memory used */
    return ceil((used * 100) / (double) mem_size);
}


void free_memory()
{   
    process_t *current = mem_head;
    process_t *temp = NULL;
    while(current != NULL)
    {
        temp = current;
        current = current->next;
        free(temp);
    }
    return;
}
