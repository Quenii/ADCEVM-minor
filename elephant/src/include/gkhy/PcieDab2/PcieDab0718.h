#pragma once

#include "gkhy/PcieDab2/PcieDab2_global.h"
#include "gkhy/PcieDab2/PcieDab.h"

namespace gkhy
{
	namespace PcieDab2
	{
		class PCIEDAB2_API PcieDab0718 : public PcieDab
		{
			typedef void* HANDLE;

		public:
			static int DetectedCards(const DeviceLocation** devv);

		public:
			PcieDab0718(const DeviceLocation* dl = 0);
			virtual ~PcieDab0718(void);
		
		public:					
			bool isOpen() { return m_bDeviceopen; }
			bool open();
			bool open(const DeviceLocation& dev);
			void close();

			int readData(unsigned int* ppBuf, int count);
			int writeData(const unsigned int* ppBuf, int count);

			int readSglDma(unsigned int addr, unsigned int* ppBuf, int count);
			int writeSglDma(unsigned int addr, const unsigned int* ppBuf, int count);

			unsigned int readReg(int addr);
			void writeReg(int addr, unsigned int val);
		
		private:	
			HANDLE	m_hDevice;
			bool m_bDeviceopen;	
			DeviceLocation m_dl;
		};
	}
}

