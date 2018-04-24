#pragma once
#include <iostream>
#include "PreAllocString.h"
#include <stdarg.h>

static const char* digits = " - | |   | | -      |     |    -   | - |   -  -   | -   | -    | | -   |    - |   -   | -  - |   - | | -  -   |     |    - | | - | | -  - | | -   | - ";

//0 = { " - | |   | | - " };
//0 =	" - "
//		"| |"
//		"   "
//		"| |"
//		" - "

//1 = { "     |     |   " };
//2 = { " -   | - |   - " };
//3 = { " -   | -   | - " };
//4 = { "   | | -   |   " };
//5 = { " - |   -   | - " };
//6 = { " - |   - | | - " };
//7 = { " -   |     |   " };
//8 = { " - | | - | | - " };
//9 = { " - | | -   | - " };

class MultiDigit {
public:
	operator const char*() const;
	template<int ... Ns>
	constexpr MultiDigit();
private:
	//Problem: string zeigt evtl. auf sinnloses Zeug nach verlassen des Konstruktors (wg. PreAllocString implementierung)
	PreAllocString* string;
	template<typename ... Args>
	bool createString(PreAllocString*, int, Args ... args);
	bool createLine(PreAllocString*, int, int, ...);
};

MultiDigit::operator const char*() const
{
	return static_cast<const char*>(*string);
}

template<typename ... Args>
inline bool MultiDigit::createString(PreAllocString * target, int count, Args ... args)
{
	for (int i = 0; i < 5; i++) {
		if(!createLine(string, i, count, args...)) return false;
	}
	return false;
}

inline bool MultiDigit::createLine(PreAllocString * target, int line, int count, ...)
{
	va_list argPtr;
	va_start(argPtr, count);
	for (int i = 0; i < count; i++) {
		int digit = va_arg(argPtr, int) % 10;
		if (digit / 10) return false;
		for (int j = 0; j < 3; j++) {
			*target += digits[digit * 15 + line * 3 + j];
		}
		if (i < count - 1) {
			target->AddWhiteSpace();
		}
	}
	*target += '\n';
	va_end(argPtr);
	return true;
}



template<int ... Ns>
inline constexpr MultiDigit::MultiDigit()
{
	CREATE(var, (sizeof...(Ns)+1) * 20);
	string = &var;
	createString(string, sizeof...(args)+1, args...);
	std::cout << string->SizeOf() << std::endl;
	std::cout << static_cast<const char*>(*this) << std::endl;
}
