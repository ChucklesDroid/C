//                                              QUICKSORT ALGORITHM 
// Quicksort Algorithm makes use of recurrsion 
// Quicksort Algorithm consists of two functions :- 1) Quicksort(Arr , low , high ) and 2) Partition( Arr , low , high )
// Quicksort Function :- divides the Original array into two different arrays around Pivot index
// Partition Function :- is used to determine Pivot index and arrange unsorted array such that those elements that are smaller
//                       than pivot are relocated towards left of pivot and those greater than pivot are relocated towards right
//                       of pivot without actually sorting the array at that instant of time.
//Example :- Let the array be ( 7,2,1,6,8,5,3,4 )
//           Then for first Quicksort call from the main the array would be from 7 to 4
//           The first Partition call would find the pivot index of the pivot which by default is taken as the last element while
//           dividing the array around the pivot( 4 ) into two arrays one which has elements smaller than pivot ( 2,1,3 ) and the 
//           other array which will contain elements greater than pivot ( 8,5,7,6 ) and then recurrsion would occur 

//           base condition set would be that when "low >= high" it would return nothing Eg in ( 2,1,3 ) only
//           one array would be formed ( 2,1 ) around the pivot index because here the position of the pivot is towards the end
//           so following logic of Quicksort(Arr, PIVOTINDEX + 1 , high) for the right function would not be possible since 
//           "low > high" and also when array containing ( 2,1 ) would go through partition then while finding and arranging pivot 
//           position partitioned array would look like ( 1,2 ) where pivot would be 1 so one of the array calls would be 
//           Quicksort(Arr , PIVOTINDEX+1 , high) so here PIVOTINDEX+1 = high ie, low = high Therefore the equal sign in base case
//  VIDEO TUTORIAL :- https://www.youtube.com/watch?v=COk73cpQbFQ



#include<stdio.h>

void Quicksort( int Arr[] , int low , int high ) ;
void Swap (int Arr[] ,int pos1 , int pos2 ) ;
int Partition( int Arr[] , int low , int high ) ;
int main(int argc , char *argv[])
{
    int Arr[] = { 7,2,1,6,8,5,3,4 } ;
    Quicksort( Arr , 0 , 7 ) ;
    for(int i = 0; i < 8 ; i++)
        printf("%d " , Arr[i]) ;
    return 0 ;
}

void Quicksort( int Arr[] , int low , int high )
{   
    int Pivotindex = low ;
    if( low >= high )
        return ; 
    else {
    Pivotindex = Partition( Arr , low , high ) ;
    Quicksort( Arr , Pivotindex + 1 , high ) ;
    Quicksort( Arr , low , Pivotindex - 1 ) ;
    }
}

int Partition ( int Arr[] , int low , int high ) 
{
    int Pivot = Arr[ high ] ;
    int Pivotindex = low ;
    int i = low ;
    while( i < high)
    {
       if( Arr[i] < Pivot )
       {
           Swap ( Arr , Pivotindex , i ) ;
           Pivotindex++ ;
       }
       i++ ;
    }
    Swap( Arr , Pivotindex , high ) ;
    return Pivotindex ;
}

void Swap (int Arr[] ,int pos1 , int pos2 )
{
    int temp ;
    temp = Arr[ pos1 ] ;
    Arr[ pos1 ] = Arr[ pos2 ];
    Arr[ pos2 ] = temp ;
}