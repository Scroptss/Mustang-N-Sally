#pragma once
#include "includes.h"
#define OFFSET(x) ((INT64)GetModuleHandle(NULL) + (INT64)x)



enum netsrc_t
{
	NS_NULL = 0xFFFFFFFF,
	NS_CLIENT1 = 0x0,
	NS_CLIENT2 = 0x1,
	NS_CLIENT3 = 0x2,
	NS_CLIENT4 = 0x3,
	NS_SERVER = 0x4,
	NS_MAXCLIENTS = 0x4,
	NS_PACKET = 0x5,
};

enum netadrtype_t
{
	NA_BOT = 0x0,
	NA_BAD = 0x1,
	NA_LOOPBACK = 0x2,
	NA_RAWIP = 0x3,
	NA_IP = 0x4,
};

struct netadr_t
{
	union
	{
		std::uint8_t ip[4];
		std::uint32_t inaddr;
	};

	std::uint16_t port;
	netadrtype_t type;
	netsrc_t localNetID;
};

enum JoinType
{
	JOIN_TYPE_NORMAL = 0x0,
	JOIN_TYPE_PLAYLIST = 0x1,
	JOIN_TYPE_FRIEND = 0x2,
	JOIN_TYPE_INVITE = 0x3,
	JOIN_TYPE_PARTY = 0x4,
	JOIN_TYPE_GROUPS = 0x5,
	JOIN_TYPE_COUNT = 0x6,
};

enum LobbyModule
{
	LOBBY_MODULE_INVALID = 0xFFFFFFFF,
	LOBBY_MODULE_HOST = 0x0,
	LOBBY_MODULE_CLIENT = 0x1,
	LOBBY_MODULE_PEER_TO_PEER = 0x3,
	LOBBY_MODULE_COUNT = 0x4,
};

enum LobbyMode
{
	LOBBY_MODE_INVALID = 0xFFFFFFFF,
	LOBBY_MODE_PUBLIC = 0x0,
	LOBBY_MODE_CUSTOM = 0x1,
	LOBBY_MODE_THEATER = 0x2,
	LOBBY_MODE_ARENA = 0x3,
	LOBBY_MODE_FREERUN = 0x4,
	LOBBY_MODE_COUNT = 0x5,
};

enum class LocalClientNum_t
{
	INVALID_LOCAL_CLIENT = 0xFFFFFFFF,
	LOCAL_CLIENT_0 = 0x0,
	LOCAL_CLIENT_FIRST = 0x0,
	LOCAL_CLIENT_KEYBOARD_AND_MOUSE = 0x0,
	LOCAL_CLIENT_1 = 0x1,
	LOCAL_CLIENT_2 = 0x2,
	LOCAL_CLIENT_3 = 0x3,
	LOCAL_CLIENT_COUNT = 0x4,
};

enum LobbyDisconnectClient
{
	LOBBY_DISCONNECT_CLIENT_INVALID = 0xFFFFFFFF,
	LOBBY_DISCONNECT_CLIENT_DROP = 0x0,
	LOBBY_DISCONNECT_CLIENT_KICK = 0x1,
	LOBBY_DISCONNECT_CLIENT_BADDLC = 0x2,
	LOBBY_DISCONNECT_CLIENT_KICK_PARTY = 0x3,
	LOBBY_DISCONNECT_CLIENT_HOSTRELOAD = 0x4,
	LOBBY_DISCONNECT_CLIENT_NOPARTYCHAT = 0x5,
};

enum LobbyType
{
	LOBBY_TYPE_INVALID = 0xFFFFFFFF,
	LOBBY_TYPE_PRIVATE = 0x0,
	LOBBY_TYPE_GAME = 0x1,
	LOBBY_TYPE_TRANSITION = 0x2,
	LOBBY_TYPE_COUNT = 0x3,
	LOBBY_TYPE_FIRST = 0x0,
	LOBBY_TYPE_LAST = 0x2,
	LOBBY_TYPE_AUTO = 0x3,
};
enum SessionActive
{
	SESSION_INACTIVE = 0x0,
	SESSION_KEEP_ALIVE = 0x1,
	SESSION_ACTIVE = 0x2,
};

enum IMType
{
	JOIN_REQUEST = 0x0,
	JOIN_REPLY = 0x1,
	INVITE = 0x2,
	UPDATE_INVITE_INFO = 0x3,
	NUM_INSTANT_MESSAGE_TYPES = 0x4,
};

