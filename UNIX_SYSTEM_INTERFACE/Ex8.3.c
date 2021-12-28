/* Flushing a buffer means writing data stored in temporary storage into permanent
   storage
   https://www.geeksforgeeks.org/buffer-flush-means-c/
*/

#include "stdio_excerpt.h"
#include <stddef.h> /* ptrdiff_t is defined in this header file */
#include <unistd.h> /* close,write is defined in unistd.h */


/* _flushbuff :- check for errors , flush the stream or if base is not initialised
( i.e first call is made then initialises the buffer ) */
int _flushbuff(int x , FILE *fp)
{
    /* no of characters to be flushed */
    ptrdiff_t nc ;
    size_t buffsize ;

    /* Invalid FIle open */
    if(fp < _iob || fp >= _iob+OPEN_MAX )
        return EOF ;
    /* If error present then returns it */
    if(fp->flag & (_EOF | _ERR | _WRITE) != _WRITE)
        return EOF ;
    /* Allocating buffer */
    buffsize = (fp->flag | _UNBUF) ? 1 : BUFSIZ ; 

    /* If buffer is not yet initialised */
    if(fp->base == NULL){
        if( (fp->base = (char*)malloc(BUFSIZ)) == NULL)
            return EOF ;
        fp->ptr = fp->base ;
        fp->count = buffsize ;
    }

    // if(--(fp)->cnt >= 0)
    //     fp->ptr++ = x; 
    // else{
    //     if(fp->count == -1)
    //         fp->flag != _EOF ;
    //     else
    //         fp->flag |= _ERR ;
    //     return EOF ;
    // }

    /* If buffer is already initialised */
    else{
        nc = fp->ptr-fp->base ;
        if( write(fp->fd,fp->base,nc) != nc ){
            fp->flag |= _ERR ;
            return EOF ;
        }
    } 

    fp->ptr = fp->base ;
    fp->count = buffsize - 1;
    *fp->ptr++ = (char)x ;
    return x ;
}

/* fflush : checks for errors , if output stream then flushes the data otherwise 
   discards the data 
    */
int fflush(FILE *stream)
{
    int rc = 0; /* Return Character */
    if( stream > _iob || stream > _iob+OPEN_MAX ){
        stream->flag |= _ERR ;
        return EOF ;
    }
    if( stream->flag & _WRITE )
        rc = _flushbuf(0,stream) ;
    stream->ptr = stream->base ;
    stream->count = (stream->flag & _UNBUF) ? 1 : BUFSIZ ;
    return rc ; 
}

/* fclose calls fflush to flush the data(write temporary data into permanent
   storage) and also free the memory occupied by the file stream (by closing it)
   */

int fclose(FILE *stream)
{
    int rc ; /* return character */
    if( (rc = fflush(stream)) != EOF ){
        free(stream->base) ;
        stream->base = NULL ;
        stream->ptr = NULL ;
        stream->flag = 0 ;
        stream->count = 0 ;
        close(stream->fd) ;
        stream->fd = -1 ;
    }
    return rc ;
}