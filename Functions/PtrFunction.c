#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#define MAXLINES 100    
#define MAXLEN 1000
#define BUFFMAX 10000
#define NUM 1
#define REV 2
#define FOLD 4
#define DIR 8 

static char options = 0 ;   // To determine which flags are passed at command line by manipulating it at a bit level
char LineBuffer[ BUFFMAX ] ;// Stores Lines in this array rather using dynamic memory allocation
char *Line_ptr[ MAXLINES ] ;// Stores pointer to each line
int parsflags( int nlines ) ;
int numcmp( char *str1 , char *str2 ) ; 
int charcmp( char *str1 , char *str2 ) ; 
void Quicksort( int start , int end , int (*comp)( char *, char *) ) ;
int Partition( int start , int end , int (*comp)(char *, char *) ) ;
void Swap( char **str1 , char **str2 ) ;
int Readlines( void ) ; 
int Getline( char *line ) ; 
void Writelines( int nlines , int rev ) ;
int main( int argc , char *argv[] )
{
    char chce ;
    while(--argc && *(*(++argv)) == '-' ) // Both while loops ( Lines 26 and LIne 27 ) checks for
        while( chce = *(++(*argv)) )      // flags passed at command line 
            switch( chce )
            {
                case 'n' : options |= NUM ;// For parsing numeric values
                            break ;
                case 'r' : options |= REV ;// For displaying elements in the decreasing order by default displays in inc order
                            break ;
                case 'f' : options |= FOLD ;// For making comparision between lower and upppercase redundant
                            break ;
                case 'd' : options |= DIR ; // For making comparision on letters ,nos and blanks
                            break ;
                default  : printf("\n Invalid Flag -%c Passed!!!", chce ) ;
            }
    Writelines( parsflags(Readlines()) , options & REV );
    return 0 ;
}

// Calls sorting function depending on the flags passed ( command line arguments )
// accepts no of lines as argument
// returns value depending upon if lines are read or not
int parsflags( int nlines )
{
    if( nlines > 0 ) {
        if( options & NUM )
            Quicksort( 0 , nlines - 1, (int (*)( char *, char *))numcmp ) ;
        else if( (options & FOLD) || (options & DIR) )
            Quicksort( 0 , nlines - 1, (int (*)(char * , char *))charcmp ) ;
        else 
            Quicksort( 0 , nlines - 1, (int (*)( char * , char *))strcmp ) ;
        return nlines ;
    }
    else{
        printf("\nError - No Line stored !!!") ;
        return -1 ;
    }        
}

// Reads total line pointer by  into array Line_ptr[] 
// return no of lines read and stored in memory
int Readlines( void )
{
    int nlines = 0 ;
    int len ;
    char Line[MAXLEN] ;
    char *p = LineBuffer ;
    while( len = Getline( Line )  && p != NULL ){
        strcpy( p , Line ) ;
        Line_ptr[ nlines++ ] = p ;
        p += len ;
    }
    return nlines ;
}

// Stores the concurrent line by collecting the userinput from stdin 
// takes the array line[] passed from and defined in Readlines() as argument 
// returns the length of the line[]
int Getline( char *line )
{
    int i = -1 ;
    char c ;
    while( c = getchar() != '\n' && i < MAXLEN )
        line[++i] = c ;
    line[++i] = '\0' ;
    return i ;
}

// For sorting Lines Lexicographically stored in Line_ptr
// takes start and end indices as first two arguments
//      pointer to function which depends on the flags parsed in parsflags() is 3rd argument
void Quicksort( int start , int end , int (*comp)( char *, char *) )
{
    if( start >= end )
        return ;
    else{
        int Pindex = Partition( start , end , comp ) ;
        Quicksort( start , Pindex - 1 , comp ) ;
        Quicksort( Pindex + 1 , end , comp ) ;
    }
}

// Partitions the given array around the pivot element
// takes start and end indices as first two argument 
//      pointer to function which depends on the flags parsed in parsflags() is 3rd argument
// returns Pivot index 
int Partition( int start , int end , int (*comp)(char *, char *) )
{
    int Pindex = 0 ;
    char *Pivot = Line_ptr[end] ; // Pivot is taken as the end index element of the array
    for( int i = start ; i < end ; i++ )
        if( comp( Pivot , Line_ptr[i] ) <  0){
            Swap( &Line_ptr[Pindex] , &Line_ptr[i] ) ;
            Pindex++ ;
        }
    return Pindex ;
}

// Swaps the values present at the two indices in Line_ptr
// takes address of both indices to be swapped as arguments
void Swap( char **str1 , char **str2 )
{
    char *temp = NULL ;
    temp = *str1 ;
    *str1 = *str2 ;
    *str1 = temp ;
}

// For numerical comparison 
// returns difference between numbers
int numcmp( char *str1 , char *str2 )
{
    int v1 = atoi( str1 ) ;
    int v2 = atoi( str2 ) ;
    if( v1 == v2 )
        return 0 ;
    else
        return v1 - v2 ;
}

// Flags -f and -d will be checked simultaneously
// takes address of strings to be compared as arguments
// returns difference between ascii values of characters
int charcmp( char *str1, char *str2 )
{
    int fold = options & FOLD ;
    int dirord = options & DIR ;
    int val ;
    for(; *str1 != '\0' && *str2 !='\0' ; str1++ , str2++ ){
        if( dirord ){
            while( !isalpha(str1) && *str1 != ' ')
                str1++ ;
            while( !isalpha(str2) && *str2 != ' ')
                str2++ ;
        }
        if( fold ){
            if( ( tolower(*str1) - tolower(*str2)) == 0 && *str1 != '\0' )
                return 0 ;
            if( ( tolower(*str1) - tolower(*str2)) == 0 )
                continue ;
            if( val = ( tolower(*str1) - tolower(*str2)) != 0 )
                return val ;
        }
        else{
            if( strcmp(str1 , str2) == 0 && *str1 != '\0' )
                return 0 ;
            if( strcmp(str1 , str2) == 0 )
                continue ;
            if( ( val = strcmp(str1 , str2)) != 0 )
                return val ;
        }
    }
}

// Displays all the lines read from stdinput
// takes no of lines (nlines) and flag to determine the order of display of lines as input 
void Writelines( int nlines , int rev )
{
    int start = 0, end = nlines - 1 ;
    if(rev){
        start = nlines - 1;
        end = 0 ;
    }
    for( int i = start , j = 1 ; i <= end ; i++ , j++)
        printf("%d %s\n", j , Line_ptr[i] ) ;
}   