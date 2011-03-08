#pragma once

#include "DataScanCore.hpp"
#include <vector>


#define  GET_PACKCNT(buf) 	\
( \
	  (unsigned int(((unsigned char*)(buf))[2]) << 16) | \
		   (unsigned int(((unsigned char*)(buf))[1]) << 8) | \
		   unsigned int(*((unsigned char*)(buf)))  \
)
 

class DataScanCore_1279Pack_cul32 : public DataScanCore
{
public:
	DataScanCore_1279Pack_cul32(int bufferSize = 64 * 1024 * 1024) : DataScanCore(bufferSize)
	{
	}

	virtual ~DataScanCore_1279Pack_cul32() 
	{

	}


	UINT ThreadProc(LPVOID lpvoid, volatile bool& enabled)
	{
		_tcprintf(
			_T("\n")
			_T("***************DataScan**************\n")
			_T("This program verifies 1279 bytes long CCSDS pack with 32-bit count-up data.\n")
			_T("Start scan...Okay.\n"));

		m_buff.chop(m_buff.count());

		std::vector<char> buff(1275);
		bool bLocked = false;		
		unsigned int packCnt = 0;
		unsigned int lastPackCnt = 0;

		while (enabled)
		{	
			// sync
			if (!bLocked)
			{
				if (m_buff.count() < 4)	
				{
					Sleep(10);
					continue;
				}

				while (m_buff.count() >= 4)
				{
					m_buff.read(&buff[0], 1);
					if (unsigned char(buff[0]) != 0x1a) continue;

					m_buff.read(&buff[0], 1);
					if (unsigned char(buff[0]) != 0xcf) continue;

					m_buff.read(&buff[0], 1);
					if (unsigned char(buff[0]) != 0xfc) continue;

					m_buff.read(&buff[0], 1);
					if (unsigned char(buff[0]) != 0x1d) continue;					

					bLocked = true;
					break;
				}
			}
			

			// verify
			if (bLocked)
			{
				if (m_buff.count() < 1275)
				{
					Sleep(10);
					continue;
				}

				m_buff.read(&buff[0], 1275);

				lastPackCnt = packCnt;
				packCnt = GET_PACKCNT(&buff[0]);
				if (((lastPackCnt + 1) & 0xFFFFFF) != packCnt)
				{
					_tcprintf(_T("PackCnt Err(last: 0x%08X, this: 0x%08X)\n"), 
						lastPackCnt, packCnt);
				}

				unsigned int* pCnt = (unsigned int*)&buff[3];
				for (int i = 1; i < 1272 / 4; ++i)
				{
					if (pCnt[i-1] + 1 != pCnt[i])
					{
						_tcprintf(_T("Cnt Err(PackCnt: 0x%08X, last: 0x%08X, this: 0x%08X)\n"),
							packCnt, pCnt[i-1], pCnt[i]);
						break;
					}
				}

				bLocked = false;
			}					
		}

		_tcprintf(_T("Stop scan...Okay.\n"));

		return 0;
	}	
};