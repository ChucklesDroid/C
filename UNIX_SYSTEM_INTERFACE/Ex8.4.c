#include "stdio_excerpt.h"

/* 1st Attempt */
// int fseek( FILE *fp , long offset , int origin ){
//     int rc = 0 ; /* Return character */
//     if( fp->flag & (_WRITE | _ERR | _EOF ) != _WRITE )
//         return -1 ;
//     rc=lseek(fp->fd,offset,origin) ;
//     return rc ;
// }
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

int fseek ( FILE *stream , long offset , int whence)
{
    /* Checking for legitimate file stream */
    if( stream < _iob || stream > _iob+OPEN_MAX)
        return EOF ;
    /* Checking for errors in the file stream */
    if( stream->flag & (_ERR | _UNBUF | _EOF ) != 0 )
        return EOF ;
    if( stream->flag & _WRITE ){
        /* flushes the data stored in the stream opened for writing */
        fflush(stream) ;
        return 0 ;
    } else if( stream->flag & _READ ){
        /*
            when passed stream is in read mode : (i) if offset < stream->count then
            stream->ptr and stream->count is set accordingly
            (ii) if offset > stream->count then offset = offset - stream->count and
            stream->ptr = stream->base
        */
        if( whence == SEEK_CUR ){
            if(offset >= 0 && offset <= stream->count){
            /* shortcut when offset <= stream->count(space in the buffer) but >= 0 */
                stream->count -= offset ;
                stream->ptr += offset ;
                stream->flag &= ~_EOF ;
                return 0 ;
            } else
            /* */
                offset -= stream->count ;
        }
        stream->count = 0 ;
        stream->ptr = stream->base ;
        /*
            flushing the buffer of input stream
        */
    }
    int result = (lseek(stream->fd,offset,whence) < 0) ;
    if( result == 0 )
        stream->flag &= ~_EOF ;
    return result ;
}