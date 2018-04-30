#pragma once
#include "PreAllocString.h"
#include <stdarg.h>

#define MAX_DIGITS 100
#define DIGIT_CHARLENGTH 20

static const char* digits = " - | |   | | -      |     |    -   | - |   -  -   | -   | -    | | -   |    - |   -   | -  - |   - | | -  -   |     |    - | | - | | -  - | | -   | - ";

template<typename...Args>
class MultiDigit {
public:
	constexpr MultiDigit(Args...Ns)
	{
		//TODO: Nur int akzeptieren
		string = createString(sizeof...(Ns), Ns...);
	}
	operator const char*() const 
	{
		return static_cast<const char*>(string);
	}
private:
	PreAllocString<MAX_DIGITS*DIGIT_CHARLENGTH> string;
	const char* createString(int count, Args ... args)
	{
		for (int i = 0; i < 5; i++) {
			createLine(i, count, args...);
		}
		return static_cast<const char*>(string);
	}
	void createLine(int line, int count, ...)
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
};