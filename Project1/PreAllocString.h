#pragma once

#define CREATE(varName, size) \
	char varName##tmp[size+1]; \
	PreAllocString varName = PreAllocString(varName##tmp, &varName##tmp[size]);

class PreAllocString {
public:
	operator const char *() const; //Typecast to char*
	operator const void *() const; //to void*
	const char& operator [] (const int idx);  //tested
	size_t GetLength() const {
		return length;
	}
	constexpr size_t SizeOf() {
		return size-1;
	}
	void Empty();

	PreAllocString(char* str, char* end);

	PreAllocString& operator =(char rhs); //tested
	PreAllocString& operator =(const char * rhs); //tested
	PreAllocString& operator =(char * const rhs); //tested

	PreAllocString& operator +=(char rhs); //tested
	PreAllocString& operator +=(char const * rhs);

	void AddFormat(const char* format, ...); //does not work
	void AddWhiteSpace(); //tested
private:
	char* string;
	const char* end;
	size_t length = 0, size;
};
