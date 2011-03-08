#include "StdAfx.h"
#include "i_servicebase.h"
#include <string.h>

#pragma warning(disable: 4996)


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// LOCAL PREPROCESOR DEFINITIONS

#define CS_DEFAULT_NAME _T("NoName")

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// UTILITY FUNCTIONS

DWORD MyServiceCtrlHandlerDispatch(
								DWORD dwControl,     // requested control code
								DWORD dwEventType,   // event type
								LPVOID lpEventData,  // event data
								LPVOID lpContext     // user-defined context data
								)
{
	CI_ServiceBase* pService = (CI_ServiceBase*)lpContext;
	DWORD ret_val =  NO_ERROR;

	/*WaitForSingleObject(hMutex, INFINITE);*/
	switch(dwControl)
	{
	case SERVICE_CONTROL_PAUSE:
		if(pService->get_CanPauseAndContinue())
		{
			pService->m_Status.dwCurrentState = SERVICE_PAUSE_PENDING;
			if (!SetServiceStatus (pService->m_hStatus, 
				&(pService->m_Status)))
			{ 
				return GetLastError(); 
			}
			pService->OnPause();
			pService->m_Status.dwCurrentState = SERVICE_PAUSED;
			if (!SetServiceStatus (pService->m_hStatus, &(pService->m_Status)))
			{ 
				ret_val = GetLastError(); 
			}
		}
		else
		{
			ret_val = ERROR_CALL_NOT_IMPLEMENTED;
		}
		break;
	case SERVICE_CONTROL_CONTINUE:
		if(pService->get_CanPauseAndContinue())
		{
			pService->m_Status.dwCurrentState = SERVICE_CONTINUE_PENDING;
			if (!SetServiceStatus (pService->m_hStatus,	&(pService->m_Status)))
			{ 
				//return GetLastError(); 
			}
			pService->OnContinue();
			pService->m_Status.dwCurrentState = SERVICE_RUNNING;
			if (!SetServiceStatus (pService->m_hStatus, &(pService->m_Status)))
			{ 
				ret_val = GetLastError(); 
			}
		}
		else
		{
			ret_val = ERROR_CALL_NOT_IMPLEMENTED;
		}
		break;
	case SERVICE_CONTROL_STOP:
		if(pService->get_CanStop())
		{
			/*pService->m_Status.dwWin32ExitCode = NO_ERROR; 
			pService->m_Status.dwCurrentState  = SERVICE_STOPPED; 
			pService->m_Status.dwCheckPoint    = 0; 
			pService->m_Status.dwWaitHint      = INFINITE;

			if (!SetServiceStatus (pService->m_hStatus, 
				&(pService->m_Status)))
			{ 
				 return GetLastError(); 
			}*/
			pService->m_Status.dwCurrentState = SERVICE_STOP_PENDING;
			if (!SetServiceStatus (pService->m_hStatus, &(pService->m_Status)))
			{ 
				return GetLastError(); 
			}

			pService->OnStop();

		}
		else
		{
			ret_val = ERROR_CALL_NOT_IMPLEMENTED;
		}
		break;
	case SERVICE_CONTROL_SHUTDOWN:
		if(pService->get_CanShutdown())
		{
			pService->m_Status.dwCurrentState = SERVICE_STOP_PENDING;
			if (!SetServiceStatus (pService->m_hStatus, &(pService->m_Status)))
			{ 
				return GetLastError(); 
			}
			pService->OnShutdown();
		}
		else
		{
			ret_val = ERROR_CALL_NOT_IMPLEMENTED;
		}
		break;
	case SERVICE_CONTROL_POWEREVENT:
		if(pService->get_CanHandlePowerEvent())
		{
			if(!pService->OnPowerEvent(dwEventType)){ ret_val = BROADCAST_QUERY_DENY; }
		}
		else
		{
			ret_val = ERROR_CALL_NOT_IMPLEMENTED;
		}
		break;
	case SERVICE_CONTROL_INTERROGATE:
		// report current status
		if (!SetServiceStatus (pService->m_hStatus, &(pService->m_Status)))
		{ 
			ret_val = GetLastError(); 
		}
		break;
	default:
		pService->OnCustomCommand(dwControl);
		break;
	}
	
	return ret_val;
}

