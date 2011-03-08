#pragma once

#include <QString>
#include <vector>
#include <QMetaType>
#include <QSettings>
#include <QFile>


 #define MATLAB 1

struct AdcBoardInfo 
{
	int usbAddr;
	QString devName;
	QString infName;
};

enum AdcCoding 
{
	AdcCodingOffset = 0,
	AdcCodingComplement = 1,
	AdcCodingGray = 2		
};

inline QString conv_to_string(const AdcCoding& e) 
{
	switch (e)
	{
	case AdcCodingOffset:
		return "Offset";
	case AdcCodingComplement:
		return "Complement";
	case AdcCodingGray:
		return "Gray";
	default:
		return "";
	}
}


struct AdcSettings
{
	QString adcType;
	float va;
	float vd;
	unsigned int bitcount;
	float vpp;
	AdcCoding coding;
	float phase;

	AdcSettings()
	{
		adcType = "JAD14P1";
		va = 1.8f;
		vd = 1.8f;  
		bitcount = 16;
		vpp = .72f;
		coding = AdcCodingComplement;
		phase = 0;
	}

	void writeSettings(QSettings& settings) const
	{
		settings.beginGroup("AdcSettings");

		settings.setValue("Adc Type", adcType);
		settings.setValue("Va", va);
		settings.setValue("Vd", vd);
		settings.setValue("Bit Count", bitcount);
		settings.setValue("Vpp", vpp);
		settings.setValue("Coding", (int)coding);
		settings.setValue("Phase", phase);

		settings.endGroup();
	}

	void readSettings(QSettings& settings)
	{
		settings.beginGroup("AdcSettings");

		adcType = settings.value("Adc Type", adcType).toString();
		va = settings.value("Va", va).toString().toFloat();
		vd = settings.value("Vd", vd).toString().toFloat();
		bitcount = settings.value("Bit Count", bitcount).toString().toFloat();
		vpp = settings.value("Vpp", vpp).toString().toFloat();
		coding = (AdcCoding) settings.value("Coding", (int)coding).toInt();
		phase = settings.value("Phase", phase).toString().toFloat();

		settings.endGroup();

	}
};

struct SignalSettings
{
	float clockFreq;
	float signalFreq;
	float signalPower;

	SignalSettings()
	{
		clockFreq = 100.0e6;
		signalFreq = 1.0e6;
		signalPower = -10; //dBm
	}

	void writeSettings(QSettings& settings) const
	{
		settings.beginGroup("SignalSettings");

		settings.setValue("Clock Freq", clockFreq);
		settings.setValue("Signal Freq", signalFreq);
		settings.setValue("Signal Power", signalPower);

		settings.endGroup();
	}

	void readSettings(QSettings& settings)
	{
		settings.beginGroup("SignalSettings");

		clockFreq = settings.value("Clock Freq", clockFreq).toString().toFloat();
		signalFreq = settings.value("Signal Freq", signalFreq).toString().toFloat();
		signalPower = settings.value("Signal Power", signalPower).toString().toFloat();

		settings.endGroup();
	}
};

struct PowerStatus
{
	float va;
	float vd;
	float ia;
	float id;
	float power;
};


struct TimeDomainReport
{
	std::vector<float> samples;
	std::vector<float> xaxis;
	std::vector<unsigned short> rawSamples;
	float min;
	float max;	
};


struct FreqDomainReport
{
	std::vector<float> Spectrum;
	std::vector<float> xaxis;
	float A;
	float AdB;
	float SINAD;
	float SNR;
	float THD;
	float SFDR;
	float ENOB;
	std::vector<float> HD;
};

struct AdcBoardReport
{
	PowerStatus powerStatus;
	FreqDomainReport fdReport;
	TimeDomainReport tdReport;
};