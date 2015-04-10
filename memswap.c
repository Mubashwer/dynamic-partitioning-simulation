/**
  * Name: Mubashwer Salman Khurshid
  * Username: mskh
  * StudentID: 601738
  *
  * Simulation of memory management process swapping (COMP30023 Project 1)
  */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>   
#include <string.h>
#include <unistd.h>

#include "free_list.h"


/* Extern declarations: */
extern  int     optind;
extern  char    *optarg;
extern  int     mem_size;
extern  hole_t  *hole_head;

int main(int argc, char** argv)
{
    char input; /* argument identifier */
    char *filename;
    char *algorithm; /* algorithm for choosing hole */
    process_t *out; /* dequeue process */
  
    while ((input = getopt(argc, argv, "f:a:m:")) != EOF)
    {
        switch (input)
        {
            case 'f':
            /* set the filename of input data */
            filename = optarg;
            break;

            case 'a':
            /* set the algorithm for placing process in memory */
            algorithm = optarg;
            break;

            case 'm':
            /* set the value of size (int value) based on optarg */
            mem_size = atoi(optarg);
            break;

            default:
            break;
        } 
    }

    /* load process from file into queue */
    load_into_queue(filename);
    
    /* initialize the free list with empty memory of given size */
    hole_head = make_hole_node(0, mem_size);
    
    while(1)
    {
        
        /* dequeue process, break from loop if queue is empty */
        if((out = process_dequeue()) == NULL) 
            break;

        /* load process into memory by using free holes, evict older process
            and create larger/more holes if necessary */
        use_hole(out, algorithm);
        
        /* print memory status */
        printf("%d loaded, numprocesses=%d, numholes=%d, memusage=%.0f%%\n",
            out->pid, give_numprocesses(), give_numholes(), give_memusage());
    }  
    

    /* free dynamically allocated memory */
    free_free_list();
    free_memory();


    return 0;
}