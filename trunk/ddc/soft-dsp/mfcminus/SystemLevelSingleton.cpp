#include "stdafx.h"
#include "gkhy/mfcminus/SystemLevelSingleton.hpp"
#include "gkhy/mfcminus/FileInfo.hpp"
#include "gkhy/mfcminus/Win32App.hpp"
#include "gkhy/mfcplus/StringEx.hpp"
#include <afxmt.h>
#include <AtlConv.h>
#include <string>

using namespace std;
using namespace gkhy::MfcMinus;
using namespace gkhy::mfcplus;

class LockPair
{
public:
	LockPair(char* name) : mutex(FALSE, CStringEx(name)), lock(&mutex) {}
	BOOL Lock(unsigned int timeout_ms) { return lock.Lock(timeout_ms); }
	void Unlock() { lock.Unlock(); }

private:
	CMutex mutex;	
	CSingleLock lock;
};

SystemLevelSingleton::SystemLevelSingleton(char* name) :
m_lockPair(*new LockPair(name))
{	
	if (!m_lockPair.Lock(10))
	{
		string str = "Only one instance of ";
		str += name;
		str += " can exist across process boundaries. This process will terminate soon.";

		// force the system to load COMCTL32.dll.
		InitCommonControls();

		string title = string("Exception"); 
				
		MessageBoxA(GetForegroundWindow(), str.c_str(), title.c_str(), MB_OK | MB_ICONEXCLAMATION);
		exit(1);
	}	
}

SystemLevelSingleton::~SystemLevelSingleton()
{
	m_lockPair.Unlock();
	delete &m_lockPair;
}


