#ifndef _RAKSERVER_H_
#define _RAKSERVER_H_
#include "BitStream.h"
#include "../Hooking.h"
#include "../types.h"
#include "../subhook\subhook.h"
#include "Packet.h"
#include "rpc.h"

namespace RakNet
{
	// Function Types
	typedef bool (THISCALL* RakNet_Start_t)(void* ppRakServer, unsigned short AllowedPlayers, unsigned int depreciated, int threadSleepTimer, unsigned short port, const char* forceHostAddress);
	typedef bool (THISCALL* RakNet_Send_t)(void* ppRakServer, BitStream* parameters, PacketPriority priority, PacketReliability reliability, unsigned orderingChannel, PlayerID playerId, bool broadcast);
	typedef Packet* (THISCALL* RakNet_Receive_t)(void* ppRakServer);
	typedef void (THISCALL* RakNet_SetAllowedPlayers_t)(void* ppRakServer, unsigned short numberAllowed);
	typedef int (THISCALL* RakNet_GetLastPing_t)(void* ppRakServer, const PlayerID playerId);
	typedef void (THISCALL* RakNet_RegisterAsRemoteProcedureCall_t)(void* ppRakServer, int* uniqueID, void(*functionPointer) (RPCParameters* rpcParms));
	typedef void (THISCALL* RakNet_UnregisterAsRemoteProcedureCall_t)(void* ppRakServer, int* uniqueID);
	typedef bool (THISCALL* RakNet_RPC_t)(void* ppRakServer, BYTE* uniqueID, BitStream* parameters, PacketPriority priority, PacketReliability reliability, unsigned orderingChannel, PlayerID playerId, bool broadcast, bool shiftTimestamp);
	typedef const char* (THISCALL* RakNet_GetLocalIP_t)(void* ppRakServer, unsigned int index);
	typedef int (THISCALL* RakNet_GetIndexFromPlayerID_t)(void* ppRakServer, PlayerID playerId);
	typedef PlayerID(THISCALL* RakNet_GetPlayerIDFromIndex_t)(void* ppRakServer, int index);
	typedef void (THISCALL* RakNet_SetTimeoutTime_t)(void* ppRakServer, RakNetTime timeMS, const PlayerID target);
	typedef void (THISCALL* RakNet_AddToBanList_t)(void* ppRakServer, const char* IP, unsigned int milliseconds);
	typedef void (THISCALL* RakNet_RemoveFromBanList_t)(void* ppRakServer, const char* IP);
	typedef void (THISCALL* RakNet_ClearBanList_t)(void* ppRakServer);

	typedef BYTE(*getPacketId_t)(Packet* p);

	// Subhook handlers
	extern DWORD FUNC_GetPacketId;
	extern subhook::Hook GetPacketId_hook;

	class RakServer
	{
	public:
		Packet* Receive(void* ppRakServer) const;

	public:
		static RakServer* GetRakServer(bool passive);
		static Packet* THISCALL HookReceive(void* ppRakServer);
		static BYTE GetPacketId(Packet* packet);

	private:
		// RakServer Data
		void* m_pRakServer;
		RakServer();

	private:
		// Function Pointers
		RakNet_Start_t pnf_Start;
		RakNet_Send_t pnf_Send;
		RakNet_Receive_t pnf_Receive;
		RakNet_SetAllowedPlayers_t pnf_SetAllowedPlayers;
		RakNet_GetLastPing_t pnf_GetLastPing;
		RakNet_RegisterAsRemoteProcedureCall_t pnf_RegisterAsRemoteProcedureCall;
		RakNet_UnregisterAsRemoteProcedureCall_t pnf_UnregisterAsRemoteProcedureCall;
		RakNet_RPC_t pnf_RPC;
		RakNet_GetLocalIP_t pnf_GetLocalIP;
		RakNet_GetIndexFromPlayerID_t pnf_GetIndexFromPlayerID;
		RakNet_GetPlayerIDFromIndex_t pnf_GetPlayerIDFromIndex;
		RakNet_SetTimeoutTime_t pnf_SetTimeoutTime;
		RakNet_AddToBanList_t pnf_AddToBanList;
		RakNet_RemoveFromBanList_t pnf_RemoveFromBanList;
		RakNet_ClearBanList_t pnf_ClearBanList;
	};
}

#endif