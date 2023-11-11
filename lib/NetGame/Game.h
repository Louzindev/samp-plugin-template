#ifndef _GAME_H_
#define _GAME_H_
#include "CNetGame.h"

namespace NetGame
{
	class Game
	{
	public:
		static CNetGame* GetNetGame();
	};
}

#endif