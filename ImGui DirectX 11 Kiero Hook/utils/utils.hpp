#pragma once
#include "../includes.h"

#define FRIENDS_LIST "friends.json"

namespace utils
{
	template <typename T>
	static auto atoi(const std::string& str)
	{
		return static_cast<T>(std::atoi(str.data()));
	}

	static auto atoi(const std::string& str)
	{
		return atoi<std::uint32_t>(str);
	}

	static auto atoll(const std::string& str)
	{
		return static_cast<std::uint64_t>(std::atoll(str.data()));
	}

	std::string va(const char* fmt, ...);
	std::string adr_to_string(const netadr_t* address);

	static std::string ToLower(std::string str)
	{
		std::transform(str.begin(), str.end(), str.begin(), ::tolower);
		return str;
	}

	static std::string FindAndReplaceString(std::string text, std::string find, std::string replace)
	{
		size_t iPosition;

		while ((iPosition = ToLower(text).find(ToLower(find))) != std::string::npos)
			text.replace(iPosition, find.length(), replace);

		return text;
	}
}