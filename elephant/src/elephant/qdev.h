#ifndef QDEV_H
#define QDEV_H

#include "gkhy/PcieDab2/PcieDab.h"

#include <QObject>
#include <memory>

class QDev : public QObject
{
public:
	explicit QDev(QObject* parent = 0);
	virtual ~QDev();

public:
	bool isEmulator() const { return m_emulator; }

protected:
	template<typename PcieDabType, unsigned short typeId>
	void tryLoadRealDev() 
	{		
		const DeviceLocation* devv = 0;
		int count  = PcieDabType::DetectedCards(&devv);

		if ( count <=0 )
			return; 

		std::auto_ptr<PcieDabType> dev(new PcieDabType(devv)); // use the first PcieDab dev detected.
		if (dev->open(*devv) == false || (dev->readReg(14 * 4) >> 4) != typeId)
		{
			dev.reset();
		}
		
		if (dev.get() != 0)
		{
			if (dev->isOpen())
				dev->close();
			
			m_pcieDab.reset(dev.release());
			m_emulator = false;
		}
	}
	
protected:
	std::auto_ptr<gkhy::PcieDab2::PcieDab> m_pcieDab;
	bool m_emulator;
};

#endif // QDEV_H
