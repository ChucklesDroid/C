// 			Binary Search Algorithm
//	To understand the algorithm refer :https:-//www.youtube.com/watch?v=P3YID7liBug
//	only the first two to two and half mins to understand the algorithm and then refer to following examples to write the code
//	12 , 25 , 33  to find 20
// 	12 , 25 , 33 , 44 , 55 to find 25 


#include<stdio.h>

int BinarySearch( int , int Arr[] , int ) ;

int main( int argc , char *argv[] )
{
	int Arr[] = { 12 , 25 , 33 , 44 , 55 } ;	
	int val = BinarySearch( 25 , Arr , 5 ) ;
	printf(" \n value = %d ", val ) ;
	return 0 ;
}

int BinarySearch( int val , int Arr[5] , int n ) 
{
	int low = 0 , mid , high = n -1 ;

	while( low <= high ){
		mid = ( low + high ) / 2 ;
		if ( Arr[mid] == val )
			return mid ;
		else if ( Arr[mid] > val )
			high = mid - 1 ;
		else
			low = mid + 1 ;
	}

	return -1 ;
}
