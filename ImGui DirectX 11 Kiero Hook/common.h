#pragma once
#include "includes.h"

extern std::vector<std::string> vec;

//extern bool tr;
//extern bool tp;

//GAME FUNCTIONS
extern std::uintptr_t dwProcessBase;

using ControllerIndex_t = std::uint32_t;
using ClientNum_t = std::uint32_t;

//CORE
extern bool menurgb;

extern float flHue;

//ESP
extern bool enemy_active;
extern bool friendly_active;
extern bool rgb_enemy;
extern bool rgb_friendly;
extern bool unfilled_boxes;
extern bool filled_boxes;
extern bool skeleton_esp;
extern bool player_names;
extern bool corner_esp;
extern bool Healthbars;
extern bool Snaplines;
extern bool crosshair;

extern int speed_sel;

extern float rgb_speed;
extern float boldness;

extern const char* speed_selection[4];

//AIMBOT

extern int delayat;
extern int delayat1;

extern bool aimbot_active;
extern bool nospread;
extern bool pto;
extern bool autofire;
extern bool silent_active;
extern bool snapaim;
extern bool autowall;
extern bool visibility_check;
extern bool ads_check;
extern bool no_recoil;
extern bool selected[21];

extern int bone_type;
extern int aimbot_type;

extern const char* boneSel[21];

//MISC
extern int RequestTMR;
extern int AutoRequestTime;
extern bool session;
extern bool party;
extern bool Name;
extern bool Xuid;
extern bool ItemID;
extern bool list;
extern bool player;
extern bool Config;
extern bool ct;
extern bool div_loop;
extern bool chatmsg;
extern bool internmsg;
extern bool crashrtn;
extern bool crashrtn1;
extern bool inf_hatr;
extern bool begincombo;
extern bool drawcircle;
extern bool start_pos_set;

//TOOLS

extern int map_select;

extern std::string send_map_name;

extern char buf[255];
extern char print_bold[1012];
extern char clan_input[5];
extern char name_input[32];
extern char xuid_lookup_input[20];
extern char name_lookup_input[32];
extern char join_input[32];
extern char callvote_input[10000];
extern char crash_input[32];
extern char popup_input[32];
extern char oob_input[32];
extern char reliable_input[5000];
extern char single_input[5000];
extern char cbuf_input[5000];
extern char player_list[32];
extern char slot_input[50];
extern char steamid_input[50];
extern char spoofName[32];
extern char nameBuffer[32];

// SPOOFING

extern bool spoof_netadr;

extern int c;
extern int clicked;
extern int value;
extern int value2;
extern int frames;
extern int serverID;
extern int itemID;
extern int div_amount;
extern int count1;
extern int count2;

//AUTO OPTIONS

extern std::string chatspam_msg;
extern std::string chatspammssage;

extern std::string kickspam_msg;
extern std::string kickspam_msg1;
extern std::string kickspam_msg2;
extern std::string kickspam_msg3;
extern std::string kickspam_msg4;




extern bool autocrash1;
extern bool autokick1;
extern bool autopopup1;

extern const char* cc[];

const static auto LobbyClientMsg_SendModifiedStats = reinterpret_cast<std::uintptr_t(__fastcall*)(int, int)>(dwProcessBase + 0x1ED42A0);
const static auto BG_WeaponFireRecoil = reinterpret_cast<std::uintptr_t(__fastcall*)(double val, void* ps, float* recoilSpeed, float* kickaVel)>(dwProcessBase + 0x26D36E0);
const static auto CL_IsLocalClientInGame = reinterpret_cast<std::uintptr_t(__fastcall*)(int localClientNum)>(dwProcessBase + 0x13598E0);
const static auto BG_CalculateViewMovementAngles = reinterpret_cast<std::uintptr_t(__fastcall*)(__int64* a1, __int64 a2, char a3)>(dwProcessBase + 0x26F87B0);

