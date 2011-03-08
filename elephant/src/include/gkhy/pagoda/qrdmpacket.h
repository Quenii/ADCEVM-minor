#ifndef QRDMPACKET_H
#define QRDMPACKET_H

#include "gkhy/pagoda/pagoda_global.h"

#include <QObject>

namespace gkhy
{
	namespace pagoda
	{
		class QRdmPeer;

		class PAGODA_EXPORT QRdmPacket : public QObject
		{
		public:
			enum PacketType
			{
				ConfigPacket,
				StatusPacket,
				CommandPacket,
			};
			struct Preamble
			{ 
				int sop;
				int size;
				int id;
			};

		public:
			static int identifyPreamble(const char* buf, int bufSize, int* len = 0);
		public:
			QRdmPacket(QObject* parent);
			virtual ~QRdmPacket() {}
		private:
			Q_DISABLE_COPY(QRdmPacket)

		public:
			virtual int verfify(const char* buf, int bufSize) const = 0;
			virtual PacketType type() const = 0; 
			virtual unsigned char packetId() const = 0;
			virtual int packetSize() const = 0;			
			virtual char* packetAddr() const = 0;

			virtual int preambleSize() = 0;	

			virtual int setLocal() const { return 0; }
			virtual int getLocal() { return 0; }

			// return value: 1 - ok, 0 - buffer full, -1 - error.
			virtual int send(QRdmPeer& rdmPeer) const;
		
			// return value: 1 - ok, 0 - packet no recognized, -1 - error.
			virtual int recv(QRdmPeer& rdmPeer);		

		protected:
			virtual void on_GotPacket()  {}

		protected:
			static const int SOP;	 
			static const int EOP;
		};

		template <typename PAYLOAD_TYPE, int PACKET_ID, QRdmPacket::PacketType PACKET_TYPE>
		class QRdmPacketTemplate : public QRdmPacket
		{
		public: 
			struct PacketData
			{
				Preamble preamble;
				PAYLOAD_TYPE   payload;	
				int eop;
			};		

		public:
			QRdmPacketTemplate(QObject* parent) 
				: QRdmPacket(parent) 
			{
				m_packetData.preamble.sop = SOP;
				m_packetData.preamble.size = packetSize();
				m_packetData.preamble.id = packetId();
				m_packetData.eop = EOP;
			}
		private:			
			Q_DISABLE_COPY(QRdmPacketTemplate)

		public:				
			int verfify(const char* buf, int bufSize) const
			{
				if (bufSize < sizeof(PacketData))
				{					
					return 0;
				}

				const PacketData* temp = (const PacketData*)buf;
				if (temp->preamble.sop != QRdmPacket::SOP || 
					temp->preamble.size != sizeof(PacketData) || 
					temp->eop != QRdmPacket::EOP)
				{
					Q_ASSERT(false);
					return  -1;
				}

				return 1;
			}

			PacketType type() const { return PACKET_TYPE; }
			unsigned char packetId() const { Q_ASSERT(PACKET_ID > 0); return PACKET_ID; }
			int packetSize() const { return sizeof(m_packetData); }
			char* packetAddr() const { return (char*)&m_packetData; }

			int preambleSize() { return sizeof(Preamble); }

			PAYLOAD_TYPE& payload() { return m_packetData.payload; }
			const PAYLOAD_TYPE& payload() const { return m_packetData.payload; }
		
		private:
			PacketData  m_packetData;	
		};
	}
}

#endif // QRDMPACKET_H
