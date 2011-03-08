#pragma once

#include "gkhy/PcieDab2/PcieDab2_global.h"

namespace gkhy
{
	namespace PcieDab2
	{
		struct DeviceLocation 
		{
			unsigned char  BusNumber;
			unsigned char SlotNumber;
			unsigned short DeviceId;
			unsigned short VendorId;
			char SerialNumber[20];
		};


		class PCIEDAB2_API PcieDab
		{
		
		public:
			PcieDab(void);
			virtual ~PcieDab(void);

		public:
			// virtual unsigned short deviceId() = 0;

			virtual bool isOpen() = 0; 
			
			virtual bool open() = 0;
			virtual void close() = 0;

			virtual int readData(unsigned int* ppBuf, int count) = 0;
			virtual int writeData(const unsigned int* ppBuf, int count) = 0;

			virtual int readSglDma(unsigned int addr, unsigned int* ppBuf, int count) = 0;
			virtual int writeSglDma(unsigned int addr, const unsigned int* ppBuf, int count) = 0;

			virtual unsigned int readReg(int addr) = 0;
			virtual void writeReg(int addr, unsigned int val) = 0;
		};

	}
}