const static auto NET_OutOfBandPrint = reinterpret_cast<bool(__fastcall*)(netsrc_t, netadr_t, const char*)>(dwProcessBase + 0x2174170);
const static auto MSG_InitReadOnly = reinterpret_cast<void(*)(msg_t*, const char*, int)>(dwProcessBase + 0x2155A70);
const static auto MSG_BeginReading = reinterpret_cast<void(*)(msg_t*)>(dwProcessBase + 0x2155760);
const static auto MSG_ReadByte = reinterpret_cast<std::uint8_t(*)(msg_t*)>(dwProcessBase + 0x2155EB0);
const static auto Live_IsUserSignedInToDemonware = reinterpret_cast<bool(*)(const ControllerIndex_t)>(dwProcessBase + 0x1E0D830);
const static auto dwInstantSendMessage = reinterpret_cast<void* (*)(const ControllerIndex_t, const std::uint64_t*, std::uint32_t, std::uint8_t, const void*, unsigned int)>(dwProcessBase + 0x143A810);
const static auto LobbyMsg_SendInfoRequest = reinterpret_cast<bool(__fastcall*)(const ControllerIndex_t, const std::uint64_t*, int, const Msg_InfoRequest*)>(dwProcessBase + 0x1EE54C0);
const static auto LobbyMsgRW_PrepReadData = reinterpret_cast<bool(__fastcall*)(LobbyMsg*, char*, int)>(dwProcessBase + 0x1EF6A10);
const static auto LobbyMsgRW_PrepReadMsg = reinterpret_cast<bool(*)(LobbyMsg*, msg_t*)>(dwProcessBase + 0x1EF6A40);
const static auto MSG_ReadData = reinterpret_cast<void(*)(msg_t*, void*, int)>(dwProcessBase + 0x2155F10);
const static auto MSG_InfoResponse = reinterpret_cast<bool(*)(void*, LobbyMsg*)>(dwProcessBase + 0x1EE1EB0);

//HOOKED FUNCTIONS
const static auto LobbyVM_OnDisconnect = reinterpret_cast<__int64(__fastcall*)(LobbySession * lobbySession, __int64 xuid, __int32 disconnectClient)>(dwProcessBase + 0x1EEFF10);
const static auto dwInstantDispatchMessage = reinterpret_cast<__int64(__fastcall*)(int64 SenderId, unsigned int controllerIndex, __int64 msg, unsigned int messageSize)>(dwProcessBase + 0x143A600);
const static auto CL_ConnectionlessCMD = reinterpret_cast<char(__fastcall*)(LocalClientNum_t localClientNum, netadr_t from, msg_t * msg)>(dwProcessBase + 0x134CDAD);
const static auto HandlePacketInternal = reinterpret_cast<char(__fastcall*)(ControllerIndex_t controllerIndex, netadr_t fromAdr, __int64 fromXUID, LobbyType lobbyType, int a5, msg_t * a6)>(dwProcessBase + 0x1EF8068);

//ESSENTIAL FUNCTIONS
const static auto dwRegisterSecIDAndKey = reinterpret_cast<bool(*)(const bdSecurityID*, const bdSecurityKey*)>(dwProcessBase + 0x143E120);
const static auto dwCommonAddrToNetadr = reinterpret_cast<bool(*)(netadr_t* const, const void* const, const bdSecurityID*)>(dwProcessBase + 0x143C360);
const static auto CL_GetConfigString = reinterpret_cast<const char* (*)(int configStringIndex)>(dwProcessBase + 0x1321110);
const static auto CL_StoreConfigString = reinterpret_cast<const char* (*)(int configStringIndex, const char* string)>(dwProcessBase + 0x13667C0);
const static auto Com_IsInGame = reinterpret_cast<bool(*)()>(dwProcessBase + 0x2148D20);
const static auto Live_IsUserInGame = reinterpret_cast<bool(*)(const ControllerIndex_t controllerIndex)>(dwProcessBase + 0x1E0D7E0);
const static auto LiveFriends_IsFriendByXUID = reinterpret_cast<bool(__fastcall*)(int controllerIndex, int64_t XUID)>(dwProcessBase + 0x1DF9430);
const static auto Dvar_SetFromString = reinterpret_cast<std::uintptr_t(__fastcall*)(const char* dvarname, const char* value, bool createifmissing)>(dwProcessBase + 0x22C7F60);
const static auto Cmd_ExecuteSingleCommand = reinterpret_cast<std::uintptr_t(__fastcall*)(int, int, const char* text, bool)>(dwProcessBase + 0x20EDC20);
const static auto LiveStats_SetClanTagText = reinterpret_cast<std::uintptr_t(__fastcall*)(int, const char*)>(dwProcessBase + 0x1EA5510);
const static auto CL_AddReliableCommand = reinterpret_cast<std::uintptr_t(__fastcall*)(int, const char*)>(dwProcessBase + 0x135D4C0);
const static auto Cbuf_AddText = reinterpret_cast<std::uintptr_t(__fastcall*)(int, const char*)>(dwProcessBase + 0x20EC8B0);
const static auto LobbyVM_JoinEvent = reinterpret_cast<std::uintptr_t(__fastcall*)(int controllerIndex, uint64_t xuid, int joinType)>(dwProcessBase + 0x1EEF8E0);

// Options

