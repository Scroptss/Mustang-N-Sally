#include "includes.h"
#include "hooks.h"

//Hooks hooks;

#define M_PI 3.14159265358979323846264338327950288

std::vector<std::string> legit_packets = { "connectResponse", "statresponse", "LM", "disconnect", "loadoutResponse", "infoResponse", "statusResponse", "keyAuthorize", "error", "print", "echo", "fastrestart", "ping", "pinga", "steamAuthReq", "cfl", "Nigger", "faggot", "N1gger", "F4ggot", "fagg0t", "f4gg0t", "n1gg3r", "nigg3r", "bitch", "b1tch", "fuck", "rape", "r4pe", "cock", "c0ck" };

const char* msgTypes[] = { "INFO REQUEST", "INFO RESPONSE", "LOBBY STATE PRIVATE", "LOBBY STATE GAME", "LOBBY STATE GAMEPUBLIC", "LOBBY STATE GAMECUSTOM", "LOBBY STATE GAMETHEATRE", "LOBBY HOST HEARTBEAT", "LOBBY HOST DISCONNECT", "LOBBY HOST DISCONNECT CLIENT", "LOBBY HOST LEAVE WITH PARTY", "LOBBY CLIENT HEARTBEAT", "LOBBY CLIENT DISCONNECT", "LOBBY CLIENT RELIABLE DATA", "LOBBY CLIENT CONTENT", "LOBBY MODIFIED STATS", "JOIN LOBBY", "JOIN RESPONSE", "JOIN AGREEMENT REQUEST", "JOIN AGREEMENT RESPONSE", "JOIN COMPLETE", "JOIN MEMBER INFO", "SERVERLIST INFO", "PEER TO PEER CONNECTIVITY TEST", "PEER TO PEER INFO", "LOBBY MIGRATE TEST", "LOBBY MIGRATE ANNOUNCE HOST", "LOBBY MIGRATE START", "INGAME MIGRATE TO", "INGAME MIGRATE NEW HOST", "VOICE PACKET", "VOICE RELAY PACKET", "DEMO STATE", "COUNT" };

std::vector<int> legit_p = { 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26 };


std::string va(const char* fmt, ...)
{
	char result[2048] = { 0 };

	va_list ap;
	va_start(ap, fmt);

	vsnprintf_s(result, sizeof(result), _TRUNCATE, fmt, ap);

	va_end(ap);
	return result;
}

std::string adr_to_string(const netadr_t* address)
{
	XNADDR xn;

	dwNetadrToCommonAddr(*address, &xn, sizeof xn, nullptr);

	return va("%u.%u.%u.%u", xn.ip[0], xn.ip[1], xn.ip[2], xn.ip[3]);
}

bool is_in_number_array(int cmp1, std::vector<int> cmp2)
{
	for (auto cmp : cmp2)
	{
		if (cmp1 == cmp)
			return true;
	}
	return false;
}

const std::string GetTime() {
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
#pragma warning(suppress : 4996).
	tstruct = *localtime(&now);

	strftime(buf, sizeof(buf), "%X", &tstruct);

	return buf;
}

static bool is_user_in_game()
{
	return Live_IsUserInGame(0);
}

static bool local_client_is_in_game()
{
	return CL_IsLocalClientInGame(0);
}

static bool is_in_game()
{
	return Com_IsInGame();
}

static bool is_match_loaded()
{
	return (is_user_in_game() && local_client_is_in_game() && is_in_game());
}

std::string to_lower(std::string text)
{
	std::transform(text.begin(), text.end(), text.begin(), ::tolower);
	return text;
}

bool is_equal(const std::string& lhs, const std::string& rhs, const std::size_t count, const bool case_sensitive)
{
	auto left = lhs;
	auto right = rhs;

	if (count != std::string::npos)
	{
		if (lhs.size() > count)
			left.erase(count);

		if (rhs.size() > count)
			right.erase(count);
	}

	if (case_sensitive)
	{
		return left == right;
	}

	else
	{
		return to_lower(left) == to_lower(right);
	}
}

bool is_in_array(std::string cmp1, std::vector<std::string> cmp2)
{
	for (auto cmp : cmp2)
	{
		if (!strcmp(cmp1.data(), cmp.data()))
			return true;
	}
	return false;
}

