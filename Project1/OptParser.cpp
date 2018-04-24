#include "OptParser.h"
//returns true if all arguments are successfully parsed
bool CmdLineOptParser::Parse(int argc, char* argv[])
{
	int argsParsed = 1; //skip first arg
	bool success = true;

	while (argsParsed < argc) {
		bool ignoreNext = false;
		char option;
		char* infoPtr;

		//make sure option begins with -x
		if (argv[argsParsed][0] == '-' && argv[argsParsed][1] != 0) {

			option = argv[argsParsed][1];
			if (argv[argsParsed][2] == 0) {
				//first char after x is null
				if (argsParsed == argc - 1) {
					//This is the last argument, info = null
					infoPtr = 0;
				}
				else if (argsParsed + 1 < argc) {
					//skip nullbyte
					if (argv[argsParsed + 1][0] == '-') {
						//This option has no info
						infoPtr = 0;
					}
					else {
						//Next argument is info
						ignoreNext = true;
						infoPtr = &argv[argsParsed + 1][0];
					}
				}
			}
			else if (argv[argsParsed][2] == '=') {
				//Option with '='
				if (argv[argsParsed][3] == 0)
				{
					//no info after '=', uses "=\0" as info
					infoPtr = &argv[argsParsed][2];
				}
				else {
					//skips '='
					infoPtr = &argv[argsParsed][3];
				}
			}
			else {
				infoPtr = &argv[argsParsed][2];
			}

			if (ignoreNext) {
				//skip next arg
				argsParsed += 2;
			}
			else {
				argsParsed++;
			}
			if (!Option(option, infoPtr)) success = false;
			option = 0;
		}
		else {
			//incorrect syntax, ignore argument and set success to false
			success = false;
			argsParsed++;
		}
	}
	return success;
}

bool CmdLineOptParser::Option(const char option, const char* info) {
	if (info == 0 || option == 'z') return false;
	else return true;
}