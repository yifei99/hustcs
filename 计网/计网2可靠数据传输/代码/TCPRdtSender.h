#ifndef TCP_SENDER_H
#define TCP_SENDER_H
#include "RdtSender.h"
class TCPRdtSender :public RdtSender
{
private:
	int sendbase;
	const int N;
	const int seqrange;
	int nextseqnum;
	bool full;
	Packet* PacketWaitAck;
	int OverAck;//记录冗余ACK
public:

	bool getWaitingState();
	bool send(Message &message);						//发送应用层下来的Message，由NetworkServiceSimulator调用,如果发送方成功地将Message发送到网络层，返回true;如果因为发送方处于等待正确确认状态而拒绝发送Message，则返回false
	void receive(Packet &ackPkt);						//接受确认Ack，将被NetworkServiceSimulator调用	
	void timeoutHandler(int seqNum);					//Timeout handler，将被NetworkServiceSimulator调用

public:
	TCPRdtSender();
	virtual ~TCPRdtSender();
};

#endif