const char* __fastcall hkCL_GetConfigString(std::int32_t configStringIndex)
{
	constexpr auto mspreload_command = "mspreload";

	if (configStringIndex == 3627)
	{
		if (auto config_string{ CL_GetConfigString(configStringIndex) }; is_equal(config_string, mspreload_command, std::strlen(mspreload_command), false))
		{
			CL_StoreConfigString(configStringIndex, "");

			if (internmsg)
			{
				std::string str = "[^2SALLYBOT^7] Loadside ^1Blocked ";

				CG_BoldGameMessageCenter(0, str.data());
			}
		}
	}

	return CL_GetConfigString(configStringIndex);
}

__int64 hkdwInstantDispatchMessage(__int64 sender_id, unsigned int controllerIndex, __int64 msg, unsigned int messageSize)
{
	const auto message{ reinterpret_cast<const char*>(msg) };
	const auto message_size{ messageSize };

	instant_message::dispatch::handle_message(sender_id, message, message_size);

	std::srand(time(NULL));
	*(__int32*)((INT64)GetModuleHandleA(NULL) + 0x112F1A14) = rand();

	return 0;
}

LONG CALLBACK hkCL_ConnectionlessCMD(LPEXCEPTION_POINTERS ex)
{

	time_t now = time(0);
#pragma warning(suppress : 4996)
	char* dt = ctime(&now);

	const char* message = (char*)ex->ContextRecord->Rdi;
	std::string sender = adr_to_string((netadr_t*)ex->ContextRecord->R15);

	if (is_in_array(message, legit_packets))
	{
		ex->ContextRecord->Rip += 3;
		ex->ContextRecord->Rdx = ex->ContextRecord->R12;
		return EXCEPTION_CONTINUE_EXECUTION;
	}

	std::string str = std::string(message) + " Received from " + sender;

	if (internmsg)
	{
		std::string str = "[^2SALLYBOT^7]" " [" + std::string(message) + "] " "^1Blocked " "^7Sent From : ^2" + sender;

		CG_BoldGameMessageCenter(0, str.data());
	}

	if (chatmsg)
	{
		std::string str = "[^2SALLYBOT^7]" " [" + std::string(message) + "] " "^1Blocked " "^7Sent From : ^2" + sender;

		ChatSendMSG(0, str.data(), 0);
	}

	std::ofstream myfile;
	myfile.open("loggingshit\\logs\\logs.txt""", std::ios_base::app);
	myfile << " [SALLYBOT] " "[" << message << "]" " Received From " << sender << "\n";
	myfile.close();

	ex->ContextRecord->Rip = (dwProcessBase + 0x134CE00);

	return EXCEPTION_CONTINUE_EXECUTION;

}

void hkLobbyVM_OnDisconnect(LobbySession* session, __int64 XUID, LobbyDisconnectClient client)
{

	time_t now = time(0);
#pragma warning(suppress : 4996)
	char* dt = ctime(&now);

	std::string kick = std::to_string(client);
	std::string sender = std::to_string(XUID);

	kick = kicks[client];

	if (internmsg)
	{
		std::string str = "[^2SALLYBOT^7]" " [" + std::string(kick) + "] " "^1Dropped " "^7Sent From : ^2" + sender;

		CG_BoldGameMessageCenter(0, str.data());
	}

	if (chatmsg)
	{
		std::string str = "[^2SALLYBOT^7]" " [" + std::string(kick) + "] " "^1Dropped " "^7Sent From : ^2" + sender;

		ChatSendMSG(0, str.data(), 0);
	}

	std::ofstream myfile;
	myfile.open("loggingshit\\logs\\logs.txt""", std::ios_base::app);
	myfile << " [SALLYBOT] " "[" << kick << "]" " Received From " << sender << "\n";
	myfile.close();

	return;
}

