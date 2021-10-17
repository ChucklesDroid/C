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
