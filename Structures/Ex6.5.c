#include <stdio.h>
#include "hashtables.c"
#include<string.h>


void undef( char *name ) 
{
	struct linkedlist *np = NULL , *prev = NULL;
	unsigned hashval = hash(name) ;
	
	for( np = hashtab[hashval] ; np != NULL ; np = np->next ){
		if( strcmp( name , np->name ) == 0 )
			break ;
		prev = np ;
	} if( prev != NULL)
		prev->next = np->next ;
	else
		hashtab[hashval] = np->next ;
	
	free( (void *)name ) ;
	free( (void *)defn ) ;
	free( (void *)np ) ;
}

