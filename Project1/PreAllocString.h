#ifndef PREALLOCSTRING_H
#define PREALLOCSTRING_H

#include <stdio.h>

template<size_t _Template_Size>
class PreAllocString
{
public:
	constexpr PreAllocString()
		: currentLen{ 0 }
	{
	}

	operator const char*() const {
		return buffer;
	}

	operator const void*() const {
		return reinterpret_cast<void *>(buffer);
	}

	size_t GetLength() const
	{
		return currentLen;
	}

	size_t constexpr SizeOf() {
		return _Template_Size;
	}

	const char & operator [] (const int idx)
	{
		unsigned int id = static_cast<unsigned int>(idx);
		if (id <= maxLen)
		{
			return buffer[id];
		}
		return buffer[0];
	}

	PreAllocString& operator =(char rhs)
	{
		if (maxLen>0)
		{
			buffer[0] = rhs;
			unsigned int i = 0;
			if (maxLen>1)
			{
				//i+1->0
				for (i = 1;i<maxLen;i++)
				{
					buffer[i] = 0;
				}
			}
			currentLen = i;
		}
		return *this;
	}

	PreAllocString& operator =(const char* rhs)
	{
		//printf("is string %s \n",rhs);
		if (!rhs)return *this;
		unsigned int i = 0;
		for (i = 0;i<maxLen;i++)
		{
			buffer[i] = rhs[i];
			if (rhs[i] == 0)break;
		}
		currentLen = i;
		//printf("%s\n",buffer);
		return *this;
	}

	PreAllocString& operator =(char *const rhs)
	{
		if (!rhs)return *this;
		if (maxLen>0 && rhs)
		{
			unsigned int i = 0;
			for (i = 0;i<maxLen;i++)
			{
				buffer[i] = rhs[i];
				if (rhs[i] == 0)break;
			}
			currentLen = i;
		}
		return *this;
	}

	PreAllocString& operator +=(char rhs)
	{
		//printf("+= char %c",rhs);
		if (currentLen + 1<maxLen)
		{
			buffer[currentLen] = rhs;
			buffer[currentLen + 1] = 0;
		}
		++currentLen;
		return *this;
	}

	PreAllocString& operator +=(char const* rhs)
	{
		//printf("+= string %s",rhs);
		if (!rhs)return*this;
		unsigned int i = 0;
		for (i = 0;i + currentLen<maxLen;i++)
		{
			buffer[i + currentLen] = rhs[i];
			if (rhs[i] == 0)break;
		}
		currentLen += i;
		return *this;
	}

	void Empty()
	{
		buffer[0] = 0;
		currentLen = 0;
	}

	void AddFormat(const char* format, ...)
	{
		//printf("Formatting...\n%s",format);
		va_list args;
		va_start(args, format);
		char* x = Printf(buffer + currentLen, buffer + maxLen, format, args);
		va_end(args);
		currentLen = x - buffer;
	}

	void AddWhiteSpace()
	{
		//printf("Adding Whitespace...\n");
		if (currentLen + 1<maxLen)
		{
			buffer[currentLen] = ' ';
			buffer[currentLen + 1] = 0;
			currentLen++;
		}
	}

private:
	char buffer[_Template_Size];
	size_t currentLen;
	size_t maxLen = _Template_Size;
};

#define CREATE(varName, _Template_Size) PreAllocString<_Template_Size> varName;
#endif