VOID ServiceStartDispatcher(DWORD argc, LPTSTR *argv) 
{ 
	int count = CI_ServiceBase::m_entries.length() - 1;
	/*for(int i=0; i<count; ++i)
	{*/
		CI_ServiceBase::m_services[0].m_hStatus = RegisterServiceCtrlHandlerEx(CI_ServiceBase::m_services[0].m_strName,
			(LPHANDLER_FUNCTION_EX)MyServiceCtrlHandlerDispatch, &(CI_ServiceBase::m_services[0]));
		if(CI_ServiceBase::m_services[0].m_hStatus == (SERVICE_STATUS_HANDLE)0) 
		{
			// exception

		}
		else
		{
			CI_ServiceBase::m_services[0].m_Status.dwCurrentState = SERVICE_RUNNING;
			SetServiceStatus(CI_ServiceBase::m_services[0].m_hStatus, &(CI_ServiceBase::m_services[0].m_Status));
			CI_ServiceBase::m_services[0].OnStart(argc, argv);
			CI_ServiceBase::m_services[0].m_Status.dwCurrentState = SERVICE_STOPPED;
			SetServiceStatus(CI_ServiceBase::m_services[0].m_hStatus, &(CI_ServiceBase::m_services[0].m_Status));
		}
	/*}*/
	return;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// CONSTRUCTION AND DESTRUCTOR IMPLEMENTATION

sref_a<SERVICE_TABLE_ENTRY> CI_ServiceBase::m_entries = sref_a<SERVICE_TABLE_ENTRY>();
CI_ServiceBase* CI_ServiceBase::m_services = NULL;

CI_ServiceBase::CI_ServiceBase(void)
{
	this->m_svc_desc.lpServiceProc = (LPSERVICE_MAIN_FUNCTION)ServiceStartDispatcher;
	this->m_svc_desc.lpServiceName = m_strName;
	_tcscpy(m_strName, CS_DEFAULT_NAME);
	this->m_CanHandle = 127;

	m_Status.dwServiceType        = SERVICE_WIN32; 
	m_Status.dwCurrentState       = SERVICE_START_PENDING; 
	m_Status.dwControlsAccepted   = SERVICE_ACCEPT_STOP | 
				SERVICE_ACCEPT_PAUSE_CONTINUE; 
	m_Status.dwWin32ExitCode      = NO_ERROR; 
	m_Status.dwServiceSpecificExitCode = 0; 
	m_Status.dwCheckPoint         = 0; 
	m_Status.dwWaitHint           = INFINITE; 
	m_hStatus = (SERVICE_STATUS_HANDLE)0;
}

CI_ServiceBase::~CI_ServiceBase(void)
{
	CloseServiceHandle((SC_HANDLE)m_hStatus);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// PROPERTIES IMPLEMENTATION

bool CI_ServiceBase::get_CanHandlePowerEvent(void)
{
	//return READ_BIT((this->m_CanHandle), P_CAN_HANDLE_POWER_EVENT);
	return bool(m_Status.dwControlsAccepted & SERVICE_ACCEPT_POWEREVENT ? true : false);
}

void CI_ServiceBase::set_CanHandlePowerEvent(bool b)
{
	//SET_BIT(this->m_CanHandle, P_CAN_HANDLE_POWER_EVENT, b);
	if(b)
	{
		m_Status.dwControlsAccepted |= SERVICE_ACCEPT_POWEREVENT;
	}
	else
	{
		m_Status.dwControlsAccepted ^= SERVICE_ACCEPT_POWEREVENT;
	}
}

//-------------------------------------------------------------------------

bool CI_ServiceBase::get_CanPauseAndContinue(void)
{
	//return READ_BIT(this->m_CanHandle, P_CAN_PAUSE_CONTINUE);
	return m_Status.dwControlsAccepted & SERVICE_ACCEPT_PAUSE_CONTINUE ? true : false;
}

void CI_ServiceBase::set_CanPauseAndContinue(bool val)
{
	//SET_BIT(this->m_CanHandle, P_CAN_PAUSE_CONTINUE, val);
	val?(m_Status.dwControlsAccepted |= SERVICE_ACCEPT_PAUSE_CONTINUE):(m_Status.dwControlsAccepted ^= SERVICE_ACCEPT_PAUSE_CONTINUE);
}

//-------------------------------------------------------------------------

bool CI_ServiceBase::get_CanShutdown(void)
{
	//return READ_BIT(this->m_CanHandle, P_CAN_SHUTDOWN);
	return m_Status.dwControlsAccepted & SERVICE_ACCEPT_SHUTDOWN ? true : false;
}

void CI_ServiceBase::set_CanShutdown(bool val)
{
	//SET_BIT(this->m_CanHandle, P_CAN_SHUTDOWN, val);
	val?(m_Status.dwControlsAccepted |= SERVICE_ACCEPT_SHUTDOWN):(m_Status.dwControlsAccepted ^= SERVICE_ACCEPT_SHUTDOWN);
}

//-------------------------------------------------------------------------

bool CI_ServiceBase::get_CanStop(void)
{
	//return READ_BIT(this->m_CanHandle, P_CAN_STOP);
	return m_Status.dwControlsAccepted & SERVICE_ACCEPT_STOP;
}

void CI_ServiceBase::set_CanStop(bool val)
{
	//SET_BIT(this->m_CanHandle, P_CAN_STOP, val);
	val?(m_Status.dwControlsAccepted |= SERVICE_ACCEPT_STOP):(m_Status.dwControlsAccepted ^= SERVICE_ACCEPT_STOP);
}

//-------------------------------------------------------------------------

bool CI_ServiceBase::get_ServiceName(TCHAR* pOutput, long nOutputSize)
{
	if(_tcsclen((this->m_strName))>size_t(nOutputSize))
	{
		_tcsncpy(pOutput, m_strName, size_t(nOutputSize));
		return false;
	}
	else
	{
		_tcscpy(pOutput, m_strName);
		return true;
	}
}

void CI_ServiceBase::set_ServiceName(const TCHAR* strName)
{
	_tcscpy(m_strName, strName);
}

//-------------------------------------------------------------------------

void CI_ServiceBase::get_ServiceTableEntry(SERVICE_TABLE_ENTRY* ste)
{
	memcpy(ste, &(this->m_svc_desc), sizeof(SERVICE_TABLE_ENTRY));
}

//-------------------------------------------------------------------------

DWORD CI_ServiceBase::get_ServiceType()
{
	return this->m_Status.dwServiceType;
}

//-------------------------------------------------------------------------

void CI_ServiceBase::set_ServiceType(DWORD Type)
{
	this->m_Status.dwServiceType = Type;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// SERVICE RUN IMPLEMENTATION

bool CI_ServiceBase::Run(CI_ServiceBase* pService)
{
	if((SERVICE_TABLE_ENTRY*)m_entries)
	{	return false; }

	CI_ServiceBase::m_services = pService;

	m_entries = I_NEWA(SERVICE_TABLE_ENTRY, 2);
	pService->get_ServiceTableEntry(m_entries);
	memset(&(m_entries[1]), NULL, sizeof(SERVICE_TABLE_ENTRY));

	return (StartServiceCtrlDispatcher(m_entries)) ? true:false;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// EVENT HANDLERS IMPLEMENTATION

void CI_ServiceBase::OnContinue(void)
{
	;
}

//-------------------------------------------------------------------------

void CI_ServiceBase::OnCustomCommand(int command)
{
	;
}

//-------------------------------------------------------------------------

void CI_ServiceBase::OnPause(void)
{
	;
}

//-------------------------------------------------------------------------

bool CI_ServiceBase::OnPowerEvent(long pwb_status)
{
	return true;
}

//-------------------------------------------------------------------------

void CI_ServiceBase::OnShutdown(void)
{
}

//-------------------------------------------------------------------------

void CI_ServiceBase::OnStart(int argc, LPTSTR* argv)
{
	;
}

//-------------------------------------------------------------------------

void CI_ServiceBase::OnStop(void)
{
	;
}

//-------------------------------------------------------------------------