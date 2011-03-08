#ifndef QZebraScopeSerializer_H
#define QZebraScopeSerializer_H

#include "AdcBoardTypes.hpp"

#include <QFile>
#include <vector>

class QZebraScopeSerializer : public QFile
{
	Q_OBJECT

public:
	QZebraScopeSerializer(const QString &name, QObject *parent = 0);
	~QZebraScopeSerializer();

public:
	void serialize(const PowerStatus& data);
	bool deserialize(PowerStatus& data);

	void serialize(const TimeDomainReport& data);
	bool deserialize(TimeDomainReport& data);

	void serialize(const FreqDomainReport& data);
	bool deserialize(FreqDomainReport& data);

	void serialize(const AdcBoardReport& data);
	bool deserialize(AdcBoardReport& data);

	template<typename T>
	void serialize(const T& data) 
	{ 
		write((const char*)&data, sizeof(T)); 
	}

	template<typename T>
	bool deserialize(T& data) 
	{
		if (bytesAvailable() < sizeof(T))
			return false;
		read((char*)&data, sizeof(T)); 

		return true;
	}

	template<typename T>
	void serialize(const std::vector<T> data)
	{
		serialize<qint64>(data.size());
		if (data.size() > 0)
		{
			write((const char*)&data[0], data.size() * sizeof(T));
		}
	}

	template<typename T>
	bool deserialize(std::vector<T> data)
	{		
		qint64 size = 0;
		if (!deserialize<qint64>(size))
			return false;

		data.resize(size);		
		if (data.size() > 0)
		{
			if (bytesAvailable() < data.size() * sizeof(T))
				return false;

			read((char*)&data[0], data.size() * sizeof(T));
		}

		return true;
	}

private:
	
};

#endif // QZebraScopeSerializer_H
