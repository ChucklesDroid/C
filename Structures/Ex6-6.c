#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#define WORDMAX 1000
#define TABLESIZE 10
#define BUFSIZE 100

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
void install( struct hashtables **) ;
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
			install(tab) ;
	}
	printtable(tab) ;
	return 0 ;
}

// passes macro and its replacment text from the input text
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
			//ungetch(ch) ;
			*k = ch ;
			while(isalpha( ch = *++k = getch() ) || ch == '_') ; 
			*k = '\0' ;
			ungetch(ch) ;
			if( isalpha(key[0]) || key[0] == '_'){
				keyval = 1;
				while( isspace( ch =getch() ) )
					if( ch == '\n')
						return '\n' ;
				//ungetch(ch) ;
				*v = ch ;
				while( isalnum(ch = *++v = getch()) ) ;
				*v = '\0' ;
				ungetch(ch) ;		
				val = 1;
			}
		}
			return ch ;
		// else
		// 	return *w ;
	} else if( isalnum(ch) ){ //entire word is parsed is returned
			while( isalpha(ch = *w++ = getch()) ) ;			
			*(--w) = '\0' ;
			ungetch(ch) ;
			return word[0] ;	
	} else	// anything other than alphanumeric or #define is encountered is also returned back
		return ch ;
}

// Parses and returns value from the buffer
int getch(void) 
{ 
    return (bufp > 0) ? buf[--bufp] : getchar();
}

// Push the extra read value back to the buffer( here a seperate array is created for that purpose)
void ungetch(int c) 
{ 
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

// void install( struct hashtables *p[TABLESIZE] , char *w)
// {
//  	int i , j ;
// 	//char *k = key , *v = value ;
// 	unsigned hashval ;
// 	hashval = hash(w) ;
// //	struct hashtables *t
// 	if( p[hashval] == NULL ){
// 		struct hashtables *temp ;
// 		temp =(struct hashtables *)malloc( sizeof( struct hashtables ) ) ;
// 		temp->key = ( char *)malloc(sizeof(char *)) ;
// 		strcpy(temp->key, ::key) ;
// 		temp->value = (char *)malloc(sizeof(char *)) ;
// 		strcpy(temp->value,::value) ;
// 		temp->next = p[hashval] ;
// 		//p[hashval]->next = p[hashval] ;
// 	} else 
// 		install( p[hashval]->next , w) ;
// }

// Prints the macros along with its replacement text which is stored in the table
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

// Function which calculates hash value depending on the key parsed from input
unsigned hash( char *s )
{
	unsigned hashval = 0; 
	for( ; *s != '\0' ; s++ )
		hashval = *s + 31 * hashval ;
	return hashval % TABLESIZE ;
}

// Returns the address of the node at which key is found else returns NULL 
struct hashtables *
lookup( struct hashtables *tab[TABLESIZE] , char *w )
{
	struct hashtables *np ;
	for( np = tab[hash(w)] ; np != NULL ; np = np->next )
		if( strcmp(np->key,w) == 0 )
			return np ;
	return NULL ;
}

// Installs the marco along with its replacement text in the hashtable
void install( struct hashtables *tab[TABLESIZE])
{
	struct hashtables *np = NULL ;
	np = lookup( tab,key ) ;
	unsigned hashval = hash(key) ;

	if( np == NULL ){
		np = (struct hashtables *)malloc( sizeof(struct hashtables)) ;
		np->key = (char *)malloc( strlen(key) + 1) ;
		np->value = (char *)malloc( strlen(value) + 1) ;
		strcpy( np->key , key ) ;
		strcpy( np->value , value) ;
		np->next = tab[hashval] ;
		tab[hashval] = np ;
	} else
		strcpy( np->value , value ) ;
}