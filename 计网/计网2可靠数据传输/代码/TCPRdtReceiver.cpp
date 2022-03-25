#include "stdafx.h"
#include "Global.h"
#include "TCPRdtReceiver.h"

TCPRdtReceiver::TCPRdtReceiver() :
	ExpectNextNum(0),
	seqrange((1 << SEQ_BIT) / WINDOW_SIZE * WINDOW_SIZE)
{
	lastAckPacket.acknum = 0;
	lastAckPacket.seqnum = -1;
	lastAckPacket.checksum = 0;
	for (int i = 0; i < Configuration::PAYLOAD_SIZE; i++)
	{
		lastAckPacket.payload[i] = '.';
	}
	lastAckPacket.checksum = pUtils->calculateCheckSum(lastAckPacket);
}

TCPRdtReceiver:: ~TCPRdtReceiver()
{
}

void TCPRdtReceiver::receive(Packet &packet)	//接收报文，将被NetworkService调用
{
	int checksum = pUtils->calculateCheckSum(packet);
	if ((checksum == packet.checksum) && (packet.seqnum == ExpectNextNum))
	{
		pUtils->printPacket("接收方正确接收到发送方的报文", packet);
		ExpectNextNum = (ExpectNextNum + 1) % seqrange;
		//取出message交给应用层
		Message msg;
		memcpy(msg.data, packet.payload, sizeof(packet.payload));
		pns->delivertoAppLayer(RECEIVER, msg);
		lastAckPacket.acknum = ExpectNextNum;
		lastAckPacket.checksum = pUtils->calculateCheckSum(lastAckPacket);
		pUtils->printPacket("接受方发送确认报文", lastAckPacket);
		pns->sendToNetworkLayer(SENDER, lastAckPacket);
	}
	else
	{
		if (checksum != packet.checksum)
		{
			pUtils->printPacket("接收方没有正确收到发送方的数据，数据损坏", packet);
		}
		else
		{
			pUtils->printPacket("接收方没有正确收到发送方的数据，报文顺序错误", packet);
		}
		pUtils->printPacket("接受方发送上一次的确认报文", lastAckPacket);
		pns->sendToNetworkLayer(SENDER, lastAckPacket);
	}
}
