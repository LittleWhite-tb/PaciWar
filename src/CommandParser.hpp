#ifndef COMMANDPARSER_HPP
#define COMMANDPARSER_HPP

class Settings;

class CommandParser
{
	static bool parse(int argc, char** argv, Settings& result);
};

#endif
