#include <sdk\plugin.h>
#include "commom.h"
#include "Native.h"

NetGame::CNetGame* netGame = NULL;
RakNet::RakServer* rakServer = NULL;

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports() {
	return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES | SUPPORTS_PROCESS_TICK;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void** ppData) {
	PluginLoad(ppData);
	return true;
}

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX* amx) {
	static bool loaded = false;
	if(!loaded)
	{
		netGame = NetGame::Game::GetNetGame();
		rakServer = RakNet::RakServer::GetRakServer(false);
		loaded = true;
	}

	return amx_Register(amx, Native::native_list, -1);
}

PLUGIN_EXPORT void PLUGIN_CALL Unload() {
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX* amx) {
	return 1;
}

PLUGIN_EXPORT void PLUGIN_CALL ProcessTick() {

}
