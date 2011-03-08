#include "PcieDab0718.h"
#include "PlxApi.h"

#include <assert.h>
#include <windows.h>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

using namespace std;
using namespace gkhy::PcieDab2;

template <typename T>
static inline const T &qMin(const T &a, const T &b) { if (a < b) return a; return b; }
template <typename T>
static inline const T &qMax(const T &a, const T &b) { if (a < b) return b; return a; }

int PcieDab0718::DetectedCards(const DeviceLocation** devv)
{	
	static std::vector<DeviceLocation> dev;
	static bool inited = false;
	if (!inited)
	{
		U32 devNumber = 0; 
		RETURN_CODE rc;
		DEVICE_LOCATION device;

		while (true)
		{
			device.BusNumber = PCI_FIELD_IGNORE;// PCI_FIELD_IGNORE;
			device.SlotNumber = PCI_FIELD_IGNORE; //PCI_FIELD_IGNORE;
			device.VendorId = PCI_FIELD_IGNORE;
			device.DeviceId = 0x0718; // PCI_FIELD_IGNORE; 
			device.SerialNumber[0] = '\0';

			rc = PlxPciDeviceFind(&device, &devNumber);
			if (rc != ApiSuccess)
			{		
				break; // detection finished, get out of loop
			}	
			++devNumber;

			DeviceLocation dl;
			dl.BusNumber = device.BusNumber;
			dl.SlotNumber = device.SlotNumber;
			dl.VendorId = device.VendorId;
			dl.DeviceId = device.DeviceId;
			memcpy(dl.SerialNumber, device.SerialNumber, sizeof(dl.SerialNumber));

			dev.push_back(dl);
		}	

		inited = true;
	}

	*devv = (dev.size() > 0) ? &dev[0] : 0;

	return int(dev.size());
}

PcieDab0718::PcieDab0718(const DeviceLocation* dl /* = 0 */) 
{
	if (dl)
		m_dl = *dl;
	else
		memset(&m_dl, 0, sizeof(m_dl));
	
	m_bDeviceopen = false;
}

PcieDab0718::~PcieDab0718(void)
{
	close();
}

bool PcieDab0718::open()
{
	if (m_bDeviceopen)
	{
		assert(false);
		return false;
	}

	// cout << "open" << endl;

	DEVICE_LOCATION card;
	card.BusNumber = m_dl.BusNumber;
	card.SlotNumber = m_dl.SlotNumber;
	card.VendorId = m_dl.VendorId;
	card.DeviceId = m_dl.DeviceId;
	memcpy(card.SerialNumber, m_dl.SerialNumber, sizeof(card.SerialNumber));

	RETURN_CODE rc;
	rc = PlxPciDeviceOpen(&card, &m_hDevice);
	if (rc != ApiSuccess)
		return false;


	DMA_CHANNEL_DESC dmaDesc;
	// Clear DMA structure
	memset(&dmaDesc, 0, sizeof(DMA_CHANNEL_DESC));
	// Initialize the DMA channel
	dmaDesc.EnableReadyInput		= 1;
	dmaDesc.EnableBTERMInput		= 1;
	dmaDesc.DmaStopTransferMode		= AssertBLAST;
	dmaDesc.EnableIopBurst			= 1;
	dmaDesc.DmaChannelPriority		= Rotational;
	dmaDesc.IopBusWidth				= 3;  // 32-bit
	dmaDesc.HoldIopAddrConst		= 1;

	rc = PlxDmaSglChannelOpen(m_hDevice, PrimaryPciChannel0, &dmaDesc);
	if (rc != ApiSuccess)	
		return false;

	rc = PlxDmaSglChannelOpen(m_hDevice, PrimaryPciChannel1, &dmaDesc);
	if (rc != ApiSuccess)	
		return false;

	PlxPciBoardReset(m_hDevice);

	m_bDeviceopen = true;

	return true;
}

bool PcieDab0718::open(const DeviceLocation& dev)
{	
	if (m_bDeviceopen)
	{ 		
		assert(false);
		return false;
	}

	m_dl = dev;

	return open();	
}

void PcieDab0718::close()
{
	// cout << "close" << endl;

	if (m_bDeviceopen)
	{
		RETURN_CODE rc;

		PlxDmaSglChannelClose(m_hDevice, PrimaryPciChannel0);
		PlxDmaSglChannelClose(m_hDevice, PrimaryPciChannel1);

		rc = PlxPciDeviceClose(m_hDevice);
		assert(rc == ApiSuccess);

		m_bDeviceopen = false;
	}
}

int PcieDab0718::readSglDma(unsigned int addr, unsigned int* buf, int count/* = 512 * 1024 */)
{	
	assert(m_bDeviceopen);

	if (count < 0 ) 
		return -1;

	if (count == 0)
		return 0;
	
	RETURN_CODE rc;

	DMA_TRANSFER_ELEMENT dma;
	memset(&dma, 0, sizeof(dma));
	dma.u.UserVa		= U64(buf);
	dma.LocalAddr		= addr;
	dma.TransferCount	= count * 4;
	dma.LocalToPciDma	= 1;	
	
	rc = PlxDmaSglTransfer(m_hDevice, PrimaryPciChannel1, &dma, false); 	
	if (rc != ApiSuccess)
		return -1;
	
	return count;
}


int PcieDab0718::writeSglDma(unsigned int addr, const unsigned int* buf, int count)
{	
	assert(m_bDeviceopen);

	if (count < 0)
		return -1;
	
	if (count == 0)
		return 0;
	
	RETURN_CODE rc;
	DMA_TRANSFER_ELEMENT dma;
	memset(&dma, 0, sizeof(dma));
	dma.u.UserVa		= U64(buf);
	dma.LocalAddr		= addr;
	dma.TransferCount	= count * 4;
	dma.LocalToPciDma	= 0;
	
	rc = PlxDmaSglTransfer(m_hDevice, PrimaryPciChannel0, &dma, false); 	
	if (rc != ApiSuccess)
		return -1;

	return count;
}

unsigned int PcieDab0718::readReg(int addr)
{
	assert(m_bDeviceopen);

	unsigned int val;
	if (PlxBusIopRead(m_hDevice, IopSpace0, addr, true, &val, sizeof(val), BitSize32) != ApiSuccess)
	{
		assert(false); // return false;
		return 0;
	}
	else
	{
		return val;
	}
	//	return true;
}

void PcieDab0718::writeReg(int addr, unsigned int val)
{		
	assert(m_bDeviceopen);

	if (PlxBusIopWrite(m_hDevice, IopSpace0, addr, true, &val, sizeof(val), BitSize32) != ApiSuccess)
	 assert(false); //	return false;
	//else
	//	return true;
}	

int PcieDab0718::readData(unsigned int* ppBuf, int count)
{
	unsigned int available = readReg(50 * 4);
	int toRead = qMin(count, int(available));		
	int read = readSglDma(51 * 4, ppBuf, toRead);
	return read;
}

int PcieDab0718::writeData(const unsigned int* ppBuf, int count)
{
	unsigned int space = readReg(0 * 4);
	int toWrite = qMin(count, int(space));		
	int written = writeSglDma(1 * 4, ppBuf, toWrite);
	return written;
}

