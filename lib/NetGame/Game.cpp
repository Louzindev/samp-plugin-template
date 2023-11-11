#include "Game.h"

namespace NetGame
{
	CNetGame* Game::GetNetGame()
	{
		CNetGame* pNetGame = NULL;
		auto(*pfn_GetNetGame)(void) = (int(*)(void))ppPluginData[PLUGIN_DATA_NETGAME];
		pNetGame = reinterpret_cast<CNetGame*>(pfn_GetNetGame());

		return pNetGame;
	}
}