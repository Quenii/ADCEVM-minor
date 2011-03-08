#pragma once

#include "DataScanCore.hpp"

class DataScanCore_cul32 : public DataScanCore
{
public:
	DataScanCore_cul32(int bufferSize = 64 * 1024 * 1024) : DataScanCore(bufferSize)
	{
	}

	virtual ~DataScanCore_cul32() 
	{
		
	}
	

	UINT ThreadProc(LPVOID lpvoid, volatile bool& enabled)
	{
		_tcprintf(
			_T("\n")
			_T("***************DataScan**************\n")
			_T("This program verifies 32-bit count-up data.\n")
			_T("Start scan...Okay.\n")		
			);

		unsigned int no = 0;
		unsigned int errCnt = 0;
		unsigned int last[2];
		bool bLocked = false;
		long long lockCnt = 0;
		m_buff.chop(m_buff.count());
		while (enabled)
		{			
			// sync
			while (enabled && (!bLocked) && m_buff.count() > 0)
			{
				memmove(last, (char*)last + 1, 7);
				int read = m_buff.read((char*)last + 7, 1); assert(read == 1);

				if (last[0] + 1 == last[1])
				{
					bLocked = true;
					lockCnt ++;
					_tcprintf(_T("Locked (%I64i) @ (0x%08X, 0x%08X)\n"),
						lockCnt, last[0], last[1]);
					break;
				}
			}


			// verify
			while (enabled  && bLocked && m_buff.count() >= 4)
			{
				if (m_buff.nextReadBlockSize() < 4)  
				{
					last[0] = last[1];
					m_buff.read((char*)last + 4, 4);

					if (last[0] + 1 != last[1])
					{
						bLocked = false;					
						_tcprintf(_T("Unocked @ (0x%08X, 0x%08X)\n"),
							last[0], last[1]);
						break;
					}
				}
				else //if (m_buff.nextReadBlockSize() >= 4)
				{
					unsigned int* p = (unsigned int*)m_buff.nextReadBlock();
					int len = (m_buff.nextReadBlockSize() / 4);

					for (int i = 0; i < len; ++i)
					{
						last[0] = last[1];
						last[1] = p[i];

						if (last[0] + 1 != last[1])
						{
							bLocked = false;							
							_tcprintf(_T("Unocked @ (0x%08X, 0x%08X)\n"),
								last[0], last[1]);
							m_buff.chop( (i + 1) * 4);
							break;
						}
					}				

					m_buff.chop(len * 4);
				}	
			}		

			if (enabled && m_buff.count() < 4)
			{
				Sleep(10);
			}
		}


		_tcprintf(_T("Stop scan...Okay.\n"));

		return 0;
	}	
};