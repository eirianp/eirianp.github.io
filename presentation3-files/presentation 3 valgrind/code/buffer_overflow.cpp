// run valgrind with --tool=exp-sgcheck
#include <iostream>

int main(){
	int foo[3];
	for (int i = 0; i < 6; i++){
		foo[i] = i;
	}
	return 0;
}
