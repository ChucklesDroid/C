#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
#define WORDMAX 1000
#define BUFSIZE 100
enum { NUM = 1 } ;

struct linkedlist {
	int lnum ;
	struct linkedlist *ptr ;
} ;

struct tnode{
	char *word ;
	struct linkedlist *list ;
	struct tnode *left ;
	struct tnode *right ;
} ;

char buf[BUFSIZE]; 
int bufp = 0; 
struct tnode*
addtree( struct tnode * , int , char * ) ;
int getword( char * );
int noiseword( char * ) ;
int getch( void ) ;
char *Strdup( char *w ) ;
void comments( void ) ;
void ungetch( int c ) ;
void printtree( struct tnode * ) ;
void addline( struct tnode *p , int linenum ) ;
int main( int argc , char *argv[])
{
   struct tnode *root ;
   int linenum = 1;
   char word[WORDMAX] ;
   root = NULL ;
   while( getword(word) != EOF ){
   	if( isalpha(word[0]) && noiseword(word) == -1 )
		root = addtree( root , linenum , word ) ;
	if( word[0] == '\n' )
		linenum++ ;
   }
   printtree(root) ;
   return 0 ; 
}

int noiseword( char *w )
{
	int ch ;
	char *nw[] = { 
	    "a",
        "an",
        "and",
        "be",
        "but",
        "by",
        "he",
        "I",
        "is",
        "it",
        "of",
        "off",
        "on",
        "she",
        "so",
        "the",
        "they",
        "to",
        "you"
	} ;
	int low = 0;
	int high = sizeof(nw)/sizeof(char *) - 1; 
	int mid ;
	int cond ;
	while( low <= high ){
		mid = ( low + high ) / 2 ;
		if((ch = (strcmp(nw[mid] , w ))) == 0 ) 
			return mid ;
		else if ( ch < 0 ) 
			low = mid + 1; 	
		else 
			high = mid - 1;
	}
	return -1 ;
}

int getword ( char *w )
 {
         char c ;
         while( (c = *w = getch()) == ' ' && c == '\t' ) ;
 
         if ( isalpha(c) || c == '_' || c == '#' ) {
                 while( isalnum(c = getch()) || c == '_' )
                         *(++w) = c ;
                 ungetch(c) ;
         *(++w) = '\0' ;
                 return NUM ;
         } else if( c == '\'' || c =='"' ) {
                 while(( c = getch()) != '\'' && c != '"' && c != EOF )
                         *(++w) = c ;
                 //ungetch(c) ;
                 if( c == '\'' || c == '"')
             			*(++w) = c ;
                 *(++w) = '\0' ;
                 return '"' ;
         } else if( c == '/'){
                 //while( (c=getch()) != ' ') ;
                 comments() ;
                 *w = '\0' ;
                 return '/';
         } else {
                 *(++w) = '\0' ;
                 return c ;
         }
 }

void comments( void )
{
	char c ;
	if( (c=getch()) == '*' || c == '/' ){
		while( (c=getch()) != '*' && c != '\n' && c != EOF ) 
            if ( c == '*')
                if( c == '/')
                    break ;
                else 
                    ungetch(c) ;
	}
    if ( c == '\n' )
        ungetch(c) ;
}

int getch(void) 
{ 
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) { 
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

 struct tnode *
 addtree( struct tnode *p , int linenum , char *w )
 {
 	int cond ;
    	if( p == NULL ){
		p = (struct tnode *)malloc(sizeof(p)) ;
		p->word = Strdup(w) ;
		p->list = (struct linkedlist *)malloc(sizeof(struct linkedlist)) ;
		p->list->lnum = linenum ;
		p->list->ptr = NULL ;
		p->left = NULL ;
		p->right = NULL ;
	} else if((cond = strcmp( p->word ,w )) == 0 ){
		addline(p , linenum) ;	
	} else if( cond > 0 )
		p->left = addtree( p->left , linenum , w) ;
	else
		p->right = addtree( p->right , linenum , w ) ;
	return p ;
 }

 void addline( struct tnode *p , int linenum )
 {
	struct linkedlist *temp = p->list ;
	while( temp->ptr != NULL )
		temp = temp->ptr ;
	if( temp->lnum != linenum ) {
		temp=temp->ptr ;
		temp = (struct linkedlist *)malloc(sizeof(temp)) ;
		temp->lnum = linenum ;	
		temp->ptr = NULL ;
	}
  }
 
 char *Strdup( char *w )
 {
 	char *p = NULL ;
	p = (char *)malloc(strlen(w) + 1) ;
	if( p != NULL )
		strcpy( p , w) ;
	return p ;
 }

 void printtree( struct tnode *p)
 {
	if( p != NULL){
	printtree( p->right ) ;
		printf("\n%4s %d", p->word , p->list->lnum ) ;
		struct linkedlist *temp = p->list;
		while( temp != NULL ){
			printf(",%d", temp->lnum) ;
			temp = temp->ptr ;
		}
	printtree( p->left ) ;
	}
 }

