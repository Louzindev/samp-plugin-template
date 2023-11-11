#include "commom.h"
#include <RakNet/Packet.h>

#include <sdk\plugin.h>

RakNet::Packet* __thiscall RakNet::RakServer::HookReceive(void* ppRakServer)
{
	RakNet::Packet* packet = rakServer->Receive(ppRakServer);
	BYTE packetID = RakNet::RakServer::GetPacketId(packet);
	if (packetID != 255)
	{
		if (packetID == 207)
		{
			NetGame::CSyncData* sync = reinterpret_cast<NetGame::CSyncData*>(&packet->data[1]);
			logprintf("weapon %d", sync->byteWeapon);
		}
		logprintf("Received packet id %d", packetID);
	}
	return packet;
}