const static auto CG_BoldGameMessageCenter = reinterpret_cast<std::uintptr_t(__fastcall*)(int clientNum, const char* msg)>(dwProcessBase + 0x8C4C80);
const static auto ChatSendMSG = reinterpret_cast <std::uintptr_t(__fastcall*)(int, const char* text, int chattype)>(dwProcessBase + 0x1DEAB60);
const static auto LobbyMsgTransport_SendToAdr = reinterpret_cast<bool(__fastcall*)(ControllerIndex_t controllerIndex, int channel, LobbyModule destModule, netadr_t adr, __int64 toXuid, msg_t * msg, MsgType msgType)>(dwProcessBase + 0x1EF8850);
const static auto LobbyMsgRW_PrepWriteMsg = reinterpret_cast<bool(*)(LobbyMsg*, char*, int, MsgType)>(dwProcessBase + 0x1EF6A80);

// Lobby

const static auto LobbySession_GetClientNetAdrByIndex = reinterpret_cast<netadr_t(__fastcall*)(const LobbyType lobbyType, const ClientNum_t clientNum)>(dwProcessBase + 0x1ECC120);
const static auto LobbySession_GetControllingLobbySession = reinterpret_cast<bool(__fastcall*)(const LobbyModule lobbyModule)>(dwProcessBase + 0x1ECC200);
const static auto LobbySession_GetSession = reinterpret_cast<LobbySession * (__fastcall*)(unsigned int a1)>(dwProcessBase + 0x1ECDAB0);
const static auto dwNetadrToCommonAddr = reinterpret_cast<bool(*)(netadr_t, void*, const unsigned int, bdSecurityID*)>(dwProcessBase + 0x143DA60);
const static auto LobbySession_GetClientByClientNum = reinterpret_cast<SessionClient * (*)(LobbySession*, ClientNum_t)>(dwProcessBase + 0x1F000C0);
const static auto LobbyClientMsg_SendDisconnectClient = reinterpret_cast<bool(__fastcall*)(const ControllerIndex_t controllerIndex, LobbyType lobbyType, int64 xuid, __int32 disconnectClient)>(dwProcessBase + 0x1ED40E0);

const static auto LobbyMsg_HandleIM = reinterpret_cast<std::uintptr_t(__fastcall*)(unsigned int targetController, __int64 senderXuid, void* buff, int len)>(dwProcessBase + 0x1EF6430);
const static auto LobbyMsgRW_PackageUInt = reinterpret_cast<bool(*)(LobbyMsg*, const char*, const unsigned int*)>(dwProcessBase + 0x38F7FE0);
const static auto MSG_ReadBigString = reinterpret_cast<const char* (*)(msg_t*)>(dwProcessBase + 0x2DDF310);
const static auto MSG_ReadString = reinterpret_cast<char* (*)(msg_t*, char*, unsigned int)>(dwProcessBase + 0x2DE4CE0);
const static auto Sys_Milliseconds = reinterpret_cast<std::uint64_t(*)()>(dwProcessBase + 0x2333430);

// patches

extern const char* kicks[7];

typedef bool(__fastcall* LootT)(int controllerIndex, __int64 index, unsigned int incAmount);
typedef bool(__fastcall* BG_UnlockablesItemOptionLockedT)(unsigned int a1, unsigned int a2, unsigned int a3, unsigned int a4);
typedef bool(__fastcall* BG_UnlockablesIsItemLockedFromBufferT)(int a1, __int64 a2, int a3);
typedef __int64(__fastcall* CL_GetRankForXPT)(int a1, int a2);
typedef bool(__fastcall* Com_SessionMode_IsPublicOnlineGameT)();
typedef __int64(__fastcall* sub_7FF641E597C0T)(unsigned int localClientNum, int statThing);
typedef __int64(__fastcall* sub_7FF641E596F0T)(unsigned int localClientNum, int statThing);
typedef __int64(__fastcall* LiveStorage_UploadStatsForControllerT)(int controllerIndex);
typedef bool(__fastcall* WorldPosToScreenPosT)(int localClientNum, float* worldPos, float* out);
typedef __int64(__fastcall* CL_GetLocalClientGlobalsT)(int localClientNum);
typedef __int64(__fastcall* AimTarget_GetTagPosT)(__int64 centity_t, unsigned int tagName, float* out);
typedef bool(__fastcall* AimTarget_IsTargetVisibleT)(int localClientNum, __int64 centity_t);
typedef __int64(__fastcall* CG_DObjGetWorldTagPosT)(__int64 a1, __int64 a2, int a3, __int64 a4, __int64 a5, int a6);
typedef WORD(__fastcall* RegisterTagT)(char* tag);
typedef void(__fastcall* GameSendServerCommandT)(int clientNum, int reliable, const char* command);
typedef __int64(__fastcall* CG_DObjGetWorldTagPosInternalT)(__int64 centity_t, __int64 DObj, int tag, float* whatever, float* pos, int something);//, int a6);
typedef char(__fastcall* GScr_SetDStatT)(__int64 a1, const char* a2, __int64 a3);
typedef __int64(__fastcall* Com_GetClientDObjT)(int a1, int a2);
typedef void(__fastcall* SV_ExecuteClientCommandT)(__int64 client_t, __int64 command, int clientOK, int fromOldServer);
typedef __int64(__fastcall* LiveStats_GetRootDDLStateT)(int statThing);
typedef bool(__fastcall* Pub_GameT)();
typedef __int64(__fastcall* DDL_MoveToPathT)(__int64 tmp, char* result, int deptch, const char** path);
typedef __int64(__fastcall* DDL_SetUIntT)(__int64 result, __int64 a1, int buf);
typedef __int64(__fastcall* DDL_GetUIntT)(__int64 result, __int64 a1);
typedef int(__fastcall* GetSessionStateT)();
typedef bool(__fastcall* CG_IsEntityFriendlyNotEnemyT)(int localClientNum, __int64 centity_t);
typedef char* (__fastcall* tGetPersonaName) (DWORD_PTR _this);
typedef __int64(__fastcall* tLiveSteam_FilterPersonaName)(char* buffer, int size, char asciionly);

