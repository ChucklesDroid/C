#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define WORDMAX 100
#define BUFSIZE 100
#define YES 1 
#define NO 0

char buf[BUFSIZE]; 
int bufp = 0; 
enum { NUM = 1 } ;
struct tnode{
	char *word ;
	int conf ;
	struct tnode *left ;
	struct tnode *right ;
} ;
struct tnode *
talloc(void) ;
struct tnode *
addtree( struct tnode *p , char *w , int num , int *found ) ;
char *strrdup(char *w) ;
void printtree( struct tnode *p ) ;
int compare( struct tnode *p , char *t , int num , int *found ) ;
int getword( char *w ) ;
void comments( void ) ;
int getch( void ) ;
void ungetch( int c ) ;
int main( int argc , char *argv[])
{
	char word[WORDMAX] ;
	int ch , num ;
	int found = NO ;
	struct tnode *root ;
	num = (--argc > 0 && **(++argv) == '-') ? atoi(++(*argv)) : 6 ;
	root = NULL ;
	while( (ch=getword(word)) != EOF && ch != '\n')
		if( isalpha(word[0]) ){
			found = 0; 
			root = addtree( root , word , num , &found ) ;
		}
	printtree(root) ;
}

struct tnode *
addtree( struct tnode *p , char *w , int num , int *found ) 
{
	int cond ;
	if( p == NULL ){
		p = talloc() ;	
		p->word = strrdup(w) ;
		p->conf = *found ;
		p->left = p->right = NULL ;
		//return p ;
	}// else if( (cond = compare( p , w , num ,found)) == 0 ) {
	 //	p->conf = YES ;
	//}
	else if( (cond = compare( p , w , num ,found)) > 0 ){
		if(found)
			p->conf = YES ;
		p->right = addtree( p->right , w , num ,found) ; 
	} else if( cond < 0 ){
		if( found )
			p->conf = YES ;
		p->left = addtree( p->left , w , num ,found) ;
	} else 
		p->conf = YES ;
	return p ;
}

void printtree( struct tnode *p )
{
	if( p != NULL) {
	printtree( p->left) ;
	//if( p != NULL && p->conf == YES)
	if( p->conf )
		printf("%s\n" , p->word ) ;
	printtree( p->right ) ;
	}
}

int compare( struct tnode *p , char *t , int num , int *found )
{
	char *s = p->word ;
	int i ;
	for(i = 0 ; *s == *t ; s++ , t++, i++ ){
			if( *s == '\0')
				return 0 ;
		}	
		if( i >= num ){
			*found = YES ;
			p->conf = YES ;
		}
	return (*s - *t) ;
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
		*w = '\0' ;
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
	//else
	//	ungetch(c) ;
	//if( c == '*')
	//	getch() ;
	//else
	//	ungetch(c) ;
}

int getch(void) 
{ /* get a (possibly pushed back) character */
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) { /* push character back on input */
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

char *strrdup( char *w )
{
	char *p ;
	p = (char *)malloc( strlen(w) + 1) ;
	if(p)
		strcpy(p,w) ;
	return p ;
}

struct tnode *
talloc(void)
{
	return (struct tnode *)malloc(sizeof(struct tnode)) ;
}