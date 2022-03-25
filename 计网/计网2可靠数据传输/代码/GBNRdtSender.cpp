#include "stdafx.h"
#include "Global.h"
#include "GBNRdtSender.h"

GBNRdtSender::GBNRdtSender() :
	N(WINDOW_SIZE),
	base(0),
	nextseqnum(0),
	PacketWaitAck(new Packet[WINDOW_SIZE]),
	full(false),
	seqrange((1 << SEQ_BIT) / WINDOW_SIZE * WINDOW_SIZE)
{
}

GBNRdtSender::~GBNRdtSender()
{
	delete[] PacketWaitAck;
}
//当有上层的调用时，GBN协议先检验窗口是否已满，如果已满则告诉上层测试不能发送数据
//如果没满则将上层传递过来的数据打包，给数据包加上序列号和其他标志信息，并传送到网络层。
//GBN协议只对send_base一个分组进行计时，当发送分组的序号等于send_base时就启动计时器，否则不启动计时器。
bool GBNRdtSender::send(Message &message)//发送应用层下来的Message，由NetworkService调用,如果发送方成功地将Message发送到网络层，返回true;如果因为发送方处于等待确认状态或发送窗口已满而拒绝发送Message，则返回false
{
	if (full)
	{
		return false;
	}
	else
	{
		PacketWaitAck[nextseqnum%N].seqnum = nextseqnum;
		PacketWaitAck[nextseqnum % N].acknum = -1;
		PacketWaitAck[nextseqnum%N].checksum = 0;
		memcpy(PacketWaitAck[nextseqnum%N].payload, message.data, sizeof(message.data));
		PacketWaitAck[nextseqnum%N].checksum = pUtils->calculateCheckSum(PacketWaitAck[nextseqnum%N]);
		pUtils->printPacket("发送方发送报文", PacketWaitAck[nextseqnum%N]);
		if (base == nextseqnum)
		{
			pns->startTimer(SENDER, Configuration::TIME_OUT, base);
		}
		pns->sendToNetworkLayer(RECEIVER, PacketWaitAck[nextseqnum%N]);
		nextseqnum = (nextseqnum + 1) % seqrange;
		if (nextseqnum == ((base + N) % seqrange))//发送之后窗口满了
		{
			full = true;
		}
		return true;
	}
}
//收到一个ACK，如果收到的是ACK未损坏并且当ACk的是send_base，那么就要将窗口向前滑动，更新send_base，并且重置计时器
void GBNRdtSender::receive(Packet &ackPkt)//接受确认Ack，将被NetworkService调用	
{
	int checksum = pUtils->calculateCheckSum(ackPkt);
	bool ackinwindows;//收到的ack序号是否在窗口中
	if (base <= nextseqnum)
	{
		ackinwindows = (base <= ackPkt.acknum) && (ackPkt.acknum < nextseqnum);
	}
	else
	{
		ackinwindows = (ackPkt.acknum < nextseqnum) || (ackPkt.acknum >= base);
	}

	if (checksum == ackPkt.checksum && ackinwindows)
	{
		int bases = base;
		if ((ackPkt.acknum + 1) % seqrange != base)//如果相等说明是收到的上一个包的ack
		{
			pUtils->printPacket("接收到方正确收到确认", ackPkt);
			base = (ackPkt.acknum + 1) % seqrange;//滑动窗口
			full = false;
		}
		if (base == nextseqnum)//发送完毕
		{
			pns->stopTimer(SENDER, bases);//停止计时器
		}
		else//重启计时器
		{
			pns->stopTimer(SENDER, bases);
			pns->startTimer(SENDER, Configuration::TIME_OUT, base);
		}
	}


}
//发生超时时。就把[send_base,next_seqnum-1]范围内的所有数据包重新发送一遍。
//PacketWaitAck用来存储已经发送但是没被确认的数据包
void GBNRdtSender::timeoutHandler(int seqNum)			//Timeout handler，将被NetworkService调用
{
	int i;
	printf("发送方计时器超时，重发之前发送的报文\n");
	pns->stopTimer(SENDER, base);
	pns->startTimer(SENDER, Configuration::TIME_OUT, base);
	if (base <= nextseqnum)
	{
		for (i = base; i < nextseqnum; i++)
		{
			pUtils->printPacket("发送方计时器时间到，重新发送之前的报文", PacketWaitAck[i%N]);
			pns->sendToNetworkLayer(RECEIVER, PacketWaitAck[i%N]);
		}
	}
	else
	{
		for (i = base; i < seqrange; i++)
		{
			pUtils->printPacket("发送方计时器时间到，重新发送之前的报文", PacketWaitAck[i%N]);
			pns->sendToNetworkLayer(RECEIVER, PacketWaitAck[i%N]);
		}
		for (i = 0; i < nextseqnum; i++)
		{
			pUtils->printPacket("发送方计时器时间到，重新发送之前的报文", PacketWaitAck[i%N]);
			pns->sendToNetworkLayer(RECEIVER, PacketWaitAck[i%N]);
		}
	}

}
bool GBNRdtSender::getWaitingState()
{
	return full;

}
