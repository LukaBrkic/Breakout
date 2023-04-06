#pragma once

#include <string>

class Util
{
public:
	static void assertWithMessage(bool result, const std::string& message);
	static int randomOneOrMinus();

};

