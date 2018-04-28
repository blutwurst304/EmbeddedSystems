#pragma once
#include <iostream>
#include "PreAllocString.h"
#include <stdarg.h>

#define MAX_DIGITS 100
#define DIGIT_CHARLENGTH 20

static const char* digits = " - | |   | | -      |     |    -   | - |   -  -   | -   | -    | | -   |    - |   -   | -  - |   - | | -  -   |     |    - | | - | | -  - | | -   | - ";

class MultiDigit {
public:
	operator const char*() const;
	template<typename ... Args>
	constexpr MultiDigit(Args...Ns);
private:
	//Problem: string zeigt evtl. auf sinnloses Zeug nach verlassen des Konstruktors (wg. PreAllocString implementierung)
	PreAllocString<MAX_DIGITS*DIGIT_CHARLENGTH> string;
	template<typename ... Args>
	const char* createString(int, Args ... args);
	void createLine(int, int, ...);
};

MultiDigit::operator const char*() const
{
	return static_cast<const char*>(string);
}

template<typename ... Args>
inline const char* MultiDigit::createString(int count, Args ... args)
{
	for (int i = 0; i < 5; i++) {
		createLine(i, count, args...);
	}
	return static_cast<const char*>(string);
}

inline void MultiDigit::createLine(int line, int count, ...)
{
	va_list argPtr;
	va_start(argPtr, count);
	for (int i = 0; i < count; i++) {
		int digit = va_arg(argPtr, int) % 10;
		for (int j = 0; j < 3; j++) {
			string += digits[digit * 15 + line * 3 + j];
		}
		if (i < count - 1) {
			string.AddWhiteSpace();
		}
	}
	string += '\n';
	va_end(argPtr);
}



template<typename ... Args>
inline constexpr MultiDigit::MultiDigit(Args...Ns)
{
	string = createString(sizeof...(Ns), Ns...);
}