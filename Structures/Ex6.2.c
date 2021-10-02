#include<stdio.h>
#include<ctype.h>
#define WORDMAX 100
#define YES 1 
#define NO 0
struct tnode{
	char *word ;
	int conf ;
	struct tnode *left ;
	struct tnode *right ;
} ;
struct tnode *
talloc() ;
char *strdup(char *w) ;
void printtree( struct tnode *p ) ;
int compare( struct tnode *p , char *t , int num ) ;
int addtree( struct tnode *p , char *w , int num ) ;
int getword( struct tnode *p , char *w ) ;
void comments( void ) ;
int getch( void ) ;
void ungetch( int c ) ;
int main(void)
{
	char word[WORDMAX] ;
	int ch , num :
	struct tnode *root ;
	num =(--argc > 0 && **(++argv) == "-") ? atoi(++(*argv)) : 6 ;
	root = NULL ;
	while( (ch=getword(root,word)) != EOF && ch != "\n")
		if( isaplha(word[0]) )
			root = addtree( root , word , num) ;
	printtree(root) ;
}

int addtree( struct tnode *root , char *w , int num ) 
{
	int cond ;
	if( root == NULL ){
		root = talloc() ;	
		root->word = strdup(w) ;
		root->conf = NO ;
		root->left = root->right = NULL ;
	} else if( (cond = compare( root , w , num )) == NULL ) {
		root->conf = YES ;
	} else if( cond > 0 )
		root->left = addtree( root->left , w , num ) ; 
	else
		root->right = addtree( root->rigt , w , num ) ;
}

void printtree( struct tnode *root )
{
	printtree( root->left) ;
	if( root != NULL && root->conf == YES)
		printf("%s\n" , root->word ) ;
	printtree( root->right ) ;
}

int compare( struct tnode *p , char *w , int num )
{
	char *s = p->word ;
	for(int i = 1 ; *s == *t ; s++ , t++, i++ ) 
		if( i == num ){
			p->conf = YES ;
			return 0 ;
		}	
	return (*s - *t) ;
}


int getword ( struct tnode *p , int limit )
{
	char *w = p->word ;
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

char *strdup( char *w )
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
	return (struct tnode)malloc(sizeof(struct tnode)) ;
}