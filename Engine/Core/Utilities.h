#pragma once
#include <string>

namespace dwb
{
	std::string string_toLower(const std::string& str);
	bool string_compare_i(const std::string& str1, const std::string& str2);

	std::string unique_string(const std::string& str);
}