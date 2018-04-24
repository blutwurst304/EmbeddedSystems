#include "Printf.h"

long long pow(int base, int exp) {
	long long res = base;
	if (exp == 0) return 1;
	if (exp == 1) return res;
	for (int i = 0; i < exp - 1; i++) {
		res *= base;
	}
	return res;
}

long long pow10(int exp) {
	return pow(10, exp);
}

long long pow2(int exp) {
	return pow(2, exp);
}

char digitToChar(int digit) {
	switch (digit/10) {
	case 0: return digit + 48;
	case 1: return digit + 55;
	default: return 48;
	}
}

bool insertChar(char* dst, const void* end, const char c, int pos) {
	if (&dst[pos] < end) {
		dst[pos] = c;
		return true;
	}
	else return false;
}

int toHex(int val, char* dst, int posDst, const void* end) {
	if (val == 0) {
		if (insertChar(dst, end, '0', posDst)) return 1;
		else return 0;
	}
	
	int value = val;
	int written = 0;
	bool start = false;
	if (insertChar(dst, end, '0', posDst))written++;
	else return written;
	if (insertChar(dst, end, 'x', posDst+written))written++;
	else return written;

	unsigned int mask = 0xF0000000;
	for (int i = 7; i >= 0; i--) {
		int digit = (value & mask) >> 4 * i;
		char symbol = digitToChar(digit);
		if (symbol != '0' && !start) {
			start = true;
		}
		if(start)
		{
			if (insertChar(dst, end, symbol, posDst + written))written++;
			else return written;
		}
		mask >>= 4;
	}
	return written;
}

int toBinary(int val, char* dst, int posDst, const void* end) {
	if (val == 0) {
		if (insertChar(dst, end, '0', posDst)) return 1;
		else return 0;
	}
	
	int written = 0;
	unsigned int mask = 0x80000000;

	if (insertChar(dst, end, '0', posDst))written++;
	else return written;
	if (insertChar(dst, end, 'b', posDst+written))written++;
	else return written;

	bool start = false;
	for (int i = 31; i >= 0; i--) {
		if (val & mask) {
			start = true;
			if (insertChar(dst, end, '1', posDst + written))written++;
			else return written;
		}
		else {
			if (start) {
				if (insertChar(dst, end, '0', posDst + written))written++;
				else return written;
			}
		}
		mask >>= 1;
	}
	return written;
}

int itod(unsigned int val, char* dst, int posDst, const void* end) {
	if (val == 0) {
		if (insertChar(dst, end, '0', posDst)) return 1;
		else return 0;
	}
	
	int written = 0;
	int length = 0;
	unsigned int value = val;
	while (static_cast<long long>(value) >= pow10(length)) {
		length++;
	}
	
	for (int i = 1; i <= length; i++) {
		int power = static_cast<int>(pow10(length - i));
		int digit = (value / power);
		if (insertChar(dst, end, digitToChar(digit), posDst + written)) written++;
		else return written;
		value -= digit * static_cast<int>(pow10(length - i));
	}
	return written;
}

//TODO: write -, then treat as unsigned
int itod(int val, char* dst, int posDst, const void* end) {
	int written = 0;
	if (val < 0) {
		if (insertChar(dst, end, '-', posDst)) written++;
		else return 0;
		written+=itod(static_cast<unsigned int>(val*-1), dst, posDst + written, end);
	}
	else {
		written+=itod(static_cast<unsigned int>(val), dst, posDst + written, end);
	}
	return written;
}

char * Printf(char* dst, const void* end, const char * fmt, va_list argPtr) {
	int positionFMT = 0;
	int positionDST = 0;

	if (dst == nullptr || end == nullptr || fmt == nullptr) return nullptr;

	//initialise target array
	while (&dst[positionDST] < end) {
		dst[positionDST] = ' ';
		positionDST++;
	}
	positionDST = 0;
	
	while (fmt[positionFMT] != 0)
	{
		if (fmt[positionFMT] == 0 || &dst[positionDST] >= end) {
			//reached end
			break;
		}
		//Check each char
		if (fmt[positionFMT] == '%' && fmt[positionFMT + 1] != 0) {
			switch (fmt[++positionFMT]) //increment positionFMT -> skip fmt
			{
			case 'd': {
				//Signed Int
				int si = va_arg(argPtr, int);
				positionDST += itod(si, dst, positionDST, end);
				break;
			}
			case 'u': {
				//Unsigned Int
				unsigned int ui = va_arg(argPtr, unsigned int);
				positionDST += itod(ui, dst, positionDST, end);
				break;
			}
			case 'c': {
				//char
				dst[positionDST++] = va_arg(argPtr, int);
				break;
			}
			case 's': {
				//string
				char* s = va_arg(argPtr, char*);
				int i = 0;
				while (s[i] != 0) {
					if (insertChar(dst, end, s[i], positionDST)) {
						positionDST++;
						i++;
					}
					else return &dst[positionDST];
				}
				break;
			}
			case 'x': {
				//Hex
				int h = va_arg(argPtr, int);
				positionDST += toHex(h, dst, positionDST, end);
				break;
			}
			case 'b': {
				//Binary
				int b = va_arg(argPtr, int);
				positionDST += toBinary(b, dst, positionDST, end);
				break;
			}
			case '%': {
				//Percent
				if (insertChar(dst, end, '%', positionDST)) positionDST++;
				else return &dst[positionDST];
				break;
			}
			default: {
				//Insert nothing
			}
			}
		}
		else {
			dst[positionDST] = fmt[positionFMT];
			positionDST++;
		}
		positionFMT++;
	}
	dst[positionDST] = 0;
	return &dst[positionDST];
}

char * Printf(char * dst, const void * end, const char * fmt, ...)
{
	va_list argPtr;
	va_start(argPtr, fmt);
	char* res = Printf(dst, end, fmt, argPtr);
	va_end(argPtr);
	return res;
}
