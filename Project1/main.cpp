#include <iostream>
#include "PoolAllocator.h"

class Foo {
public:
	int test = 12;
	int test2 = 13;
	int t4 = 5;
	int t5 = 2;
	int t6 = 1;
};

int main() {
	CREATE(f, 25, 1);
	void* v1 = f.Allocate(15);
	f.printPool();
	void* v2 = f.Allocate(5);
	f.printPool();
	f.Deallocate(v1);
	f.printPool();
	v1 = f.Allocate(21);
	f.printPool();
	f.Deallocate(v2);
	f.printPool();
	f.Deallocate(v1);
	f.printPool();
	Foo* foo = new(f.Allocate(sizeof(Foo))) Foo;
	f.printPool();
	std::getchar();
}
