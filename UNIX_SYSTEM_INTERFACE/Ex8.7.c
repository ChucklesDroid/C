/*Question:-  malloc accepts a size request without checking its plausibility; 
free believes that the block it is asked to free contains a valid size field 
Improve these routines so they make more pains with error checking. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define NALLOC 1024                             /* At time NALLOC bytes are allocated since system calls are slow */
#define MAXBYTES 10240                          /* Max bytes that malloc can allocate */
typedef unsigned Align ;                        /* Most restrictive type */
typedef union header{                           /* User defined data type representing memory block */
    struct{
        union header *next ;
        unsigned size ;
    } s;
    Align x;
} Header ;

Header base ;                                   /* Dummy variable for freelist */
Header *freep ;                                 /* First member of the freelist */
Header *Kandr_malloc( unsigned ) ;
Header *memcore( unsigned ) ;
unsigned maxalloc = 0 ;                         /* Maximum size of allocated memory */
void Kandr_free( Header * ) ;


/* Kandr_Malloc : user implementation of library function */
Header *Kandr_malloc( unsigned nu )
{
    Header *currp , *prevp ;                    /* Pointers to traverse the freelist */

/* Checking size request for plausibility */
    if ( nu > MAXBYTES ){
        fprintf(stderr,"Kandr_malloc: unable to alloc %u units\n",nu) ;
        return NULL;
    }

/* Calculating the no of units of memory block required */
    unsigned nunits = ( nu - 1 + sizeof(Header) ) / sizeof(Header) + 1; /* Taking Header into consideration */

/* Checking if freelist exists , if not then degenerate list is created */
    if( freep == NULL ){
        prevp = currp = base.s.next = &base ;   /* freelist is circular linked list */
        base.s.size  = 0;
    }
    prevp = freep ;                             /* Initialising prevp */

/* Traversing the freelist to find appropriate match */
    for( currp = prevp->s.next ; ; prevp = currp , currp = currp->s.next ){
    /* Case : appropriate match is found */
        if( currp->s.size >= nu ){
            /* case : exact match is found */
            if( currp->s.size == nu ){          /* Exact match is found */
                prevp->s.next = currp->s.next ; /* Block is delinked from the freelist */
            } else {                            
                currp->s.size -= nu ;           /* Splitting the block and tail end */
                currp += nu ;                   /* is returned */
                currp->s.size = nu ;
            }
            freep = prevp ;
            return (currp + 1) ;                /* Adjusting for Header */
        }

        if( currp == freep ){                   /* Asking memcore to allocate appropriate memory */
            if( memcore(nunits) == NULL )       /* Error encountered since no memory returned */
                return NULL ;               
        }
    }
}


/* Calling kernel to allocate memory */
Header *memcore( unsigned nu )
{
/* If no of units to be allocated is less than NALLOC then NALLOC units are
   allocated since calls to kernel are very time taxing */
    if( nu < NALLOC )
        nu = NALLOC ;
    
/* Memory Block initialised and inserted in the free list */
    char *programbrk;
    programbrk = sbrk( nu * sizeof(Header) ) ; 
    Header *insertp = (Header *)programbrk ;    // Memory Block to be inserted in freelist
    if( insertp == (void *)-1 )
        return NULL ;
    insertp->s.size = nu ;


/* initialising maxalloc to makesure malloced block is freed */
    maxalloc = ( maxalloc > nu ) ? maxalloc : nu ;


/* Inserting the memory block in the freelist and resetting freep pointer*/
    Kandr_free( insertp ) ;
    return freep ;
}


/* Puts insertp in freelist */
void Kandr_free( Header *insertp )
{
    Header *currp ;
/* Checking if valid memory block is being freed */
    if( insertp->s.size == 0 || insertp->s.size > maxalloc ){
        fprintf(stderr,"Kandr :Invalid memory block passed") ;
        return ;
    }


/* Traversing the freelist to find appropriate position to insert memory block */
    for( currp = freep ; ((insertp > currp) && ( currp->s.next > insertp )) ; currp = currp->s.next){
    /* case : if block to be inserted is either rightmost of leftmost in the freelist */
        if( (currp > currp->s.next) && ( (insertp > currp) || (insertp > currp->s.next) ))        
            break ;
    }       


/* Inserting the block in the list and taking care of both ends . If free block 
   present on either side then those blocks are coalesced into one */
   /* Right end is first checked */
    if( (insertp + insertp->s.size) == currp->s.next ){
       insertp->s.size += currp->s.next->s.size ;
       insertp->s.next = currp->s.next->s.next ;
    } else {
       insertp->s.next = currp->s.next ;
    }

   /* Left end is checked next */
    if( (currp + currp->s.size) == insertp ){
        currp->s.next = insertp->s.next ;
        currp->s.size += insertp->s.size ;
    } else {
        currp->s.next = insertp ;
    }

   /* Freep is reinitialised to point at previous memory block */
   freep = currp ;
}
