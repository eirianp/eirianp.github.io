#include <cstdlib>

int main(){
	int * foo;
	foo = (int *)malloc(10*sizeof(int));
	// notice we didn't free
	return 0;
}
