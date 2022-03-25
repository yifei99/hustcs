#include "stdafx.h"
#include "Global.h"
#include "SRRdtReceiver.h"

SRRdtReceiver::SRRdtReceiver() :
	rcvbase(0),
	N(WINDOW_SIZE),
	seqrange((1 << SEQ_BIT) / WINDOW_SIZE * WINDOW_SIZE),
	PacketReceived(new Packet[WINDOW_SIZE]),
	flag(new int[WINDOW_SIZE])
{
	lastAckPacket.acknum = -1;
	lastAckPacket.seqnum = -1;
	lastAckPacket.checksum = 0;
	int i;
	for (i = 0; i < WINDOW_SIZE; i++)
	{
		flag[i] = 0;
	}
	for (i = 0; i < Configuration::PAYLOAD_SIZE; i++)
	{
		lastAckPacket.payload[i] = '.';
	}
	lastAckPacket.checksum = pUtils->calculateCheckSum(lastAckPacket);
}
SRRdtReceiver:: ~SRRdtReceiver()
{
	delete[] flag;
	delete[] PacketReceived;
}

bool SRRdtReceiver::inwindow(int num)//是否在窗口内
{

	return (rcvbase <= num && num < rcvbase + N) ||
		(rcvbase - seqrange <= num && num < rcvbase - seqrange + N);
}

bool SRRdtReceiver::oldpacket(int num)
{
	return (rcvbase - N <= num && num < rcvbase) ||
		(rcvbase + seqrange - N <= num && num < rcvbase + seqrange);

}


void SRRdtReceiver::receive(Packet &packet)
{
	int checksum = pUtils->calculateCheckSum(packet);
	if (checksum == packet.checksum)
	{
		if (inwindow(packet.seqnum))
		{
			pUtils->printPacket("接收方正确收到发送方的报文", packet);
			lastAckPacket.acknum = packet.seqnum;
			lastAckPacket.checksum = pUtils->calculateCheckSum(lastAckPacket);
			pUtils->printPacket("接收方发送确认报文", lastAckPacket);
			pns->sendToNetworkLayer(SENDER, lastAckPacket);
			if (!flag[packet.seqnum%N])//以前没有收到过这个包
			{
				flag[packet.seqnum%N] = 1;
				PacketReceived[packet.seqnum%N] = packet;
			}
			if (packet.seqnum == rcvbase)//接收到可以传递到应用层的数据了
			{
				Message msg;
				while (flag[rcvbase%N])
				{
					memcpy(msg.data, PacketReceived[rcvbase%N].payload, sizeof(PacketReceived[rcvbase%N].payload));
					pns->delivertoAppLayer(RECEIVER, msg);
					flag[rcvbase%N] = 0;
					rcvbase = (rcvbase + 1) % seqrange;
				}
			}

		}
		else
		{
			if (oldpacket(packet.seqnum))
			{
				pUtils->printPacket("接收方正确接收到发送方的报文", packet);
				lastAckPacket.acknum = packet.seqnum;
				lastAckPacket.checksum = pUtils->calculateCheckSum(lastAckPacket);
				pUtils->printPacket("发送方发送确认报文", lastAckPacket);
				pns->sendToNetworkLayer(SENDER, lastAckPacket);
			}
		}

	}
	else
	{

		pUtils->printPacket("接收方没有正确接收到发送方发送的报文，报文数据损坏", packet);
	}

}