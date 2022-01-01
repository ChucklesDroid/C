/*      File Structure in UNIX File System      */

/*  A directory in UNIX filesystem consists of 2 parts :- 
    (i) Filename (ii) Inode Number
    The inode for a file is where all information about a file except its name is 
    kept , A directory entry(Dirent) generally consists of only two items , filename and 
    inode number .
    Regrettably the format and precise contents of a directory(DIR) are not the same on
    all versions of the system . So we will divide task into 2 pieces to try to 
    isolate two pieces to try isolate non portable parts
*/

typedef struct{                 /* Portable Directory Entry */
    short inode_no ;            /* Inode No in the inode list */
    char name[NAME_MAX] ;       /* Name of the file stored in the system */
} Dirent ;

typedef struct{
    ssize_t fd ;                /* File descriptor of the file */
    Dirent d ;                  /* DIrectory Entry */
}  DIR ;

DIR *opendir( char *dirname ) ; /*to open directory */
Dirent *readdir( DIR *dfd ) ;   /*to read directory */
void closedir( DIR *dfd ) ;     /*to close directory */    

#define NAME_MAX 14             /* Minimum Length of a File is NAME_MAX */

/* The system call stat takes a filename and takes all the information in the inode
   for that file , or -1 if there is an error , It is defined in sys/stat.h */

#include <sys/stat.h>
char *name[NAME_MAX] ;
struct stat stbuf ;             /* Defined in sys/stat.h */
int stat( char *, struct stat *); /* Function Prototype of stat */


/* Typical definition of struct stat looks like this :-

struct stat {
    dev_t   st_dev;             //Device of inode
    ino_t   st_ino;             //Inode Number
    short   st_mode;            //Mode Bits
    short   st_nlink;           //Number of Links to a file
    short   st_uid;             //Owner's user id
    short   st_gid;             //Owner's group id
    dev_t   st_rdev;            //For special fIle
    off_t   st_size;            //File size in characters
    time_t  st_atime;           //TIme last accessed
    time_t st_mtime;            //Time last modified
    time_t st_ctime;            //Time inode last changed
}

For actual definition refer to linux manual :- man 2 stat
*/

/* An example of set of mode bits :-
 S_IFMT 0160000                // Type of file : 
 S_IFDIR                       // directory
 S_IFCHR                       // character special
 S_IFBLK                       // block special
 S_IFREG                       // regular
 
 For actual definition refer to linux manual :- man 7 inode
 */ 

/* fsize will print the size of files and print to screen */
/* main function will call fsize depending upon the value of argc */

int fsize(char *name) ;
int main( int argc , char *argv[] )
{
    if( argc == 1 )
        fsize(".") ;
    else
        while( --argc > 0 )
            fsize(++argv) ;
    return 0 ;
}

/* fsize : prints the size of the files in the contained directory and 
   if it encounters a directory it calls dirwalk() to deal with it. */

void fsize( char *name )
{
    struct stat statbuf ;
    if( stat(name,statbuf) == -1 ){
        fprintf(stderr,"\t\tfsize:Error encountered while retrieving info \n...Make sure that directory has execute permissions") ;
        return ;
    }
/* since st_mode a mode bit , bit operations are used to check its value */
    if( statbuf.st_mode & S_IFMT == S_IFDIR ) 
        dirwalk(name,fsize) ;
    printf("%s\t%8ld\n",name,statbuf.st_size) ;
}

/* dirwalk : prints the files stored in the directory and calls fsize recursively
   for it. */
#define PATH 1024

void dirwalk( char *name , void (*fn)(char *) )
{
    DIR dp ;
    Dirent df ;
    char local_name[PATH] ;
    if( (dp=opendir(name)) == NULL ){
        fprintf(stderr,"%s :file unable to open",name) ;
        return ;
    }
    while( (df=readdir(dp)) != NULL ){
        if( strcmp(df.name,".") == 0 || strcmp(df.name,".") == 0 )
            continue ;
        if( strlen(name)+strlen(df.name)+1 > NAME){
            fprintf(stderr,"%s/%s : path to long ..exiting") ;
            return ;
        }
        sprintf(local_name,"%s/%s",name,df.name) ;
        (*fn)(local_name); 
    }
    closedir(df) ;
}

/*  Local definition of Direct */
/*  Non portable */
/*  opendir(DIR *) , readdir(Dirent *), closedir(DIR *) are not portable and will 
    vary from file system to system */

typedef struct {
    int d_inode ;              /* inode number */
    char d_name[NAME_MAX] ;    /* Name of FIle */
} direct ;                     /* Directory Entry */

/* opendir : opens passed argument , checks if its a directory , allocates storage
   to directory pointer and returns pointer to directory*/
DIR *opendir(char *name) 
{
    DIR *dp ;                  /* Directory pointer */
    int fd ;                   /* File Descriptor */
    struct stat statbuf ;      /* Stat buffer */
    if((fd=open(name,O_RDONLY,0)) == -1 || fstat(fd,&statbuf) == -1
     || statbuf.st_mode & S_IFMT != S_IFDIR 
     || (dp=(char *)malloc(sizeof(DIR))) == NULL){
        fprintf(stderr,"%s : unable to open file",name) ;
        return NULL ;
    }
    dp->fd = fd ;
    return dp ;
}

/*  readdir : reads files from the given directory and returns pointer to 
    file(Dirent)   */
Dirent readdir( DIR *dp )
{
    direct *fp ;               /* Local Implementation of directory entry */
    Dirent *Dfp ;              /* Portable Implementation of Directory entry */
/* Loop since it can be a free slot depending on inode no */
    while( read(dp->fd,fp,sizeof(direct)) != sizeof(direct) ){ 
        if( fp->d_inode == 0 ) /* Free Slot */
            continue ;
/* Copies information from local implementation to portable implementation  */
        Dfp->inode_no = fp->d_inode ;   
        strcpy(Dfp->name,fp->d_name) ;  
        return Dfp ;
    }
    fprintf(stderr," unable to open file .") ;
    return NULL ;
}

/*  closedir : closes the open directory and frees space */
void closedir(DIR *dfp)
{
    if(dfp)
      close(dfp) ;             /* It free the file descriptor */
    free(dfp) ;                /* It frees the memory allocated to directory pointer */
}