#include <cstdlib>

int main(){
	int * foo;
	foo = (int *)malloc(10*sizeof(int));
	delete(foo);
	return 0;
}
