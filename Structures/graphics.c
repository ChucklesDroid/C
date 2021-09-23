/*
 	This Program basically tracks all the functions introduced in the book to explain passing Structures.
 */
#include <stdio.h>

// point :stores coordinates of a point i.e x and y.
struct point{
	int x; 
	int y;
} ;

// rectangle : stores two diagonal points of a rectangle.
struct rectangle{
	struct point pt1 ;
	struct point pt2 ;
} ;

// makepoint : function takes two integer coordinates as arguments and returns point structure.
struct point makepoint( int x, int y)
{
	struct point temp ;
	temp.x = x ;
	temp.y = y ;
	return temp ;
}

// addpoint : function takes structure arguments and returns structure. By incrementing the contents of one parameter rather than creating a new temporary instance emphasise that structure parameters are passed by value .
struct point addpoint( struct point p1 , struct point p2 )
{
	p1.x += p2.x ;
	p1.y += p2.y ;
	return p1 ;
}

// ptinrect : Checks if the given point falls inside the rectangle or not and returns true or false
int ptinrect( struct point p , struct rectangle r)
{
	return(( ( p.x >= r.pt1.x ) && ( p.x <= r.pt2.x ) )&&( ( p.y >= r.pt1.y ) && (p.y <= r.pt2.y) ) ) ; //Assumed rectangle in canonical form and pt1 coordinates are less than pt2
}
int main( int argc , char *argv[] )
{
	struct point pt ;
	return 0 ;
}
