#pragma once

#include "gkhy/PcieDab2/PcieDab2_global.h"
#include "gkhy/PcieDab2/PcieDab.h"
#include <string.h>

namespace gkhy
{
	namespace PcieDab2
	{
		class PCIEDAB2_API PcieDabEmulator : public PcieDab
		{
		public:
			PcieDabEmulator(void);
			~PcieDabEmulator(void);

		public:
			/*unsigned short deviceId()
			{
				return 0x00;
			}*/

			bool isOpen() { return m_open; }

			bool open()
			{
				if (m_open)
					return false;

				m_counter = 0;
				m_open = true;

				return true;
			}

			void close()
			{
				m_open  = false;
			}

			int readData(unsigned int* ppBuf, int count)
			{
				return readSglDma(0, ppBuf, count);
			}

			int writeData(const unsigned int* ppBuf, int count)
			{
				return count;
			}

			int readSglDma(unsigned int addr, unsigned int* ppBuf, int count)
			{
				for (int i = 0; i < count; ++i)
				{
					ppBuf[i] = m_counter++;
				}

				return count;
			}

			int writeSglDma(unsigned int addr, const unsigned int* ppBuf, int count)
			{
				return count;
			}

			unsigned int readReg(int addr)
			{
				return 0;
			}

			void writeReg(int addr, unsigned int val)
			{

			}

		private:
			bool m_open;
			unsigned int m_counter;
		};

	}
}
