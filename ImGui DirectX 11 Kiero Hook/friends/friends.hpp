#pragma once
#include "../includes.h"

namespace friends
{
	struct friends_t
	{
		std::uint64_t xuid;
		std::string name;
		std::string ip_str;
		netadr_t netadr;
		std::string online = "b"s;
	};

	void refresh_friends();
	void friends_list();
	void write_to_friends();
	void write_ip_to_friends(const std::string friend_ip, const std::string xuid_str);

	extern std::vector<friends_t> friends;
}