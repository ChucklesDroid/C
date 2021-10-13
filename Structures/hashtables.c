#include<stdio.h>
#define HASHSIZE 10

struct linkedlist {
	char *name ;
	char *defn ;
	struct linkedlist *next ;
}hashtab[HASHSIZE] ;

unsigned hash( char *s )
{
	unsigned hashval ;
	for( hashval = 0 ; *s != NULL ; s++ ) 
		hashval = *s + 31 * hashval ;
	return hashval ;
}

struct linkedlist *
lookup( char *s )
{
	struct linkedlist *np ;
	for( np = hashtab[hash(s)] ; np != NULL ; np = np->next ) 
		if( strcmp(s , np->next ) == 0 )
			return np ;
	return NULL ;
}

struct linkedlist *
install( char *name , char *defn ) 
{
	unsigned hashval ;
	struct linkedlist *np ;
	if((np = lookup(name)) == NULL){
		np = ( struct linkedlist *)malloc( sizeof(struct linkedlist)) ;
		if(np == NULL || (np->name=Strdup(name)) == NULL )
			return NULL ;
		hashval = hash(name) ;
		np->next = hashtab[hashval] ;
		hashtab[hashval] = np->next ;
	} else
		free( (void *)np->defn ) ;
	if( (np->defn = Strdup(defn)) == NULL )
		return NULL ;
	return np ;
}

char *Strdup( char *s )
{
	char *str = NULL ;	
	str = (char *)malloc(strlen(s)+1) ;
	if( str != NULL )
		strcpy( str , s ) ;
	return str ; 
}
