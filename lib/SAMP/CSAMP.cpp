#include "CSAMP.h"
#include <sdk\plugin.h>

namespace SAMP
{
	NetGame::CNetGame* CSAMP::GetPool()
	{
		return this->m_GamePool;
	}

	RakNet::RakServer* CSAMP::GetRakServer()
	{
		return this->m_RakServer;
	}

	bool CSAMP::AmxLoad(RakNet::RakServer* pRakServer)
	{
		if (this->m_amxload)
		{
			return true;
		}
		this->m_GamePool = GetNetGame();
		this->m_RakServer = pRakServer;
		return true;
	}

	NetGame::CNetGame* CSAMP::GetNetGame()
	{
		NetGame::CNetGame* pNetGame = NULL;
		auto(*pfn_GetNetGame)(void) = (int(*)(void))ppPluginData[PLUGIN_DATA_NETGAME];
		pNetGame = reinterpret_cast<NetGame::CNetGame*>(pfn_GetNetGame());

		return pNetGame;
	}

}