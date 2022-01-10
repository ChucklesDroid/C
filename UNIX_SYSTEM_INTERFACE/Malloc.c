/* Refer book to understand storage allocator or following website ;- 
https://stackoverflow.com/questions/13159564/explain-this-implementation-of-malloc-from-the-kr-book */

#include <stdio.h>
#include <unistd.h>
#define NALLOC 1024

typedef long Align ;
typedef union header{
    struct {
        union header *ptr ;             /* Stores address of next header sized unit */
        unsigned size ;                 /* Stores number of header sized units */
    } s;
    Align x ;                           /* Most restrictive type for worst case scenario */
} Header ;

Header *kar_malloc( unsigned ) ;        /* Allocates memory from freelist */
Header *memcore( unsigned ) ;           /* Requests OS to allocate memory into free list */
void kar_free( void * ) ;

Header base ;                           /* First address stored in the free list */
Header *freep = NULL ;                  /* First entry in the free ilst */


/* Malloc : allocates memory from free list  */
Header *kar_malloc( unsigned nu )
{
    Header *currp , *prevp ;    /* Two variables to transverse the list */

/* Calculating no of Header sized memory block units to be allocated */
    unsigned nunits = ( nu - 1 + sizeof(Header) ) / sizeof(Header) + 1 ;

/* Search Free list for memory block big enough to complete the request */
    /* case :- if free list does not exist */
    if( freep == NULL ) {   /* Degenerate List is created (Remember freelist is circular linked list*/
        prevp = base.s.ptr = freep = &base ;
        base.s.size = 0 ;
    }

    prevp = freep ;         /* Initialising prevp to point at start of free list */

    /* case :- freelist exists and is traversed to find the appropriate match */
        /* currp points at the memory block after prevp to access the list */
    for( currp = prevp->s.ptr ; ; prevp = currp , currp = currp->s.ptr ){

/* Big enough memory block is found */
        if( currp->s.size >= nunits ){

    /* case :- exact match is found */
            if( currp->s.size == nunits ){
                prevp = currp->s.ptr ;
            }
    /* case :- memory block bigger than the request is found */
            else {
                currp->s.size -= nunits ;   /* Tail end is returned to the user */
                currp += nunits ;
                currp->s.size = nunits ;
            }
    /* freep is moved to point at the next block (in case of delinking) or is pointing
    at the residue memory block */
            freep = prevp->s.ptr ;
            return (currp + 1) ;    /* To accomodate for header */
        }

/* If the entire list is traversed but big enough block is not found then a request is made to OS*/
        if( currp == freep ){
            if( memcore(nunits) == NULL )
                return NULL ;       /* Failed to allocate memory */
        }
    }
}


/* memcore : requests OS to allocate memory and then divides it into Header sized blocks */
Header *memcore( unsigned nu )
{
    Header *insertp ;       /* New memory block to be inserted in the freelist */
    void *programbreak ;    /* first address after the end of data segment is program break */

/* Constant calls to OS can be taxing on memory so on each call atleast NALLOC size block is returned from user */
    if( nu < NALLOC )
        nu = NALLOC ;

/* sbrk is system call that increases the size of data segment and returns the previous
   program break */

   programbreak = sbrk( nu * sizeof(Header) ) ;
   /* if memory cannot be allocated NULL is returned */
   if( programbreak == (void *)-1 )
        return NULL ;

/* Creating a new header sized memory block */
    insertp = (Header *)programbreak ;
    insertp->s.size = nu ;

/* Calling the free function adds the memory block into the free list */   
    free((void *)(insertp + 1)) ;    /* Adjusting for Header */

/* Calling free changes freep to point at the newly allocated memory block so that its easier for malloc to allocate memory */
    return freep ;
}


/* kar_free :  */
void kar_free( void *p )
{
/* Initializing the insertion block */
    Header *insertp = (Header *)p -1 ; /* To point to the header of memory block */
    Header *currp ;                    /* Defines the current memory block */

/* Traverse the free list to find the exact position to insert memory block */
    for( currp = freep ; ((currp <= insertp) && ( insertp < currp->s.ptr)) ; currp = currp->s.ptr ){
    /* case : when block is to be inserted at the end ( to make it rightmost block)
            or when it is to be inserted at the start ( to make it leftmost block)        
    */
        if( currp >= currp->s.ptr && ((insertp > currp) || (insertp < currp->s.ptr)) )
            break ;
    }
    
/* If inserted block is adjacent to free block on either side then it is to be 
    coalesced into one block ( Therefore we check if they are contiguous ) */

    /* If block to be inserted is to right of free block */
    if( currp + currp->s.size == insertp ){
        currp->s.size += insertp->s.size ;
    } else {            /* Else insert the block into the free list */
        insertp->s.ptr = currp->s.ptr ;       
        currp->s.ptr = insertp ;
    }

    /* If block inserted is to left of free block */
    if( insertp + insertp->s.size == currp->s.ptr ){
        insertp->s.size += currp->s.ptr->s.size ;
        insertp->s.ptr = currp->s.ptr->s.ptr ;
    } 

/*
    A better implementation would be to adjust at both ends seperately.
    First right end is looked at i.e memory block towards the right of the block
    being inserted

    if( insertp + insertp->s.size == currp->s.ptr ){
        insertp->s.size += currp->s.ptr->s.size ;
        insertp->s.ptr = currp->s.ptr->s.ptr ;
    } else{
        insertp->s.ptr = currp->s.ptr ;
    }

    Now left end is looked at i.e the memory block towards the left of the block
    being inserted 

    if( currp + currp->s.size == insertp ){
        currp->s.size += insertp->s.size ;
        currp->s.ptr = insertp->s.ptr ;
    } else {
        currp->s.ptr = insertp.s-ptr ;
    }
*/

    /* Freep is reinitialised to point to previous memory block */
    freep = currp ;
}