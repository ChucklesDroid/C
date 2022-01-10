#include <stdio.h>
#include <stdlib.h>

void *Calloc( size_t , size_t ) ;
// #include <unistd.h>
// #define NALLOC 1024             /* min size of block of data allocated by memcore */
// typedef unsigned Align ;

/*                      Malloc Library Function Implementation             */
// /* Memory block units , ALign is the most restrictive type */
// typedef union header{
//     struct{
//         union header *next ;
//         unsigned size ;
//     } mem_b ;
//     Align x ;
// } Header ;

// /* Local variants of the library functions */
// Header *Malloc( size_t ) ;
// Header *Calloc( size_t n_memb , size_t size ) ;
// Header *memcore( size_t ) ;
// void free( Header * ) ;

// /* Malloc variables */
// Header base ;                   /* Empty variable for free list */
// Header *freep ;                 /* First member of free list */

int main( int argc , char *argv[] )
{
    int *a ;
    a = (int *)Calloc(10,sizeof(int)) ;
    printf("Address = %p | Value at %d = %d| Address at %d = %p | Value at %d = %d ",a,0,*a,9,(a+9),9,*(a+9)) ;
    return 0;
}


/*                      Malloc Library Function Implementation             */
// /* Malloc : searches the freelist to return appropirate memory block */
// Header *Malloc( size_t nu )
// {
// /* units of memory blocks to be allocated */
//     size_t nunits = ( nu - 1 + sizeof( Header )) / sizeof( Header ) + 1 ; 

// /* Pointers created to traverse the free list */
//     Header *prevp = freep , *currp ;
    
// /* If free list does not exist then degenerate list is created */
//     if( freep == NULL ){
//         freep->mem_b.next = prevp = freep = &base ;
//         freep->mem_b.size = 0 ;
//     }

// /* Free list is traversed to find appropriate match */
//     for( currp = prevp->mem_b.next ; ; prevp = currp , currp = currp->mem_b.next ){

//     /* case : If big enough block is found */
//         if( currp->mem_b.size >= nunits ){
//             /* case : if exact match is found */
//             if( currp->mem_b.size == nunits ){
//                 prevp->mem_b.next = currp->mem_b.next ;
//             } else {
//             /* case : if larger memory block is found than the request then the 
//                memory block is split and tail is returned */
//                 currp->mem_b.size -= nunits ;
//                 currp += nunits ;
//                 currp->mem_b.size = nunits ;
//             }
//             /* freep is set to point at the previous memory block */
//             freep = prevp ;
//             return (currp + 1) ;
//         }

//     /* case : if no exact match exists then memcore is requested for more memory */
//         if( currp == freep ){
//             if( memcore(nunits) == NULL){
//                 return NULL ;
//             }
//         }
//     }
// }

// /* memcore : requests the operating system for more memory */
// Header *memcore( size_t nu )
// {
// /* Since calling the kernel to allocate data repeatedly is a slow process so at a
//    time NALLOC units of memory block is allocate */
//     if ( nu < NALLOC )
//         nu = NALLOC ;

// /* sbrk is a system function which calls on Operating system to allocate required 
//    memory units*/
//     Header * programbreak = sbrk( nu * sizeof(Header) ) ;
//     if( programbreak == (void *)-1 )
//         return NULL ;

// /*  Adding newly allocated memory block to freelist by calling free . Free causes 
//     freep to be repositioned to the newly allocated memory block */
//     free(programbreak) ;
//     return freep ;
// }

// void free( Header * memb )
// {

// /*  Traverses the freelist to find the exact position to insert the memory block 
//     case :- Exits the loop if exact position is right most or left most for memb */    
//     Header *currp ;
//     for( currp = freep ; ((currp > memb) && (memb < currp->mem_b.next)) ; currp = currp->mem_b.next ){
//         if( (currp >= currp->mem_b.next) && ((memb > currp) || (memb < currp->mem_b.next)) )
//             break ;
//     }        

// /* Block Insertion : If there is free block adjacent on either side then both 
//     blocks are coalesced into one */
//     /* case : right position of inserted block is checked */
//     if( memb + memb->mem_b.size == currp->mem_b.next ){
//         memb->mem_b.size += currp->mem_b.next->mem_b.size ;
//         memb->mem_b.next = currp->mem_b.next->mem_b.next ;
//     } else {
//         memb->mem_b.next = currp->mem_b.next->mem_b.next ;
//     }
    
//     /* case : left position of inserted block is checked */
//     if( currp + currp->mem_b.size == memb ){
//         currp->mem_b.size += memb->mem_b.size ;
//         currp->mem_b.next = memb->mem_b.next ;
//     } else {
//         currp->mem_b.next = memb ;
//     }

// }

/* Implementation of Library Functions Calloc */
void *Calloc( size_t n_memb , size_t size )
{
/* Checks for integer overflow for calculation of bytes to be 
   allocated(size*n_memb) */
    size_t bit_alloc = n_memb * size ;            /* Size to be allocated */
    if( size != bit_alloc/n_memb ){
        return NULL ;                             /* Error Occurs */
    }

/* Error Checking */
    if( n_memb == 0 || size == 0 ){
        return NULL ;                             /* Returns NULL */
    }    

/* Since we have to initialise each bit with 0 i.e we make use of pointer of type char* */
    char *trv_mem ;
    char *free_mem = malloc( bit_alloc ) ;
    trv_mem = free_mem ;
    
    while( trv_mem < free_mem+bit_alloc ){
        *trv_mem++ = 0 ;
    }
    
    return free_mem ;
}