extern LootT GiveLootToSelf;
extern BG_UnlockablesItemOptionLockedT BG_UnlockablesItemOptionLocked;
extern BG_UnlockablesIsItemLockedFromBufferT BG_UnlockablesIsItemLockedFromBuffer;
extern CL_GetRankForXPT CL_GetRankForXP;
extern Com_SessionMode_IsPublicOnlineGameT Com_SessionMode_IsPublicOnlineGame;
extern sub_7FF641E597C0T sub_7FF641E597C0;
extern sub_7FF641E596F0T sub_7FF641E596F0;
extern LiveStorage_UploadStatsForControllerT LiveStorage_UploadStatsForController;
extern WorldPosToScreenPosT WorldPosToScreenPos;
extern CL_GetLocalClientGlobalsT CL_GetLocalClientGlobals;
extern AimTarget_GetTagPosT AimTarget_GetTagPos;
extern AimTarget_IsTargetVisibleT AimTarget_IsTargetVisible;
extern CG_DObjGetWorldTagPosT CG_DObjGetWorldTagPos;
extern RegisterTagT RegisterTag;
extern GameSendServerCommandT SV_GameSendServerCommand;
extern CG_DObjGetWorldTagPosInternalT CG_DObjGetWorldTagPosInternal;
extern GScr_SetDStatT GScr_SetDStat;
extern Com_GetClientDObjT Com_GetClientDObj;
extern SV_ExecuteClientCommandT SV_ExecuteClientCommand;
extern LiveStats_GetRootDDLStateT LiveStats_GetRootDDLState;
extern Pub_GameT Pub_Game;
extern GetSessionStateT GetSessionState;
extern DDL_GetUIntT DDL_GetUInt;
extern DDL_SetUIntT DDL_SetUInt;
extern DDL_MoveToPathT DDL_MoveToPath;
extern WorldPosToScreenPosT WorldPosToScreenPos;
extern tGetPersonaName oGetPersonaName;
extern tLiveSteam_FilterPersonaName oLiveSteam_FilterPersonaName;
extern DWORD_PTR pGetPersonaNameReturn;
extern DWORD_PTR ISteamFriends;
extern DWORD_PTR pUserData;
extern DWORD_PTR pNameBuffer;

// Utils
#define Hook(original, hook) (DetourTransactionBegin(), DetourUpdateThread(GetCurrentThread()), DetourAttach((LPVOID*)&original, (LPVOID)hook), DetourTransactionCommit())
#define Unhook(original, hook) (DetourTransactionBegin(), DetourUpdateThread(GetCurrentThread()), DetourDetach((LPVOID*)&original, (LPVOID)hook), DetourTransactionCommit())

inline DWORD_PTR HookVMT(DWORD_PTR pVtable, DWORD_PTR hook, int index)
{
    DWORD_PTR* vtable = *(DWORD_PTR**)pVtable;
    DWORD_PTR backup = 0;
    MEMORY_BASIC_INFORMATION mbi;
    VirtualQuery((LPCVOID)vtable, &mbi, sizeof(mbi));
    VirtualProtect(mbi.BaseAddress, mbi.RegionSize, PAGE_READWRITE, &mbi.Protect);
    backup = vtable[index];
    vtable[index] = (DWORD_PTR)hook;
    VirtualProtect(mbi.BaseAddress, mbi.RegionSize, mbi.Protect, &mbi.Protect);
    return backup;
}

inline void RenamePreGame(std::string name)
{
    if (name.size() > 31)
        name.resize(31);

    strncpy_s((char*)(pUserData + 0x8), 32, name.c_str(), name.size());
    strncpy_s((char*)(pNameBuffer), 32, name.c_str(), name.size());
}