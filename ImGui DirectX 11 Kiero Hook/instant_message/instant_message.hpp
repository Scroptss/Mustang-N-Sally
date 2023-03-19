
#include "../includes.h"

#include "../players.h"

namespace instant_message
{
	namespace dispatch
	{
			void handle_message(const std::uint64_t sender_id, const char* message, const std::uint32_t message_size);
			void info_response_loop(const std::uint64_t sender_id, const char* message, const std::uint32_t message_size);
	}

	extern std::unordered_map<std::uint64_t, XSESSION_INFO> players_session_info;

	void send_info_request(const std::uint64_t target_steam_id);

}