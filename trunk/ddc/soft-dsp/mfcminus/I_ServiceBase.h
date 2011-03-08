#ifndef INTELLIGER_SERVICE_BASE_H
#define INTELLIGER_SERVICE_BASE_H

#include "smart_reference.h"
#include <winsvc.h>

// #ifdef CSERVICE_BASE_EXPORTS
// #define EASY_WAY_API __declspec(dllexport)
// #else
// #define EASY_WAY_API __declspec(dllimport)
// #endif

#define EASY_WAY_API

/*! Provides a base class for a service writed in C++ that will exist as part of a service application. CI_ServiceBase must be derived when creating a new service class.
*	Derive from CI_ServiceBase when defining your service class in a service
*	application. Any useful service overrides the OnStart and OnStop methods.
*	For additional functionality, you can override OnPause and OnContinue with
*	specific behavior in response to changes in the service state.<p>
*	To use this class, you should include in your source following headers<br>
*	<font color=red>
*		#include <windows.h> <BR>
*		#include "smart_reference.h" <BR>
*		#include "I_ServiceBase.h" <BR>
*	</font>
*/
class EASY_WAY_API CI_ServiceBase
{
	friend DWORD MyServiceCtrlHandlerDispatch(
								DWORD dwControl,     // requested control code
								DWORD dwEventType,   // event type
								LPVOID lpEventData,  // event data
								LPVOID lpContext     // user-defined context data
								);
	friend VOID ServiceStartDispatcher(DWORD argc, LPTSTR *argv);
public:
	/*! Creates a new instance of the ServiceBase class. 
	*/
	CI_ServiceBase(void);
	virtual ~CI_ServiceBase(void);

	/*!	Provides the main entry point for an executable that contains a single service. Loads the service into memory so it can be started.
	*/
	static bool Run(CI_ServiceBase* pService);
	/*!	Provides the main entry point for an executable that contains multiple associated services. Loads the specified services into memory so they can be started.
	*/
	//static bool Run(CI_ServiceBase services[], long nCount);

	// PROPERTIES

	/*! Gets a value indicating whether the service can handle notifications of computer power status changes.
	*/
	bool get_CanHandlePowerEvent(void);
	/*!Sets a value indicating whether the service can handle notifications of computer power status changes.
	*/
	void set_CanHandlePowerEvent(bool b);

	/*! Gets a value indicating whether the service can be paused and resumed.
	*/
	bool get_CanPauseAndContinue(void);

	/*! Sets a value indicating whether the service can be paused and resumed.
	*/
	void set_CanPauseAndContinue(bool b);

	/*! Gets a value indicating whether the service should be notified when the system is shutting down.
	*/
	bool get_CanShutdown(void);

	/*! Sets a value indicating whether the service should be notified when the system is shutting down.
	*/
	void set_CanShutdown(bool b);

	/*! Gets a value indicating whether the service can be stopped once it has started.
	*/
	bool get_CanStop(void);

	/*! Sets a value indicating whether the service can be stopped once it has started.
	*/
	void set_CanStop(bool b);

	/*! Gets the short name used to identify the service to the system.
	*/
	bool get_ServiceName(TCHAR* pOutput, long nOutputSize);
	/*! Sets the short name used to identify the service to the system.
	*/
	void set_ServiceName(const TCHAR* strName);

	void get_ServiceTableEntry(SERVICE_TABLE_ENTRY* ste);

	/*! Gets the type of service property value. 
	*	This member can be one of the following values. Value Meaning <BR>
	*	<b> SERVICE_FILE_SYSTEM_DRIVER </b> The service is a file system driver. <BR>
	*	<b> SERVICE_KERNEL_DRIVER </b> The service is a device driver. <BR>
	*	<b> SERVICE_WIN32_OWN_PROCESS </b> The service runs in its own process. <BR>
	*	<b> SERVICE_WIN32_SHARE_PROCESS </b> The service shares a process with other services. 
	*/
	DWORD get_ServiceType(void);
	/*! Sets the type of service property value
	*	Default value for this property is SERVICE_WIN32 = SERVICE_WIN32_OWN_PROCESS | SERVICE_WIN32_SHARE_PROCESS
	*/
	void set_ServiceType(DWORD Type);

protected:
	// OVERLOADED HANDLERS

	/*! When implemented in a derived class,
		OnContinue runs when a Continue command is sent to the
		service by the Service Control Manager (SCM).
		Specifies actions to take when a service resumes normal
		functioning after being paused.
	*/
	virtual void OnContinue(void);

	/*! When implemented in a derived class, OnCustomCommand executes
		when the Service Control Manager (SCM) passes a custom command
		to the service. Specifies actions to take when a command with
		the specified parameter value occurs.
	*/
	virtual void OnCustomCommand(int command);

	/*! When implemented in a derived class, executes when a Pause
		command is sent to the service by the Service Control Manager (SCM).
		Specifies actions to take when a service pauses.
	*/
	virtual void OnPause(void);

	/*! When implemented in a derived class, executes when the computer's
		power status has changed. This applies to laptop computers when they
		go into suspended mode, which is not the same as a system shutdown.
	*/
	virtual bool OnPowerEvent(long pwb_status);

	/*! When implemented in a derived class, executes when the system is
		shutting down. Specifies what should happen immediately prior to
		the system shutting down.
	*/
	virtual void OnShutdown(void);

	/*! When implemented in a derived class, executes when a Start command
		is sent to the service by the Service Control Manager (SCM) or when
		the operating system starts (for a service that starts automatically).
		Specifies actions to take when the service starts.
	*/
	virtual void OnStart(int argc, LPTSTR* argv);

	/*! When implemented in a derived class, executes when a Stop command
		is sent to the service by the Service Control Manager (SCM).
		Specifies actions to take when a service stops running.
	*/
	virtual void OnStop(void);

private:
	unsigned char m_CanHandle;
	TCHAR m_strName[182];
	SERVICE_TABLE_ENTRY m_svc_desc;
	SERVICE_STATUS_HANDLE m_hStatus;
	SERVICE_STATUS m_Status;
	static sref_a<SERVICE_TABLE_ENTRY> m_entries;
	static CI_ServiceBase* m_services;
};

#endif
// INTELLIGER_SERVICE_BASE_H