#pragma once
#include <string>

class buildPath
{
public:
    enum type
		{
			year, month
		};

	buildPath(std::string, buildPath&);
	buildPath(std::string);// tip of tail
	buildPath(buildPath::type, buildPath&);
	buildPath(buildPath::type);// tip of tail
	~buildPath();
	

private:

};