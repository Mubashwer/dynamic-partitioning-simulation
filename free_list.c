/**
  * Name: Mubashwer Salman Khurshid
  * Username: mskh
  * StudentID: 601738
  *
  * Library for process queue and process-in-memory list
  */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "free_list.h"


/*****************************************************************************/
/* Variables and Functions of free-list of memory holes */
/*****************************************************************************/

/* root for the free-list */
hole_t *hole_head = NULL;
/* starting position of the previously found hole, needed for next-fit */
int last_hole = 0;


hole_t *make_hole_node(int start, int size)
{
    hole_t *hole = malloc(sizeof(hole_t));
    hole->size = size;
    hole->start = start;
    hole->next = NULL;
    return hole;
}


hole_t *make_hole(process_t *out)
{
    
    /* a new hole in the position of the evicted process is created */
    hole_t *new_hole = make_hole_node(out->start, out->size);
    int start, end, current_end;
    hole_t *previous = hole_head;
    hole_t *current = hole_head;

    while(current != NULL)
    {
        start = new_hole->start;
        end = new_hole->size + start;
        current_end = current->start + current->size;

        /* if there is any adjacent hole: */
        if(current->start == end || current_end == start)
        {
            /* new hole size is updated */
            new_hole->size = new_hole->size + current->size;
            /* new hole position is updated */
            if(current->start < new_hole->start)
                new_hole->start = current->start;
            
            if(current == hole_head)
                hole_head = current->next;
            else
                previous->next = current->next;
            /* old hole which is merged is freed */
            free(current);
            current = previous->next;
        }
        else
        {
            previous = current;
            current = current->next;
        }
    }
    /* new hole is attached to the end of the list */
    if(hole_head == NULL)
        hole_head = new_hole;
    else
        previous->next = new_hole;
    return new_hole;
}


hole_t *choose_hole(hole_t *hole_previous, hole_t *hole, int size, char *algorithm)
{
    hole_t *current = hole_head;
    hole_t *previous = NULL;

    /* once there exists a large enough hole, this chooses a  hole according
    to the given algorithm */
    while(current != NULL)
    {
        /* if the hole is large enough */
        if(current->size >= size) 
        {
            /* first: earlier holes get priority */
            if(!strcmp(algorithm, "first") && current->start < hole->start) {
                hole = current;
                hole_previous = previous;
            }
            /* best: smaller holes get priority */
            else if(!strcmp(algorithm, "best") && current->size < hole->size) {
                hole = current;
                hole_previous = previous;
            }
            /* worst: largeer holes get priority */
            else if(!strcmp(algorithm, "worst") && current->size > hole->size) {
                hole = current;
                hole_previous = previous;
            }
            /* next:hole with closest starting position greater than previously
               found hole is given priority */
            else if(!strcmp(algorithm,"next") && current->start >= last_hole &&
                current->start < hole->start) {
                hole = current;
                hole_previous = previous;
            }
            else if(current->size ==hole->size && current->start < hole->start) {
                hole = current;
                hole_previous = previous;
            }
        }
        /* next: the loop and last hole position is reset if end is reached */
        if(!strcmp(algorithm, "next") && current->next == NULL &&
            hole->start < last_hole)
        {
            current = hole_head;
            previous = NULL;
            last_hole = 0;
        }
        else
        {
            previous = current;
            current = current->next;
        }
    }
    last_hole = hole->start;

    return hole_previous;
}


void use_hole(process_t *in, char *algorithm)
{

    hole_t *current = hole_head;
    hole_t *previous = NULL;
    process_t *out = NULL;

    /* iterates free-list until a large enough hole is found/created */
    while(1)
    {
        current = hole_head;
        previous = NULL;
        while(current != NULL && current->size < in->size) 
        {
            previous = current;
            current = current->next;
        }
        /* if a large enough hole already exists then break */
        if(current != NULL)
            break;
        /* otherwise get a process out and back to queue and and make a hole */ 
        out = evict();
        make_hole(out);
        process_enqueue(out);

    }

    /* once there is a large enough hole, choose a hole according
       to given algorithm */ 
    previous = choose_hole(previous, current, in->size, algorithm);
    if(previous == NULL)
        current = hole_head;
    else
        current = previous->next;
    
    /* if the hole size fits the process to be loaded exactly then the process
       is loaded and the hole is removed */
    if(current->size == in->size)
    {
        if(current == hole_head)
            hole_head = current->next;
        else
            previous->next = current->next;
        //if(*it == 4) printf("HOLE %d\n", current->start);
        load_into_memory(in, current->start);
        free(current);
        return;
    }
    /* otherwise the position and size of hole is updated after loading process */
    load_into_memory(in, current->start);
    current->size -= in->size;
    current->start += in->size;
    
    return;
}



int give_numholes()
{
    int num = 0;
    hole_t *current = hole_head;
    while(current != NULL)
    {
        num++;
        current = current->next;
    }
    return num; 
}



void free_free_list()
{   
    hole_t *current = hole_head;
    hole_t *temp = NULL;
    while(current != NULL)
    {
        temp = current;
        current = current->next;
        free(temp);
    }
    return;
}
