#ifndef GBN_RDT_SENDER_H
#define GBN_RDT_SENDER_H
#include "RdtSender.h"
class GBNRdtSender :public RdtSender
{
private:
	const int N;//窗口长度
	int base;//基序号，最早未确认分组的序号
	int nextseqnum;//下一个待发分组的序号
	const int seqrange;//序号的范围
	bool full;//窗口是否满
	Packet* PacketWaitAck;
public:
	bool send(Message &message);						//发送应用层下来的Message，由NetworkService调用,如果发送方成功地将Message发送到网络层，返回true;如果因为发送方处于等待确认状态或发送窗口已满而拒绝发送Message，则返回false
	void receive(Packet &ackPkt);						//接受确认Ack，将被NetworkService调用	
	void timeoutHandler(int seqNum);					//Timeout handler，将被NetworkService调用
	bool getWaitingState();
	GBNRdtSender();
	virtual ~GBNRdtSender();
};

#endif