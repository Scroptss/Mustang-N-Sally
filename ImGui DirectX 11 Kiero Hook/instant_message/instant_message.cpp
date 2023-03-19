#include "instant_message.hpp"

using namespace instant_message;

using namespace std;

namespace instant_message
{
	void add_friend_response(const InfoResponseLobby& lobby)
	{
		if (lobby.isValid)
		{
			const auto sess_info{ get_session_info(lobby) };

			netadr_t netadr{};
			dwRegisterSecIDAndKey(&sess_info.sessionID, &sess_info.keyExchangeKey);
			dwCommonAddrToNetadr(&netadr, &sess_info.hostAddress, &sess_info.sessionID);
		}
	}

	constexpr auto nonce{ 1111111111u };

	std::unordered_map<std::uint64_t, XSESSION_INFO> players_session_info;

	void send_info_request(const std::uint64_t target_steam_id)
	{
		if (!Live_IsUserSignedInToDemonware(0))
			return;

		const Msg_InfoRequest message{ 1 };
		LobbyMsg_SendInfoRequest(0, &target_steam_id, 1, &message);
	}

	namespace dispatch
	{
		void handle_message(const std::uint64_t sender_id, const char* message, const std::uint32_t message_size)
		{

			msg_t msg{};
			MSG_InitReadOnly(&msg, message, message_size);
			MSG_BeginReading(&msg);

			auto type = 0ui8;

			std::string outputtype = std::to_string(type);
			std::string sender = std::to_string(sender_id);

			time_t now = time(0);
          #pragma warning(suppress : 4996)
			char* dt = ctime(&now);

			if (MSG_ReadByte(&msg) == '1')
			{
				type = MSG_ReadByte(&msg);
			}

			if (type == 'h')
			{
				if (const auto size{ msg.cursize - msg.readcount }; size < 2048u)
				{
					char data[2048] = { 0 };
					MSG_ReadData(&msg, data, size);

					 std::string str =  "[^2SALLYBOT^7]" " Info Request [1h] " "Sent From : ^2" + sender;

					if (!msg.overflowed)
					{
						LobbyMsg lobby_msg{};
						if (!LobbyMsgRW_PrepReadData(&lobby_msg, data, size))
							return;

						if (lobby_msg.msgType == MESSAGE_TYPE_INFO_RESPONSE)
						{
							Msg_InfoResponse response{};
							if (!MSG_InfoResponse(&response, &lobby_msg))
								return;

							add_friend_response(response.lobby[0]);

							if (internmsg)
							{
								std::string str1 = "[^2SALLYBOT^7]" " InfoResponse ^2Sent ^7To : ^2" + sender;

								CG_BoldGameMessageCenter(0, str.data());
							}
						}
						else
						{
							if (internmsg)
							{
								CG_BoldGameMessageCenter(0, str.data());
							}

							if (crashrtn)
							{
								exploit::send_crash(sender_id);
					
								if (internmsg)
								{
									std::string str1 = "[^2SALLYBOT^7]" " Crash ^6Returned ^7To : ^2" + sender;

									CG_BoldGameMessageCenter(0, str1.data());
								}							
							}
						}
					
						LobbyMsg_HandleIM(0, sender_id, data, size);

						std::ofstream myfile;
						myfile.open("loggingshit\\logs\\logs.txt""", std::ios_base::app);
						myfile << " [SALLYBOT]" " [Info Request] " "Received From " << sender << "\n";
						myfile.close();

						return;
					}
				}
			}

			if (type == 'h')
			{
				if (const auto size{ msg.cursize - msg.readcount }; size < 2048u)
				{
					char data[2048] = { 0 };
					MSG_ReadData(&msg, data, size);

					std::string str = "[^2SALLYBOT^7]" " Peer To Peer " "Sent From : ^2" + sender;

					if (!msg.overflowed)
					{
						LobbyMsg lobby_msg{};
						if (!LobbyMsgRW_PrepReadData(&lobby_msg, data, size))
							return;

						if (lobby_msg.msgType == MESSAGE_TYPE_PEER_TO_PEER_CONNECTIVITY_TEST)
						{
							Msg_InfoResponse response{};
							if (!MSG_InfoResponse(&response, &lobby_msg))
								return;
							
						}
						else
						{
							if (crashrtn)
							{
								exploit::send_crash(sender_id);

								CG_BoldGameMessageCenter(0, str.data());

								CG_BoldGameMessageCenter(0, "^2Crash ^7Sent To ^1Sender");
							}							
						}

						LobbyMsg_HandleIM(0, sender_id, data, size);

						std::ofstream myfile;
						myfile.open("loggingshit\\logs\\logs.txt""", std::ios_base::app);
						myfile << " [SALLYBOT] " "[Peer To Peer]" " Received From " << sender << "\n";
						myfile.close();

						return;
					}
				}
			}

			if (type == 102 && message_size == 102)
				outputtype = "Crash";

			if (type == 102 && message_size == 2)
				outputtype = "Popup";

			std::string str = "[^2SALLYBOT^7] " "[^1" + std::string(outputtype) + "^7]" " Sent From : ^2" + sender;

			if (type == 102 && message_size == 102)
			{
				if (internmsg)
				{
					CG_BoldGameMessageCenter(0, str.data());
				}
					
				if (chatmsg)
				{
					std::string str = "[^2SALLYBOT^7] " + outputtype + " ^1Failed ^7Sent From ^2" + sender;

					ChatSendMSG(0, str.data(), 0);
				}
			}
			
			if (type == 102 && message_size == 2)
			{
				if (internmsg)
				{
				   CG_BoldGameMessageCenter(0, str.data());
				}

				if (chatmsg)
				{
					std::string str = "[^2SALLYBOT^7] " + outputtype + " ^1Failed ^7Sent From ^2" + sender;

					ChatSendMSG(0, str.data(), 0);
				}

			}

			std::ofstream myfile;
			myfile.open("loggingshit\\logs\\logs.txt""", std::ios_base::app);
			if (type == 102 && message_size == 2 || type == 102 && message_size == 102)
			myfile << " [SALLYBOT] " "[" << outputtype << "]" " Received From " << sender << "\n";
			myfile.close();
		}
	}
}