LONG CALLBACK hkHandlePacketInternal(LPEXCEPTION_POINTERS ex)
{

	time_t now = time(0);
#pragma warning(suppress : 4996)
	char* dt = ctime(&now);

	msg_t* msg = (msg_t*)ex->ContextRecord->Rbx;
	std::string sender = adr_to_string((netadr_t*)ex->ContextRecord->Rdx);

	LobbyMsg lobbyMsg{};

	LobbyMsgRW_PrepReadMsg(&lobbyMsg, msg);

	if (is_in_number_array(lobbyMsg.msgType, legit_p))
	{
		ex->ContextRecord->Rip += 3;
		ex->ContextRecord->Rdx = ex->ContextRecord->Rbx;
		return EXCEPTION_CONTINUE_EXECUTION;
	}

	std::string str = std::string(msgTypes[lobbyMsg.msgType]) + " Received";

	if (internmsg)
	{
		CG_BoldGameMessageCenter(0, str.data());
	}

	if (chatmsg)
	{
		ChatSendMSG(0, str.data(), 0);
	}

	std::ofstream myfile;
	myfile.open("loggingshit\\logs\\logs.txt""", std::ios_base::app);
	myfile << " [SALLYBOT] " "[" << msgTypes[lobbyMsg.msgType] << "]" " Recived From " << sender << "\n";
	myfile.close();

	ex->ContextRecord->Rip = (dwProcessBase + 0x1EF81BD);

	return EXCEPTION_CONTINUE_EXECUTION;

}

void main::hook::initializeHook() {

	Hooks hook;

	hook.Initialize();

	void handle_hooks();

	THREADENTRY32 te32;
	HANDLE hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);

	if (hThreadSnap)
	{
		te32.dwSize = sizeof(THREADENTRY32);

		if (!Thread32First(hThreadSnap, &te32))
		{
			CloseHandle(hThreadSnap);
		}
		else {
			do
			{
				if (te32.th32OwnerProcessID == GetCurrentProcessId() && te32.th32ThreadID != GetCurrentThreadId())
				{
					HANDLE hThread = OpenThread(THREAD_GET_CONTEXT | THREAD_SET_CONTEXT | THREAD_SUSPEND_RESUME, 0, te32.th32ThreadID);
					if (hThread)
					{
						CONTEXT context;
						context.ContextFlags = CONTEXT_DEBUG_REGISTERS;
						SuspendThread(hThread);

						if (GetThreadContext(hThread, &context))
						{
							context.Dr0 = (uintptr_t)dwInstantDispatchMessage;
							context.Dr1 = (uintptr_t)CL_ConnectionlessCMD;
							context.Dr2 = (uintptr_t)LobbyVM_OnDisconnect;
							context.Dr6 = (uintptr_t)HandlePacketInternal;
							context.Dr7 = (1 << 0) | (1 << 2) | (1 << 4) | (1 << 6);

							SetThreadContext(hThread, &context);
						}

						ResumeThread(hThread);
						CloseHandle(hThread);
					}
				}
			} while (Thread32Next(hThreadSnap, &te32));
			CloseHandle(hThreadSnap);
		}
	}
	SetUnhandledExceptionFilter(main::hook::hookHandler);
}

void on_frame()
{
	static bool enabled;

	if (is_match_loaded() && !enabled)
	{
		MH_CreateHook((void*)(dwProcessBase + 0x1321110), hkCL_GetConfigString, (void**)&CL_GetConfigString);
		MH_EnableHook((void*)(dwProcessBase + 0x1321110));

		enabled = true;
	}
	else if (!is_in_game() && enabled)
	{
		MH_RemoveHook((void*)(dwProcessBase + 0x1321110));
		MH_DisableHook((void*)(dwProcessBase + 0x1321110));

		enabled = false;
	}
}


LONG CALLBACK main::hook::hookHandler(LPEXCEPTION_POINTERS ex)
{
	if (ex->ExceptionRecord->ExceptionCode == STATUS_SINGLE_STEP)
	{

		if (ex->ContextRecord->Rip == (uintptr_t)dwInstantDispatchMessage)
		{
			ex->ContextRecord->Rip = (uintptr_t)hkdwInstantDispatchMessage;
		}
		else if (ex->ContextRecord->Rip == (uintptr_t)LobbyVM_OnDisconnect)
		{
			ex->ContextRecord->Rip = (uintptr_t)hkLobbyVM_OnDisconnect;
		}
		else if (ex->ContextRecord->Rip == (uintptr_t)CL_ConnectionlessCMD)
		{
			return hkCL_ConnectionlessCMD(ex);
		}
		else if (ex->ContextRecord->Rip == (uintptr_t)HandlePacketInternal)
		{
			return hkHandlePacketInternal(ex);
		}

		return EXCEPTION_CONTINUE_EXECUTION;
	}

	time_t now = time(0);
#pragma warning(suppress : 4996)
	char* dt = ctime(&now);

	return EXCEPTION_CONTINUE_SEARCH;
}