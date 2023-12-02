include(AMXConfig)
include(AddSAMPPlugin)

set(SOURCES
	"${SDK}/amxplugin.cpp"
	"${SDK}/plugin.cpp"
	"${RAKNET}/RakServer.h"
	"${RAKNET}/RakServer.cpp"
	"${RAKNET}/BitStream.h"
	"${RAKNET}/BitStream.cpp"
	"${SAMP}/CSAMP.h"
	"${SAMP}/CSAMP.cpp"
	"${LIB}/subhook/subhook.c"
	"${LIB}/Memory.cpp"
)

add_samp_plugin(Plugin 
	"${SOURCES}"
	"main.cpp"
	"Native.cpp"
	"Hooks.cpp"
	"plugin.def"
)

target_include_directories(Plugin PUBLIC
	"${LIB}"
)

install(TARGETS Plugin DESTINATION ${SAMPSVR_PLUGIN_DIR})