/**
  * Name: Mubashwer Salman Khurshid
  * Username: mskh
  * StudentID: 601738
  *
  * Library for free-list of memory holes
  */
#ifndef _FREE_LIST_INCLUDED_
#define _FREE_LIST_INCLUDED_
 

#include "process.h"


typedef struct mem_hole
{
    int size;
    int start;
    struct mem_hole *next; 

} hole_t;


/*****************************************************************************/
/* Prototypes for free-list functions */
/*****************************************************************************/

/* creates a node for the list */
hole_t *make_hole_node(int start, int size); 
/* creates a hole from the position of an evicted process and merges holes
   if required */
hole_t *make_hole(process_t *out);
/* choose hole for process to use when there is enough space using given
   algorithm */
hole_t *choose_hole(hole_t *hole_previous, hole_t *hole, int size,
 char *algorithm);
/* controls which holes to use for loading process and calls other methods
 to load process and create/merge holes */
void use_hole(process_t *in, char *algorithm);
/* gives the number of free holes */
int give_numholes();
/* deallocates dynamically allocated memory */
void free_free_list();

#endif
