#include<stdio.h>
#define WORDMAX 1000
#define TABLESIZE 10
// directive , literal , strings , comments , backslash
struct hashtables{
	char *key ;
	char *value ;
	struct linkedlist *next ;
};

unsigned directive = 0 ;
unsigned key = 0; 
unsigned value = 0;
char *key , *value;
struct hashtables tab[TABLESIZE] ;
int getword( char *) ;
void install( struct hashtables ** , ) ;
int main( int argc , char *argv[] )
{
	struct hashtables tab[TABLESIZE] ;
	char word[WORDMAX] ;
	while( getword(word) != EOF ){
		if( directive == 1 )
			install(tab,) ;
	}
	return 0 ;
}

int getword( char *word) 
{
	char *w = word , *k = key;
	char ch ;
	// Ignoring whitespaces
	while( isspace(ch = getch()) ) ;	
	
	// Parsing preprocessor directive 
	if( ch == '#' ){
		*w = ch ;
		while( isalpha( *w++ = ch = getch() ) ) ;
		directive = ( strcmp(word , "#define" ) == 0 )? 1 : 0 ;
		if( directive == 1 ) {
			while( isspace( ch = getch() ) ;
			while(isalpha( ch = *k++ = getch() ) || ch == '_') ;
			
		}
		else
			return word[0] ;
	}
}
