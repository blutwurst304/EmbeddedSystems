#pragma once

class MultiDigit {
public:
	operator const char*() const;
	
	MultiDigit(int, int...);
	MultiDigit(int);
private:
	char* string;
	unsigned int size;
};