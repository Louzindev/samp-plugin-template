#include "RakServer.h"
#include "../sdk/plugincommon.h"
#include "../Memory.h"
#include "../Hooking.h"
#include "../subhook/subhook.h"
#include "RakOffset.h"
#include <sdk\plugin.h>

namespace RakNet
{
	DWORD FUNC_GetPacketId = NULL;
	subhook::Hook GetPacketId_hook;

	RakServer::RakServer()
	{
		this->m_pRakServer = nullptr;

		this->pnf_AddToBanList = nullptr;
		this->pnf_ClearBanList = nullptr;
		this->pnf_GetIndexFromPlayerID = nullptr;
		this->pnf_GetLastPing = nullptr;
		this->pnf_GetLocalIP = nullptr;
		this->pnf_GetPlayerIDFromIndex = nullptr;
		this->pnf_Receive = nullptr;
		this->pnf_RegisterAsRemoteProcedureCall = nullptr;
		this->pnf_RemoveFromBanList = nullptr;
		this->pnf_RPC = nullptr;
		this->pnf_Send = nullptr;
		this->pnf_SetAllowedPlayers = nullptr;
		this->pnf_SetTimeoutTime = nullptr;
		this->pnf_Start = nullptr;
		this->pnf_UnregisterAsRemoteProcedureCall = nullptr;
	}

	// Returns an RakServer instance.
	RakServer * RakServer::GetRakServer(bool passive)
	{
		// Initialize RakServer instance
		RakServer* rakServer = new RakServer(); // new RakServer instance


		void* pRakServer = NULL;
		int (*pfn_GetRakServer)(void) = (int(*)(void))ppPluginData[PLUGIN_DATA_RAKSERVER];
		pRakServer = (void*)pfn_GetRakServer();

		// Get RakServer Function Table
		int* pRakServer_VTBL = ((int*)(*(void**)pRakServer)); // Initialize RakServer function table

		// Fill rakServer instance
		rakServer->m_pRakServer = pRakServer;
		rakServer->pnf_AddToBanList = reinterpret_cast<RakNet_AddToBanList_t>(pRakServer_VTBL[RAKNET_ADD_BAN_OFFSET]);
		rakServer->pnf_ClearBanList = reinterpret_cast<RakNet_ClearBanList_t>(pRakServer_VTBL[RAKNET_CLEAR_BAN_OFFSET]);
		rakServer->pnf_GetIndexFromPlayerID = reinterpret_cast<RakNet_GetIndexFromPlayerID_t>(pRakServer_VTBL[RAKNET_GET_INDEX_FROM_PLAYERID_OFFSET]);
		rakServer->pnf_GetLastPing = reinterpret_cast<RakNet_GetLastPing_t>(pRakServer_VTBL[RAKNET_GET_LAST_PING_OFFSET]);
		rakServer->pnf_GetLocalIP = reinterpret_cast<RakNet_GetLocalIP_t>(pRakServer_VTBL[RAKNET_GET_LOCAL_IP_OFFSET]);
		rakServer->pnf_GetPlayerIDFromIndex = reinterpret_cast<RakNet_GetPlayerIDFromIndex_t>(pRakServer_VTBL[RAKNET_GET_PLAYERID_FROM_INDEX_OFFSET]);
		rakServer->pnf_Receive = reinterpret_cast<RakNet_Receive_t>(pRakServer_VTBL[RAKNET_RECEIVE_OFFSET]);
		rakServer->pnf_RegisterAsRemoteProcedureCall = reinterpret_cast<RakNet_RegisterAsRemoteProcedureCall_t>(pRakServer_VTBL[RAKNET_REGISTER_RPC_OFFSET]);
		rakServer->pnf_RemoveFromBanList = reinterpret_cast<RakNet_RemoveFromBanList_t>(pRakServer_VTBL[RAKNET_REMOVE_BAN_OFFSET]);
		rakServer->pnf_RPC = reinterpret_cast<RakNet_RPC_t>(pRakServer_VTBL[RAKNET_RPC_OFFSET]);
		rakServer->pnf_Send = reinterpret_cast<RakNet_Send_t>(pRakServer_VTBL[RAKNET_SEND_OFFSET]);
		rakServer->pnf_SetAllowedPlayers = reinterpret_cast<RakNet_SetAllowedPlayers_t>(pRakServer_VTBL[RAKNET_SET_ALLOWED_PLAYERS_OFFSET]);
		rakServer->pnf_SetTimeoutTime = reinterpret_cast<RakNet_SetTimeoutTime_t>(pRakServer_VTBL[RAKNET_SET_TIMEOUT_OFFSET]);
		rakServer->pnf_Start = reinterpret_cast<RakNet_Start_t>(pRakServer_VTBL[RAKNET_START_OFFSET]);
		rakServer->pnf_UnregisterAsRemoteProcedureCall = reinterpret_cast<RakNet_UnregisterAsRemoteProcedureCall_t>(pRakServer_VTBL[RAKNET_UNREGISTER_RPC_OFFSET]);

		if (!passive)
		{
			// Hook original RakServer->Receive
			Unlock((void*)&pRakServer_VTBL[RAKNET_RECEIVE_OFFSET], 4); pRakServer_VTBL[RAKNET_RECEIVE_OFFSET] = reinterpret_cast<int>(HookReceive);
		}

		// Get GetPacketId data
#ifdef _WIN32
		FUNC_GetPacketId = FindPattern("\x8B\x44\x24\x04\x85\xC0\x75\x03\x0C\xFF\xC3", "xxxxxxx???x");
#else
		FUNC_GetPacketId = FindPattern("\x55\xB8\x00\x00\x00\x00\x89\xE5\x8B\x55\x00\x85\xD2", "xx????xxxx?xx");
#endif

		if (FUNC_GetPacketId != NULL)
		{
			GetPacketId_hook.Install(reinterpret_cast<void*>(FUNC_GetPacketId), reinterpret_cast<void*>(GetPacketId));
		}
		else
		{
			return NULL;
		}

		// Return RakServer instance
		return rakServer;
	}

	Packet* RakServer::Receive(void* ppRakServer) const
	{
		return pnf_Receive(ppRakServer);
	}


	BYTE RakServer::GetPacketId(Packet* p)
	{
		subhook::ScopedHookRemove remove(&GetPacketId_hook);

		const BYTE packetId = (reinterpret_cast<getPacketId_t>(FUNC_GetPacketId))(p);

		if (packetId == 0xFF)
		{
			return 0xFF;
		}

		if (!GetPacketId_hook.GetTrampoline())
		{
			return packetId;
		}
		else
		{
			return (reinterpret_cast<getPacketId_t>(GetPacketId_hook.GetTrampoline()))(p);
		}
	}

}