enum MsgType
{
	MESSAGE_TYPE_NONE = 0xFFFFFFFF,
	MESSAGE_TYPE_INFO_REQUEST = 0x0,
	MESSAGE_TYPE_INFO_RESPONSE = 0x1,
	MESSAGE_TYPE_LOBBY_STATE_PRIVATE = 0x2,
	MESSAGE_TYPE_DEMO_STATE = 0x20,
	MESSAGE_TYPE_PEER_TO_PEER_CONNECTIVITY_TEST = 0x17,
	MESSAGE_TYPE_COUNT = 0x21,
	MESSAGE_TYPE_LOBBY_HOST_HEARTBEAT = 0x7,
	MESSAGE_TYPE_LOBBY_HOST_DISCONNECT = 0x8,
	MESSAGE_TYPE_LOBBY_HOST_DISCONNECT_CLIENT = 0x9,
	MESSAGE_TYPE_LOBBY_HOST_LEAVE_WITH_PARTY = 0xA,
	MESSAGE_TYPE_LOBBY_CLIENT_HEARTBEAT = 0xB,
	MESSAGE_TYPE_LOBBY_CLIENT_DISCONNECT = 0xC,
	MESSAGE_TYPE_VOICE_PACKET = 0x1E,
	MESSAGE_TYPE_VOICE_RELAY_PACKET = 0x1F,
};

enum PackageType
{
	PACKAGE_TYPE_NONE = 0x0,
	PACKAGE_TYPE_WRITE = 0x1,
	PACKAGE_TYPE_READ = 0x2,
};

enum LobbyNetworkMode
{
	LOBBY_NETWORKMODE_INVALID = 0xFFFFFFFF,
	LOBBY_NETWORKMODE_UNKNOWN = 0x0,
	LOBBY_NETWORKMODE_LAN = 0x1,
	LOBBY_NETWORKMODE_LIVE = 0x2,
	LOBBY_NETWORKMODE_COUNT = 0x3,
	LOBBY_NETWORKMODE_LOCAL = 0x1,
};

enum LobbyMainMode
{
	LOBBY_MAINMODE_INVALID = 0xFFFFFFFF,
	LOBBY_MAINMODE_CP = 0x0,
	LOBBY_MAINMODE_MP = 0x1,
	LOBBY_MAINMODE_ZM = 0x2,
	LOBBY_MAINMODE_COUNT = 0x3,
};

typedef struct _SceKernelEventFlag* SceKernelEventFlag;

typedef uint64_t XUID;

struct v3
{
	float x, y, z;
};

struct Msg_LobbyClientDisconnect
{
	LobbyType lobbyType;
	XUID xuid;
};

struct EVENT_HANDLE
{
	bool manualReset;
	SceKernelEventFlag ef;
};

struct FixedClientInfo
{
	std::uint64_t xuid;
	char gamertag[32];
};

struct ActiveClient
{
	char pad[0x410];
	FixedClientInfo fixedClientInfo;
};

struct SessionClient
{
	char pad[0x8];
	ActiveClient* activeClient;
};

struct LobbySession
{
	LobbyModule module;
	LobbyType type;
	LobbyMode mode;
	char pad[0x34];
	SessionActive active;
	char pad2[0x121D4];
};

struct Msg_InfoRequest
{
	std::uint32_t nonce;
};

struct bdSecurityID
{
	std::uint64_t id;
};

struct bdSecurityKey
{
	char ab[16];
};

#pragma pack(push, 1)
struct XNADDR
{
	char pad[0x1E];
	union
	{
		std::uint8_t ip[4];
		std::uint32_t inaddr;
	};

	std::uint16_t port;
	char pad2[0x1];
};
#pragma pack(pop)

struct XSESSION_INFO
{
	bdSecurityID sessionID;
	XNADDR hostAddress;
	bdSecurityKey keyExchangeKey;
};

struct msg_t
{
	bool overflowed;
	bool readOnly;
	char* data;
	char* splitData;
	int maxsize;
	int cursize;
	int splitSize;
	int readcount;
	int bit;
	int lastEntityRef;
	bool flush;
	netsrc_t targetLocalNetID;
};

struct JoinSessionMessage
{
	IMType mType;
	char pad[0x60];
};


struct LobbyParams
{
	LobbyNetworkMode networkMode;
	LobbyMainMode mainMode;
};

struct SerializedAdr
{
	bool valid;
	XNADDR xnaddr;
};

struct InfoResponseLobby
{
	bool isValid;
	std::uint64_t hostXuid;
	char hostName[32];
	bdSecurityID secId;
	bdSecurityKey secKey;
	SerializedAdr serializedAdr;
	LobbyParams lobbyParams;
	char pad[0x28];
};

struct Msg_InfoResponse
{
	std::uint32_t nonce;
	int uiScreen;
	char natType;
	InfoResponseLobby lobby[2];
};

struct LobbyMsg
{
	msg_t msg;
	MsgType msgType;
	PackageType packageType;
	char encodeFlags;
};