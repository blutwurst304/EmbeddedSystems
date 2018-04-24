#include "PreAllocString.h"
#include "Printf.h"
#include <stdio.h>

PreAllocString::operator const char*() const
{
	return string;
}

PreAllocString::operator const void*() const
{
	return reinterpret_cast<void*>(string);
}

const char & PreAllocString::operator[](const int idx)
{
	if (static_cast<unsigned int>(idx) <= length && idx >= 0) return string[idx];
	return string[length];
}

void PreAllocString::Empty()
{
	if (size > 0) {
		string[0] = 0;
	}
	length = 0;
}

PreAllocString::PreAllocString(char * str, char* end)
{
	string = str;
	this->end = end;
	size = end + 1 - str;
	string[0] = 0;
}

PreAllocString & PreAllocString::operator=(char rhs)
{
	if (size > 1) {
		string[0] = rhs;
		if (rhs) length = 1;
		else length = 0;
	}
	string[length] = 0;
	return (*this);
}

PreAllocString & PreAllocString::operator=(const char * rhs)
{
	if (rhs != nullptr) {
		unsigned int i = 0;
		while (i < size - 1 && rhs[i]) {
			string[i] = rhs[i];
			i++;
		}
		length = i;
		string[length] = 0;
	}
	return *this;
}

PreAllocString & PreAllocString::operator+=(char rhs)
{
	if (length < size - 1) {
		string[length++] = rhs;
		string[length] = 0;
	}
	return *this;
}

PreAllocString & PreAllocString::operator+=(char const * rhs)
{
	unsigned int i = 0;
	while (length < size - 1 && rhs[i]) {
		string[length++] = rhs[i++];
	}
	string[length] = 0;
	return *this;
}

void PreAllocString::AddFormat(const char * format, ...)
{
	va_list argPtr;
	va_start(argPtr, format);
	char* newEnd = Printf(string, end, format, argPtr);
	va_end(argPtr);
	length = newEnd - string;
}

void PreAllocString::AddWhiteSpace()
{
	*this += ' ';
}
