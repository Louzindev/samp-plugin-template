#include "Native.h"

namespace Native
{
	// native PrintPlayerH(const playerid);
	cell PrintPlayerH(AMX* amx, cell* params)
	{
		const int playerid = static_cast<int>(params[1]);
		logprintf("Player id: %d has 100 health\n", playerid);
		return 1;
	}

	const AMX_NATIVE_INFO native_list[] = {
		{ "PrintPlayerH", PrintPlayerH }
	};
}