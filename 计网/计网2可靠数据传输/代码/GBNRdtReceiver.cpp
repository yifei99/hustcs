#include "stdafx.h"
#include "Global.h"
#include "GBNRdtReceiver.h"

GBNRdtReceiver::GBNRdtReceiver() :expectedseqnum(0), seqrange((1 << SEQ_BIT) / WINDOW_SIZE * WINDOW_SIZE)
{
	int i;
	lastAckPacket.seqnum = -1;
	lastAckPacket.acknum = -1;
	lastAckPacket.checksum = 0;
	for (i = 0; i < Configuration::PAYLOAD_SIZE; i++)
	{
		lastAckPacket.payload[i] = '.';
	}
	lastAckPacket.checksum = pUtils->calculateCheckSum(lastAckPacket);
}
GBNRdtReceiver:: ~GBNRdtReceiver()
{
}
//接受方有一个期望下一个收到的包的序号expectedseqnum
//当接受方接收到一个数据包，如果数据包没有损坏，并且数据包的序号和ExpectNextPacketNum相等的话，
//接收方就将数据传递给上层，发送一个为expectedseqnum的ACK，
//然后将expectedsequm加一，等待下一个包的到来。其他情况就丢掉包。
void GBNRdtReceiver::receive(Packet &packet)
{
	int checksum = pUtils->calculateCheckSum(packet);
	if ((checksum == packet.checksum) && (packet.seqnum == expectedseqnum))
	{
		pUtils->printPacket("接收方正确接收到发送方的报文", packet);
		Message msg;
		memcpy(msg.data, packet.payload, sizeof(packet.payload));
		pns->delivertoAppLayer(RECEIVER, msg);

		lastAckPacket.acknum = packet.seqnum;
		lastAckPacket.checksum = pUtils->calculateCheckSum(lastAckPacket);
		pUtils->printPacket("接收方发送确认报文", lastAckPacket);
		pns->sendToNetworkLayer(SENDER, lastAckPacket);
		expectedseqnum = (expectedseqnum + 1) % seqrange;
	}
	else
	{
		if (checksum != packet.checksum)
		{
			pUtils->printPacket("接收方没有正确收到发送方的报文，数据校验错误", packet);
		}
		else
		{
			pUtils->printPacket("接收方没有正确收到发送方的报文，报文序号错误", packet);
		}
		pUtils->printPacket("接收方继续发送上次的确认报文", lastAckPacket);
		pns->sendToNetworkLayer(SENDER, lastAckPacket);
	}


}