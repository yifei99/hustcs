#include"stdafx.h"
#include "Global.h"
#include "TCPRdtSender.h"

TCPRdtSender::TCPRdtSender() :
	sendbase(0),
	seqrange((1 << SEQ_BIT) / WINDOW_SIZE * WINDOW_SIZE),
	nextseqnum(0),
	full(false),
	OverAck(0),
	N(WINDOW_SIZE),
	PacketWaitAck(new Packet[WINDOW_SIZE])
{
}
TCPRdtSender:: ~TCPRdtSender()
{
	delete[] PacketWaitAck;
}
bool TCPRdtSender::getWaitingState()
{
	return full;
}
//上层调用时，先检查窗口是否已满，若是满的则返回信息，告诉上层不能发送数据。
//若没满则将数据打包，加上校验和，序列号，确认号等信息。
//TCP只有一个计时器。如果发送的数据包的序列号等于sendbase则启动计时器
bool TCPRdtSender::send(Message &message)						//发送应用层下来的Message，由NetworkServiceSimulator调用,如果发送方成功地将Message发送到网络层，返回true;如果因为发送方处于等待正确确认状态而拒绝发送Message，则返回false
{
	if (full)
	{
		return false;
	}
	PacketWaitAck[nextseqnum%N].acknum = -1;
	PacketWaitAck[nextseqnum%N].seqnum = nextseqnum;
	PacketWaitAck[nextseqnum%N].checksum = 0;
	memcpy(PacketWaitAck[nextseqnum%N].payload, message.data, sizeof(message.data));
	PacketWaitAck[nextseqnum%N].checksum = pUtils->calculateCheckSum(PacketWaitAck[nextseqnum%N]);


	if (sendbase == nextseqnum)
	{
		pns->startTimer(SENDER, Configuration::TIME_OUT, 0);
	}
	pUtils->printPacket("发送方发送报文", PacketWaitAck[nextseqnum%N]);
	pns->sendToNetworkLayer(RECEIVER, PacketWaitAck[nextseqnum%N]);

	nextseqnum = (nextseqnum + 1) % seqrange;
	if (nextseqnum == (sendbase + N) % seqrange)
	{
		full = true;
	}
	return true;
}
//如果收到ACK，则比较sendbase和ACK的序号
//如果序号大于sendbase，那么则将sendbase更新为序号。
//如果当前还有未确认的报文段则需要重启计时器。
//如果收到了冗余的3个ACK此则进行快速重传。
void TCPRdtSender::receive(Packet &ackPkt)						//接受确认Ack，将被NetworkServiceSimulator调用	
{
	int checksum = pUtils->calculateCheckSum(ackPkt);
	bool inwindow;
	if (sendbase <= nextseqnum)
	{
		inwindow = (ackPkt.acknum > sendbase) && (ackPkt.acknum <= nextseqnum);
	}
	else
	{
		inwindow = (ackPkt.acknum >= sendbase) || (ackPkt.acknum <= nextseqnum);
	}

	if ((checksum == ackPkt.checksum) && (inwindow))
	{
		pUtils->printPacket("发送方正确收到接收方确认报文", ackPkt);
		sendbase = ackPkt.acknum;
		pns->stopTimer(SENDER, 0);
		OverAck = 0;
		full = false;
		if (sendbase != nextseqnum)
		{
			pns->startTimer(SENDER, Configuration::TIME_OUT, 0);
		}
	}
	else
	{
		if ((checksum == ackPkt.checksum) && (!inwindow))
		{
			OverAck++;
			if (OverAck == 3)
			{
				OverAck = 0;
				pUtils->printPacket("快速重传", PacketWaitAck[sendbase%N]);
				pns->stopTimer(SENDER, 0);
				pns->startTimer(SENDER, Configuration::TIME_OUT, 0);
				pns->sendToNetworkLayer(RECEIVER, PacketWaitAck[sendbase%N]);
			}
		}
	}
}
//超时时，TCP重传引起超时的数据包并且重置计时器
void TCPRdtSender::timeoutHandler(int seqNum)
{
	printf("发送方计时器超时，重新发送之前发送的报文\n");
	pns->stopTimer(SENDER, 0);
	pUtils->printPacket("发送方计时器超时，重发之前的报文", PacketWaitAck[sendbase%N]);
	pns->sendToNetworkLayer(RECEIVER, PacketWaitAck[sendbase%N]);
	pns->startTimer(SENDER, Configuration::TIME_OUT, 0);
}