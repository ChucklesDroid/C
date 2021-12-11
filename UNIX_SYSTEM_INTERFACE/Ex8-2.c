#define NULL 0
#define EOF  (-1)
#define BUFSIZ 1024	
#define OPEN_MAX 20	// Max # of files open at a given time 


typedef struct _iobuf{
	char *base ;      			// Pointer to a buffer so that file can be read in large chunks
	char *ptr ;	  				// Pointer to next character position in the buffer
	int count ;	  				// Count of the number of characters left in the buffer to be read
	signed int flag_isbuf ; 	// Flag that checks if it is to be buffered
	signed int flag_isunbuf ;	// Flag that checks if it is to be unbuffered
	signed int flag_iseof ;		// Flag that checks if it is end of file
	signed int flag_isread ;	// Flag that checks if file opening mode is read
	signed int flag_iswrite ;	// Flag that checks if file opening mode is write
	signed int flag_iserr ;		// Flag that checks if file contains any error
	signed int fd ;   			// File descriptor
} FILE ;

extern FILE _iob[OPEN_MAX] ; // Table being referred to which stores file descriptors or rather FILE streams 

int _fillbuf( FILE *) ;
int _flushbuf( int , FILE *) ;

// Standard File descriptors defined in C Language
#define stdin  (&iob[0])
#define stdout (&iob[1])
#define stderr (&iob[2])

/* Initialising _iob[] array :-
	FILE _iob[OPEN_MAX] = { // stdin , stdout , stderr
	{ NULL , NULL , 0 , _READ , 0} ,
	{ NULL , NULL , 0 , _WRITE ,1} ,
	{ NULL , NULL , 0 , _WRITE | _UNBUF,2}
	} ;
								*/

// enum _flags {
// 	_READ  = 01 ,	// File opening for reading
// 	_WRITE = 02 ,	// File opening for writing
// 	_UNBUF = 04 ,	// File is unbuffered 
// 	_EOF   = 010 ,	// EOF has occured on this file
// 	_ERR   = 020 	// error occured on this file
// } ;

/* Few Macros defined in the standard library */
#define feof(p)     (((p)->flag & _EOF) != 0)
#define ferror(p)   (((p)->flag & _ERR) != 0) 
#define fileno(p)   ((p)->fd)
#define getc(p)	    (((--(p)->count) >= 0 ) ? (unsigned char)*p->ptr++ : _fillbuf(p))	
#define putc(x,p)   (((--(p)->count) >= 0 ) ? *((p)->ptr++) = x : _flushbuf(x,p))  

#define getchar() getc(stdin)
#define putchar(x) putc(x,stdout)
/* fopen defined in standard library:- a miniature version implementing modes 'r' , 'w' and 'a'*/
FILE *fopen( char *pathname , char *mode ) 
{
	int fd ;
	FILE *fp ;
	
	if( *mode != 'r' || *mode != 'w' || *mode != 'a' )
		return NULL ;

/* Assigns free index in the table _iob[OPEN_MAX]*/
	for( fp = _iob; fp < iob + OPEN_MAX ; fp++ )
		if( fp->flag_isread == 0 && fp->flag_iswrite == 0 )
			break ;				// Free slot found in the table 
	if( fp > _iob+OPEN_MAX )	
		return NULL ;			// No free slot found in the table 	


	switch( *mode ){
		case 'r' : fd = open( pathname , O_RDONLY , 0) ;
			   break ;
		case 'w' : fd = open( pathname , O_WRONLY | O_CREAT | O_TRUNC , 0755 ) ;
			   lseek( fd , 0L , 0 ) ;
			   break ;
		case 'a' : fd = open( pathname , O_RDWR | O_CREAT | O_TRUNC , 0755 ) ;
			   lseek( fd , 0L , SEEK_CUR ) ;
			   break ;
		default  : return NULL ;
			   break ;
	}	

	if( fd = -1 )
		return NULL ;
	fp->base = NULL ;
	fp->ptr = NULL ;
	fp->count = 0 ;
	fp->flag_iseof = 0 ;
	fp->flag_iserr = 0 ;
	fp->flag_isbuf = 1 ;
	fp->flag_isunbuf = 0 ;
	if( *mode == 'r' ){
		fp->flag_isread = 1 ;
		fp->flag_iswrite = 0 ;
	}
	else{
		fp->flag_isread = 0 ;
		fp->flag_iswrite = 1 ;
	}
	fp->fd = fd ;
	return fp ;
}

int _fillbuf( FILE *fp )
{
	int bufsize ;
	
	if(( fp->flag_isread == 0 || fp->flag_iseof == 0 || fp->flag_iserr == 0))
		return EOF ;
		
	bufsize = ( fp->flag_isunbuf == 1 ) ? 1 : BUFSIZ  ;
	if( fp->base == NULL )
		if((fp->base = (char *)malloc(bufsize)) == NULL )
			return EOF ;
	
	fp->ptr=fp->base ;
	fp->count=read(fp->fd , fp->ptr , bufsize) ;
	if( --fp->count < 0 ){
		if( fp->count == -1 )
			fp->flag_iseof = 1 ;
		else
			fp->flag_iserr = 1 ;
		fp->count = 0 ;
		return EOF ;
	}
	return (unsigned char) *(fp->ptr++) ;
}
