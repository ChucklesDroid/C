#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
#define NKEYS (sizeof(keytab) / sizeof(keytab[0]) )
enum { NUM = 1 } ;
struct key {
    char *word;
    int count;
} keytab[] = {
    {"auto", 0},
    {"break", 0},
    {"case", 0},
    {"char", 0},
    {"const", 0},
    {"continue", 0},
    {"default", 0},
    {"do", 0},
    {"double", 0},
    {"else", 0},
    {"enum", 0},
    {"extern", 0},
    {"float", 0},
    {"for", 0},
    {"goto", 0},
    {"if", 0},
    {"int", 0},
    {"long", 0},
    {"register", 0},
    {"return", 0},
    {"short", 0},
    {"signed", 0},
    {"sizeof", 0},
    {"static", 0},
    {"struct", 0},
    {"switch", 0},
    {"typedef", 0},
    {"union", 0},
    {"unsigned", 0},
    {"void", 0},
    {"volatile", 0},
    {"while", 0}
};

int getword(char *, int);
int binsearch(char *, struct key *, int);
void comments(void) ; // For managing comments
/* count C keywords */
int main() {
    int n;
    char word[MAXWORD] , ch ;

    while ((ch = getword(word, MAXWORD)) !='\n' && ch != EOF ) {
    	if (isalpha(word[0]))
        	    if ((n = binsearch(word, keytab, NKEYS)) >= 0)
                	keytab[n].count++;
    }

    for (n = 0; n < NKEYS; n++)
        if (keytab[n].count > 0)
            printf("%4d %s\n",keytab[n].count, keytab[n].word);

    return 0;
}

/* binsearch: find word in tab[0]...tab[n-1] */
int binsearch(char *word, struct key tab[], int n) {
    int cond;
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low+high) / 2;
        if ((cond = strcmp(word, tab[mid].word)) < 0)
            high = mid - 1;
        else if (cond > 0)
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}

int getch(void);
void ungetch(int);

#define BUFSIZE 100

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */

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

int getword ( char *w , int limit )
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
