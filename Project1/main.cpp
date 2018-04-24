#include "OptParser.h"
#include "PreAllocString.h"
#include "Printf.h"
#include "7Segment.h"
#include <iostream>

void TestOptParser(int argc, char * argv[])
{
	CmdLineOptParser c;
	std::cout << c.Parse(argc, argv);
	std::getchar();
}

void TestPrintf() {
	char* testPtr;
	testPtr = new char[100];
	testPtr[99] = 0;
	const void* endPtr = &testPtr[99];
	const char* format;
	format = "%%_%d_%u_%x_%b";
	for (int i = -100; i < 101; i++) {
		Printf(testPtr, endPtr, format, i, i, i, i);
		std::cout << testPtr << std::endl;
	}
	Printf(testPtr, endPtr, "Das %s und das %c ein char.", "ist ein String", 'c');
	std::cout << testPtr << std::endl;
	std::cout << "Done" << std::endl;
	std::getchar();
}

void testPreAllocString() {
	CREATE(test, 1000);

	test = 'c';
	test.AddWhiteSpace();
	test += 'c';
	puts(test);
	test = "Das ist ein String";
	puts(test);
	test.Empty();
	puts(test);
	test += "01234567890";
	puts(test);
	printf("Size: %d Length: %d\n", static_cast<int>(test.SizeOf()), static_cast<int>(test.GetLength()));
	printf("CharAt 2: %c\n", test[2]);
	test.AddFormat("Das %s und das %c ein char.", "ist ein String", 'c');
	puts(test);
	printf("Size: %d Length: %d\n", static_cast<int>(test.SizeOf()), static_cast<int>(test.GetLength()));
	std::getchar();
}

void test7Segment() {
	MultiDigit md{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
	MultiDigit md2{ 1 };
	std::cout << static_cast<const char*>(md) << std::endl;
	std::cout << static_cast<const char*>(md2) << std::endl;
	std::getchar();
}

int main() {
	//TestOptParser(argc, argv);
	//TestPrintf();
	//testPreAllocString();
	test7Segment();
}
