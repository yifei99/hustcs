#include"stdafx.h"
#include "Global.h"
#include "SRRdtSender.h"

SRRdtSender::SRRdtSender() :
	sendbase(0),
	N(WINDOW_SIZE),
	nextseqnum(0),
	full(false),
	seqrange((1 << SEQ_BIT) / WINDOW_SIZE * WINDOW_SIZE)
{
	packetWaitAck = new Packet[WINDOW_SIZE];
	flag = new int[WINDOW_SIZE];
	for (int i = 0; i < WINDOW_SIZE; i++)
	{
		flag[i] = 0;
	}
}
SRRdtSender :: ~SRRdtSender()
{
	delete[] flag;
	delete[] packetWaitAck;
}

bool SRRdtSender::getWaitingState()
{
	return full;//表示窗口已经满了
}
//当被上层调用时，检查窗口是否已满，如果窗口已满则告诉上层此时不能发送数据。
//否则将数据打包，加上序列号、校验和等标志信息，将数据包发送到网络层并且对这个数据包启动一个计时器。
//SR协议对每一个数据包都有一个专门的计时器。
bool SRRdtSender::send(Message &message)
{
	if (full)
	{
		return false;
	}
	else
	{
		packetWaitAck[nextseqnum % N].acknum = -1;
		packetWaitAck[nextseqnum % N].seqnum = nextseqnum;
		packetWaitAck[nextseqnum % N].checksum = 0;
		memcpy(packetWaitAck[nextseqnum % N].payload, message.data, sizeof(message.data));
		packetWaitAck[nextseqnum % N].checksum = pUtils->calculateCheckSum(packetWaitAck[nextseqnum % N]);

		pUtils->printPacket("发送方发送报文", packetWaitAck[nextseqnum%N]);
		pns->startTimer(SENDER, Configuration::TIME_OUT, nextseqnum);
		pns->sendToNetworkLayer(RECEIVER, packetWaitAck[nextseqnum%N]);
		nextseqnum = (nextseqnum + 1) % seqrange;
		if (nextseqnum == (sendbase + N) % seqrange)
		{
			full = true;
		}
		return true;
	}

}
//如果收到一个ACK，如果ACK未损坏并且ACK的序号在接收方传窗口内部，
//说明发送的一个包被正确的接收到了，将这个包标记为已经收到。
//如果ACK的序号和send_base相等，则把将send_base移动到下一个还未确认的序号。
//否则并不立刻滑动窗口。
void SRRdtSender::receive(Packet &ackPkt)
{
	int checksum = pUtils->calculateCheckSum(ackPkt);
	bool inwindow;
	if (sendbase <= nextseqnum)
	{
		inwindow = (sendbase <= ackPkt.acknum) && (ackPkt.acknum < nextseqnum);
	}
	else
	{
		inwindow = (ackPkt.acknum < nextseqnum) || (sendbase <= ackPkt.acknum);
	}

	if ((checksum == ackPkt.checksum) && inwindow)
	{
		pUtils->printPacket("发送方正确接收到确认信息", ackPkt);
		if (flag[ackPkt.acknum%N] == 0)
		{
			pns->stopTimer(SENDER, ackPkt.acknum);
		}
		flag[ackPkt.acknum%N] = 1;//确认收到
		if (ackPkt.acknum == sendbase)//移动窗口
		{
			while (flag[sendbase%N] == 1)
			{
				flag[sendbase%N] = 0;
				sendbase = (sendbase + 1) % seqrange;
			}
			full = false;
		}
	}
}
//如果某个包的计时器超时，就只重传这个包并且重启这个包的计时器。
void SRRdtSender::timeoutHandler(int seqNum)
{
	printf("发送方计时器超时，重发之前发过的报文\n");

	pns->stopTimer(SENDER, seqNum);
	pUtils->printPacket("发送方计时器超时，重新发送之前的报文", packetWaitAck[seqNum%N]);
	pns->startTimer(SENDER, Configuration::TIME_OUT, seqNum);
	pns->sendToNetworkLayer(RECEIVER, packetWaitAck[seqNum%N]);

}