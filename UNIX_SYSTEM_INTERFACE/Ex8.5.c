/*              Fsize Program           */
/* This program will print all the information contained in inode entry
   For info refer Listing_libraries.c */
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>               /* For stat,macros for modebit,opendir */
#include <stdlib.h>
#include <dirent.h>                 /* For opendir,readdir, */
#include <fcntl.h>
#define MAX_PATH 1024               /* Max length of path */

void dirwalk( char *name , void (*fn)( char *) ) ;
void fsize( char *name ) ;              
int main( int argc , char *argv[] )
{
    if( argc == 1 )
        fsize(".") ;
    else{
        while( --argc > 0 )
            fsize(*(++argv)) ;
    }
    return 0 ;
} 

/* fsize : prints all information about the file contained in the inode entry */
void fsize( char *name )
{
    struct stat stbuf ;
    if(stat(name,&stbuf) == -1){
        fprintf(stderr,"\n%s :file unable to open\n\tExiting fsize..",name) ;
        return ;
    }
    if( stbuf.st_mode & S_IFMT == S_IFDIR )
        dirwalk(name,fsize) ;
    printf("%s\t%ld\n",name,stbuf.st_size) ;
    printf("Number of HardLinks:%d\n",stbuf.st_nlink) ;
    printf("User Id : %d\n",stbuf.st_uid) ;
    printf("Group Id: %d\n",stbuf.st_gid) ;
    printf("Device Id: %d\n",stbuf.st_rdev) ;
    printf("Inode Number :%d\n\n",stbuf.st_ino) ;
}

/* dirwalk : opens the directory and recursively calls the function 
   fsize to print information about the file */
void dirwalk( char *name , void (*fn)( char * ) )
{
    DIR *dp ;                       /* Directory pointer */
    struct dirent *fp ;             /* File pointer */
    char pathname[MAX_PATH] ;       /* Pathname when file is encountered in given directory*/
    if( (dp=opendir(name)) == NULL ){
        fprintf(stderr,"%s : file could not be opened !!..",name) ;
        return ;
    }
    while( (fp=readdir(dp)) != NULL ){
/*Skips the rest of code when it encounters the parent directory or itself .*/
        if( strcmp(fp->d_name,".") == 0 || strcmp(fp->d_name,"..") == 0 )
            continue ;              
        if( fp->d_type != DT_DIR ){
            sprintf(pathname,"%s/%s",name,fp->d_name) ;
            (*fn)(pathname) ;
        }
        else
            dirwalk(name,fn) ;
    }
    closedir(dp) ;
}