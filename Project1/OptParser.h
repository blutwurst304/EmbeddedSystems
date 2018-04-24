#pragma once
class CmdLineOptParser {
public:
	bool Parse(int, char* argv[]);
protected:
	virtual bool Option(const char, const char*);
};