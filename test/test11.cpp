/*
 * Sorts an array of C-strings.
 * Demonstrates how to write an ordering function 
 * that compares two C-strings.
 */

#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

int order_string(const void* e1, const void* e2);						// (a)

int main()
{
	char* string_data[] = { "see", "the", "quick", "red", "fox", "jump",			// (b)
		    "over", "the", "lazy", "brown", "dog" };
			
	qsort(string_data, 11, sizeof(char*), order_string);					// (c)

	for (int i = 0; i < 11; i++)								// (d)
		cout << string_data[i] << endl;

	char* key = "jump";									// (e)
	char** found = (char **)bsearch(&key, string_data, 11, sizeof(char*), order_string);	// (f)
	if (*found != nullptr)									// (g)
		cout << "key found: " << *found << endl;
	else
		cout << "key not found\n";

	return 0;
}


int order_string(const void* e1, const void* e2)						// (h)
{
	return strcmp(*(char **) e1, *(char **) e2);						// (i)
}