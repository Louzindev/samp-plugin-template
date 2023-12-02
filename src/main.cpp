#include <sdk\plugin.h>
#include "commom.h"
#include "Native.h"

SAMP::CSAMP* Game = new SAMP::CSAMP();

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports() {
	return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES | SUPPORTS_PROCESS_TICK;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void** ppData) {
	PluginLoad(ppData);
	return true;
}

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX* amx) {
	Game->AmxLoad(RakNet::RakServer::GetRakServer(false));
	return amx_Register(amx, Native::native_list, -1);
}

PLUGIN_EXPORT void PLUGIN_CALL Unload() {
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX* amx) {
	return 1;
}

PLUGIN_EXPORT void PLUGIN_CALL ProcessTick() {

}
