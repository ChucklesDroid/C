#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#define MAXWORD 100
#define NMAX 1000
#define BUFSIZE 100
enum { NUM=1 } ;
struct tnode{
	char *word ;
	int count ;
	struct tnode *left ;
	struct tnode *right ;
} ;

char buf[BUFSIZE]; 
int bufp = 0; 
int ntnde = 0;
char *Strdup( char *W ) ;
struct tnode *
addtree( struct tnode * , char * ) ;
void printtree(struct tnode **) ;
void shellsort(struct tnode *, struct tnode **) ;
void ungetch(int ) ;
void comments(void) ;
int getword(char * ) ;
int getch(void) ;
void treestore(struct tnode * , struct tnode **) ;
int main( int argc , char *argv[] )
{
	struct tnode *root ;
	char word[MAXWORD];
	struct tnode *ptrlist[NMAX] ;
	while( getword(word) != EOF ){
		if( isalpha(word[0]) )
			root = addtree( root , word ) ;
	}
	treestore(root,ptrlist) ;
	shellsort(root, ptrlist);
	printtree(ptrlist) ;
	return 0 ;
}

struct tnode*
addtree( struct tnode *p , char *w ) 
{
	int cond ;
	if( p == NULL ){
		p = (struct tnode *)malloc( sizeof(struct tnode) ) ;
		p->word = Strdup(w) ;
		p->count = 1 ;
		p->left = NULL ;
		p->right = NULL ;
	} else if((cond = strcmp( p->word , w )) == 0 ) 
		p->count++ ;
	else if( cond < 0 )
		p->right = addtree( p->right , w ) ;
	else 
		p->left = addtree( p->left , w ) ;
}

void printtree( struct tnode **p )
{
	while( ntnde >= 0 ){
		printf("%d\t%s", (*p)->count , (*p)->word ) ;
		ntnde-- ;
		p++ ;
	}
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

void ungetch(int c) 
{ 
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

char *Strdup( char *w )
{
 	char *p = NULL ;
 	p = (char *)malloc(strlen(w) + 1) ;
 	if( p != NULL )
 		strcpy( p , w) ;
 	return p ;
}

void shellsort( struct tnode *p, struct tnode *Arr[])
{
	int gap , i , j ;
	for( gap = ntnde/2 ; gap >= 0 ; gap /= 2 )
		for( i = gap ; i < ntnde ; i++ )
			for ( j = i - gap ; j>0 && Arr[j] > Arr[j+gap] ; j -= gap ){
				struct tnode *temp = Arr[j] ;
				Arr[j] = Arr[j+gap] ;
				Arr[j+gap] = temp ;
			}	
}

void treestore( struct tnode *p , struct tnode *Arr[NMAX])
{
	if( p != NULL){
		treestore(p->left,Arr) ;
		if( ntnde<NMAX )
			Arr[ntnde++] = p ;
		treestore(p->right,Arr) ;
	}
}
