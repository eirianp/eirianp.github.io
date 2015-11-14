// invalid read and invalid write

#include <iostream>
#include <cstdlib>

int main(){

	int * foo;
	foo = (int *)malloc(10*sizeof(int));
	foo[13] += 1;
	free(foo);
	return 0;
}
