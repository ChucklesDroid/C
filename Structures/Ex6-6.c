#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#define WORDMAX 1000
#define TABLESIZE 10
#define BUFSIZE 100
// directive , literal , strings , comments , backslash
struct hashtables{
	char *key ;
	char *value ;
	struct hashtables *next ;
};

unsigned line_start = 1 ; // 1 indicates start of the line and 0 indicates otherwise
char buf[BUFSIZE]; 
int bufp = 0; 
int getch(void) ;
void ungetch(int ) ;
unsigned directive = 0 ;
unsigned keyval = 0; 
unsigned val = 0;
char key[WORDMAX] , value[WORDMAX] ;
struct hashtables *tab[TABLESIZE] ;
struct hashtables *
lookup( struct hashtables ** , char *) ;
int getword( char *) ;
void printtable( struct hashtables **) ;
void install( struct hashtables **, char *) ;
unsigned hash( char * ) ;
int main( int argc , char *argv[] )
{
	struct hashtables *tab[TABLESIZE] = {NULL} ;
	char word[WORDMAX] , ch ;
	while( (ch = getword(word)) != EOF ){
		if( ch == '\n' )
			line_start = 1;
		else
			line_start = 0; 
		if( directive == 1 && keyval == 1 && val == 1)
			install(tab,word) ;
	}
	printtable(tab) ;
	return 0 ;
}

// passes macro and its replacment from the input text
int getword( char *word) 
{
	char *w = word , *k = key , *v = value ;
	char ch ;
	// Ignoring whitespaces
	while( isspace(ch = getch()) ) 
		if( ch == '\n')
			line_start = 1;	
	
	// Parsing preprocessor directive 
	if( ch == '#' && line_start == 1){
		*w = ch ;
		while( isalpha( *(++w) = ch = getch() ) ) ;
		*w = '\0' ;
		ungetch(ch) ;
		directive = ( strcmp(word , "#define" ) == 0 ) ? 1 : 0 ;
		if( directive == 1 ) {
			while( isspace(ch = getch()) )
				if( ch == '\n'){
					line_start = 1;
					return '\n' ;
				}
			ungetch(ch) ;
			while(isalpha( ch = *k++ = getch() ) || ch == '_') ; 
			*k = '\0' ;
			ungetch(ch) ;
			if( isalpha(key[0]) || key[0] == '_'){
				keyval = 1;
				while( isspace( ch =getch() ) )
					if( ch == '\n')
						return '\n' ;
				ungetch(ch) ;
				while( isalnum(ch = *v++ = getch()) ) ;
				*v = '\0' ;
				ungetch(ch) ;		
			}
			return '#' ;
		}
		else
			return *w ;
	}
	else if( isalnum(ch) ){
		while( isalpha(ch = *w++ = getch()) ) ;			
		return word[0] ;	
	}
	else
		return ch ;
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

void install( struct hashtables *p[TABLESIZE] , char *w)
{
 	int i , j ;
	char *k = key , *v = value ;
	unsigned hashval ;
	hashval = hash(w) ;
//	struct hashtables *t
	if( p[hashval] == NULL ){
		struct hashtables *temp ;
		p[hashval] =(struct hashtables *)malloc( sizeof( struct hashtables ) ) ;
		p[hashval]->key = ( char *)malloc(sizeof(char *)) ;
		strcpy(p[hashval]->key,k) ;
		p[hashval]->value = (char *)malloc(sizeof(char *)) ;
		strcpy(p[hashval]->value,v) ;
		temp = p[hashval]->next ;
		p[hashval]->next = p[hashval] ;
	}
		
}

void printtable ( struct hashtables *tab[TABLESIZE] )
{
	int i ;
	for( i = 0 ; i < TABLESIZE ; i++ ){
		if( tab[i] != NULL ){
			for( struct hashtables *np = tab[i] ; np != NULL ; np = np->next )
				printf("%s -> %s\n" , np->key , np->value ) ;
		}
	}
}

unsigned hash( char *s )
{
	unsigned hash = 0; 
	for( ; *s != '\0' ; s++ )
		hash = *s + 31 * hash ;
	return hash ;
}

struct hashtables *
lookup( struct hashtables *tab[TABLESIZE] , char *w )
{
	struct hashtables *np ;
	for( np = tab[hash(w)] ; np != NULL ; np = np->next )
		if( strcmp(np->key,w) == 0 )
			return np ;
	return NULL ;
}
