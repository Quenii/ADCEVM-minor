#include "stdafx.h"
#include "gkhy/mfcminus/Win32Service.hpp"
#include "I_ServiceBase.h"
#include <vector>
#include <assert.h>
using namespace std;

namespace gkhy
{
	namespace MfcMinus
	{
		class Win32ServicePrivate : public CI_ServiceBase
		{
		public:
			Win32ServicePrivate(Win32Service& master) : m_master(master) { }
		protected:
			void OnContinue(void) { m_master.onContinue(); }			
			void OnCustomCommand(int command) { m_master.onCustomCommand(command); }
			void OnPause(void) { m_master.onPause(); }
			bool OnPowerEvent(long pwb_status) { return m_master.onPowerEvent(pwb_status); }
			void OnShutdown(void) { m_master.onShutdown(); }
			virtual void OnStart(int argc, LPTSTR* argv)
			{
				USES_CONVERSION;
				std::vector< std:: string > args;
				for (int i = 0; i < argc; ++i)
				{
					args.push_back(T2A(argv[i]));
				}

				m_master.onStart(args); 
			}

			void OnStop(void) { m_master.onStop(); }

		private:
			Win32Service& m_master;
		};
	}
}

using namespace gkhy::MfcMinus;

Win32Service::Win32Service()
{
	m_p = new Win32ServicePrivate(*this);
}

Win32Service::~Win32Service()
{
	delete m_p;
}

bool Win32Service::install(const char* binPathName, 
								  const char* serviceName,
								  const char* displayName)
{
	SC_HANDLE schSCManager;
	SC_HANDLE schService;

	schSCManager = OpenSCManagerA(NULL,NULL,SC_MANAGER_ALL_ACCESS);
	if (schSCManager == NULL) 
		return false;
	
	schService = CreateServiceA(
		schSCManager,
		serviceName, 
		displayName, // service name to display
		SERVICE_ALL_ACCESS, // desired access 
		SERVICE_WIN32_OWN_PROCESS, // service type 		
		SERVICE_AUTO_START, //SERVICE_DEMAND_START, // start type 
		SERVICE_ERROR_NORMAL, // error control type 
		binPathName, // service's binary 
		NULL, // no load ordering group 
		NULL, // no tag identifier 
		NULL, // no dependencies
		NULL, // LocalSystem account
		NULL); // no password

	if (schService == NULL)
		return false; 

	CloseServiceHandle(schService);

	return true;

}

bool Win32Service::uninstall(const char* serviceName)
{
	SC_HANDLE schSCManager;
	SC_HANDLE hService;
	schSCManager = OpenSCManagerA(NULL,NULL,SC_MANAGER_ALL_ACCESS);

	if (schSCManager == NULL)
		return false;
	hService=OpenServiceA(schSCManager,serviceName,SERVICE_ALL_ACCESS);
	if (hService == NULL)
		return false;
	if(DeleteService(hService)==0)
		return false;
	if(CloseServiceHandle(hService)==0)
		return false;
	return true;
}

bool Win32Service::start(const char* serviceName)
{
	// run service with given name
	SC_HANDLE schSCManager = OpenSCManagerA( NULL, NULL, SC_MANAGER_ALL_ACCESS); 
	if (schSCManager==0) 
	{
		return false;
	}
	else
	{
		// open the service
		SC_HANDLE schService = OpenServiceA( schSCManager, serviceName, SERVICE_ALL_ACCESS);
		if (schService==0) 
		{
			return false;
		}
		else
		{
			// call StartService to run the service
			if(StartServiceA(schService, 0, (const char**)NULL))
			{
				CloseServiceHandle(schService); 
				CloseServiceHandle(schSCManager); 
				return TRUE;
			}
			else
			{
				assert(false);
				return false;
			}
			CloseServiceHandle(schService); 
		}
		CloseServiceHandle(schSCManager); 
	}
	return FALSE;
}

bool Win32Service::kill(const char* serviceName)
{
	// kill service with given name
	SC_HANDLE schSCManager = OpenSCManagerA( NULL, NULL, SC_MANAGER_ALL_ACCESS); 
	if (schSCManager==0) 
	{
		return false;
	}
	// open the service
	SC_HANDLE schService = OpenServiceA( schSCManager, serviceName, SERVICE_ALL_ACCESS);
	if (schService==0) 
	{
		return false;
	}
	
	// call ControlService to kill the given service
	SERVICE_STATUS status;
	if(ControlService(schService,SERVICE_CONTROL_STOP,&status))
	{
		CloseServiceHandle(schService); 
		CloseServiceHandle(schSCManager); 
		return true;
	}

	CloseServiceHandle(schService); 
	CloseServiceHandle(schSCManager); 

	return false;
}

bool Win32Service::run(Win32Service* pService) 
{ 
	return Win32ServicePrivate::Run(pService->m_p);
}

bool Win32Service::get_CanHandlePowerEvent(void)
{
	return m_p->get_CanHandlePowerEvent();
}

void Win32Service::set_CanHandlePowerEvent(bool b)
{
	m_p->set_CanHandlePowerEvent(b);
}

bool Win32Service::get_CanPauseAndContinue(void)
{
	return m_p->get_CanPauseAndContinue();
}

void Win32Service::set_CanPauseAndContinue(bool b)
{
	m_p->set_CanPauseAndContinue(b);
}

bool Win32Service::get_CanShutdown(void)
{
	return m_p->get_CanShutdown();
}

void Win32Service::set_CanShutdown(bool b)
{
	m_p->set_CanShutdown(b);
}

bool Win32Service::get_CanStop(void) 
{
	return m_p->get_CanStop();
}

void Win32Service::set_CanStop(bool b)
{
	m_p->set_CanStop(b);
}

bool Win32Service::get_ServiceName(std::string& name)
{
	USES_CONVERSION;

	vector< TCHAR > buff;
	buff.resize(1025);
	buff[buff.size() - 1] =  0;

	if(!m_p->get_ServiceName(&buff[0], int(buff.size() - 1)))
		return false;

	name = T2A(&buff[0]);

	return true;

}

void Win32Service::set_ServiceName(const char* strName)
{
	USES_CONVERSION;
	m_p->set_ServiceName(A2T(strName));
}

// void Win32Service::get_ServiceTableEntry(SERVICE_TABLE_ENTRY* ste)
// {
// 	m_p->get_ServiceTableEntry(ste);
// }

unsigned long Win32Service::get_ServiceType(void)
{
	return m_p->get_ServiceType();
}


void Win32Service::set_ServiceType(unsigned long Type)
{
	m_p->set_ServiceType(Type);
}
