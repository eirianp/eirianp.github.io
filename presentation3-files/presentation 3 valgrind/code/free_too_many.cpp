#include <cstdlib>

int main(){
	int * foo;
	foo = (int *)malloc(10*sizeof(int));
	free(foo);
	free(foo);
	return 0;
}
