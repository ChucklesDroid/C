/* 			BFREE			*/
/* Write a routine bfree(p,n) that will free an arbitrary block of p of n characters into
 * freelst maintained by malloc and free. By using bfree ,a user can add a static or 
 * external array to the free list at any time */

#include <stdio.h>
#include <unistd.h>								/* For sbrk() */
#define NALLOC 1024                             /* At time NALLOC bytes are allocated since system calls are slow */
#define MAXBYTES 10240                          /* Max bytes that malloc can allocate */
typedef long Align ;							/* Most Restrictive type */
typedef union header{                           /* User defined data type representing memory block */
    struct{
        union header *next ;
        unsigned size ;
    } s;
    Align x;
} Header ;


Header base ;                                   /* Dummy variable for freelist */
Header *freep ;                                 /* First member of the freelist */
unsigned maxalloc = 0 ;                         /* Maximum size of allocated memory */
void Kandr_free( Header * ) ;					/* K&r implementation of library call free() */
void *bfree( void *p , unsigned n) ;			/* Free any arbitrary block into the free list */
int main( int argc , char *argv[] )
{
	char Arr[10] = "Aakarsh";
	printf("Size of header is %lu \n", sizeof(Header *));
	bfree( (void *)Arr , 10 ) ;
	printf("Address of Arr is %p\n" , Arr ) ;
	printf("Address of base is %p\n" , &base ) ;
	printf("Address pointed by freep is %p\n",freep) ;
	return 0 ;
}


/* Function that will free any static or external array */
void *bfree( void *p , unsigned n )
{
/* Returning when null is passed as argument */
	if( p == NULL ){
		fprintf(stderr,"bfree: pointer passed is NULL\n") ;
		return NULL ;
	}
/* Returning when size passed as argument is 0 */
	if( n == 0){
		fprintf(stderr,"bfree: size of passed array is 0 \n") ;
		return NULL ;
	}

/* To create header block pointing at *p passed as argument */
	Header *insertp = (Header *)p ;
	unsigned nunits = ( n - 1 + sizeof(Header *) ) / sizeof( Header *) + 1;
	insertp->s.size = nunits ;

/* To position the memory block in the free list */
	/* To check if list is uninitialised or not */
	if( freep == NULL ){						/* To create a degenerate list */
		freep = &base ;
		freep->s.size = 0 ;
		freep->s.next = insertp ;				
		insertp->s.next = freep ;				/* Since the block created is a circular linked list */
		freep = insertp ;		
	} else {
	/* Puts the memory block back into the free list and reinitialises the freep pointer */
		Kandr_free(insertp) ;
	}
return NULL;
}


/* Puts insertp in freelist */
void Kandr_free( Header *insertp )
{
    Header *currp ;
/* Checking if valid memory block is being freed */
    if( (insertp->s.size == 0) || (insertp->s.size > maxalloc) ){
        fprintf(stderr,"Kandr_free :Invalid memory block passed\n") ;
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
