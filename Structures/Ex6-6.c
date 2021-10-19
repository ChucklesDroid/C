#include<stdio.h>
#define WORDMAX 1000
#define TABLESIZE 10
#define BUFSIZE 100
// directive , literal , strings , comments , backslash
struct hashtables{
	char *key ;
	char *value ;
	struct hashtables *next ;
};

unsigned line_start = 1 ; // 1 indicates start of the line and 0 indicates
char buf[BUFSIZE]; 
int bufp = 0; 
int getch(void) ;
void ungetch(int ) ;
unsigned directive = 0 ;
unsigned keyval = 0; 
unsigned val = 0;
char *key , *value;
struct hashtables *tab[TABLESIZE] ;
int getword( char *) ;
void lookup( struct hastables ** , char *) ;
void install( struct hashtables ** , char *) ;
unsigned hash( char * ) ;
int main( int argc , char *argv[] )
{
	struct hashtables tab[TABLESIZE] = NULL ;
	char word[WORDMAX] ;
	while( getword(word) != EOF ){
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
	while( isspace(ch = getch()) ) ;	
	
	// Parsing preprocessor directive 
	if( ch == '#' && line_start == 1){
		*w = ch ;
		while( isalpha( *w++ = ch = getch() ) ) ;
		ungetch(ch) ;
		directive = ( strcmp(word , "#define" ) == 0 )? 1 : 0 ;
		if( directive == 1 ) {
			while( isspace( ch = getch() ) 
				if( ch == '\n')
					return '\n' ;
			ungetch(ch) ;
			while(isalpha( ch = *k++ = getch() ) || ch == '_') ; 
			if( isalpha(key[0]) ){
				keyval = 1;
				while( isspace( ch =getch() )
					if( ch == '\n')
						return '\n' ;
				ungetch(ch) ;
				while( isalpha(ch = *v++ = getch()) ) ;
				ungetch(ch) ;		
			}
			return '#' ;
		}
		else
			return *w ;
	}
	else if( isalnum(ch) ){
		while( isalpha(ch = *w++ = getch() ) ;			
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
	struct hashtables *t
	if( p[hash(w)]   
}

void printtable ( struct hashtables *tab[TABLESIZE] )
{
	int i ;
	for( i = 0 ; i < TABLESIZE ; i++ ){
		if( *tab[i] != NULL ){
			for( struct hashtables *np = tab[i] ; np != NULL ; np = np->next )
				printf("%s -> %s" , np->key , np->val ) ;
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

void lookup( char *w )
{

}
