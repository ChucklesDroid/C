#include<stdio.h> #include<string.h>
#include<stdio.h>

struct tnode {
	char *word ;
	int count ;
	struct tnode *left ;
	struct tnode *right ;
} ;
struct tnode *
addtree( struct tnode *root , char *word ) ;
printtree( struct tnode *root ) ;
int getword(
int main( int argc ,char *argv[] )
{ 
	int ch ;
	char *word ;
	struct tnode *root ;
	root = NULL ;
	if( (ch=getword(word , WORDMAX)) != EOF )
		if( isalpha(word[0]) )
			root = addtree(root , word) ;
	printtree( root, tree) ;
	return 0 ; 
}

struct tnode *
addtree( struct tnode *p , char *w )
{
	int cond ;
	if ( p == NULL )
	{
		p = talloc() ;
		p->word = strdup(w) ;
		p->count = 1 ;
		p->left = p->right = NULL ;
	}
	else if( (cond = strcmp( w , p->word ) ) == 0 )
		p->count++ ;
	else if( cond < 0 )
		p->left = addtree(p->left,w) ;
	else
		p->right = addtree(p->right ,w) ;
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

void printtree( struct tnode *p)
{
	printtree( p->left ) ;
	if( p != NULL )
		printf("%4d\n" , p->word ) ;
	printtree( p->right ) ;
}