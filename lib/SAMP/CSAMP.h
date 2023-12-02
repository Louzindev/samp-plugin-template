#ifndef _GAME_H_
#define _GAME_H_
#include "Structs.h"
#include <RakNet/RakServer.h>

namespace SAMP
{
	class CSAMP
	{
	public:
		NetGame::CNetGame* GetPool();
		RakNet::RakServer* GetRakServer();
		bool AmxLoad(RakNet::RakServer* pRakServer);
	private:
		static NetGame::CNetGame* GetNetGame();
		bool m_amxload;
		bool m_load;
		NetGame::CNetGame* m_GamePool;
		RakNet::RakServer* m_RakServer;
	};
}

#endif