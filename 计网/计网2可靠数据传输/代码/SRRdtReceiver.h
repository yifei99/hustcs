#ifndef SR_RDT_RECEIVER_H
#define SR_RDT_RECEIVER_H
#include "RdtReceiver.h"
class SRRdtReceiver : public RdtReceiver
{
	int rcvbase;//下一个希望收到的报文编号
	const int N;
	const int seqrange;
	Packet lastAckPacket;
	Packet* const PacketReceived;//存储窗口中已经收到的packet
	int* const flag;//标识packetReceived数组中是否是有效的

	bool inwindow(int num);
	bool oldpacket(int num);

public:
	SRRdtReceiver();
	virtual ~SRRdtReceiver();
	void receive(Packet &packet);
};

#endif


