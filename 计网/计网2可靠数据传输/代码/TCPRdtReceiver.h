#ifndef TCP_RECEIVER_H
#define TCP_RECEIVER_H
#include "RdtReceiver.h"
class TCPRdtReceiver :public RdtReceiver
{

	int ExpectNextNum;
	Packet lastAckPacket;
	const int seqrange;
public:
	TCPRdtReceiver();
	virtual ~TCPRdtReceiver();

public:

	void receive(Packet &packet);	//接收报文，将被NetworkService调用
};

#endif

