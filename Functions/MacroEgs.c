// Use of ## and # while writing macros 
// if macro definition of the outtermost macro has # and ## then innermost macro is not evaluated 
// if the outtermost macro doesn't have # or ## in its definition then first innermost macro definition is evaluated
// Link :- https://stackoverflow.com/questions/39317816/use-of-in-a-macro
          

#include <stdio.h>
#define dprintf(x) printf(#x "=%d", x) ;

int main(int argc , char *argv[])
{
    int x = 0 ;
    dprintf( x ) ;
    return 0 ;
}