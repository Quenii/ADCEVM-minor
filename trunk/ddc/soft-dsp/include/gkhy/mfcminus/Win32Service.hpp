//////////////////////////////////////////////////////////////////////////
// Win32Service 
//
// Author: Liu Peng
// Email:  liupengee@126.com
// Copyright(c)2010, GKHY
//
// You may freely use or modify this code provided this
// Copyright is included in all derived versions.
//
// Created : Feb 26, 2010 Liu Peng
//
//  example
//  ===============================
// 	TestService ts;
// 
// 	ts.set_CanPauseAndContinue(false);
// 	ts.set_ServiceName("isw_test");
// 	gkhy::MfcMinus::Win32Service::run(&ts);
// 
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "gkhy/mfcminus/mfcminus_global.hpp"
#include <string>
#include <vector>

namespace gkhy
{
	namespace MfcMinus
	{		
		class Win32ServicePrivate;

		class MFCMINUS_API Win32Service
		{
			friend class Win32ServicePrivate;

		public:
			Win32Service();
			virtual ~Win32Service();

		public:
			static bool install(const char* binPathName, const char* serviceName, const char* displayName);		
			static bool uninstall(const char* serviceName);
			static bool start(const char* serviceName);
			static bool kill(const char* serviceName);

			/*!	Provides the main entry point for an executable that contains a single service. Loads the service into memory so it can be started.
			*/
			static bool run(Win32Service* pService);
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
			bool get_ServiceName(std::string& name);
			/*! Sets the short name used to identify the service to the system.
			*/
			void set_ServiceName(const char* strName);

			//void get_ServiceTableEntry(SERVICE_TABLE_ENTRY* ste);

			/*! Gets the type of service property value. 
			*	This member can be one of the following values. Value Meaning <BR>
			*	<b> SERVICE_FILE_SYSTEM_DRIVER </b> The service is a file system driver. <BR>
			*	<b> SERVICE_KERNEL_DRIVER </b> The service is a device driver. <BR>
			*	<b> SERVICE_WIN32_OWN_PROCESS </b> The service runs in its own process. <BR>
			*	<b> SERVICE_WIN32_SHARE_PROCESS </b> The service shares a process with other services. 
			*/
			unsigned long get_ServiceType(void);
			/*! Sets the type of service property value
			*	Default value for this property is SERVICE_WIN32 = SERVICE_WIN32_OWN_PROCESS | SERVICE_WIN32_SHARE_PROCESS
			*/
			void set_ServiceType(unsigned long Type);

		protected:
			// OVERLOADED HANDLERS

			/*! When implemented in a derived class,
			onContinue runs when a Continue command is sent to the
			service by the Service Control Manager (SCM).
			Specifies actions to take when a service resumes normal
			functioning after being paused.
			*/
			virtual void onContinue(void) {}

			/*! When implemented in a derived class, onCustomCommand executes
			when the Service Control Manager (SCM) passes a custom command
			to the service. Specifies actions to take when a command with
			the specified parameter value occurs.
			*/
			virtual void onCustomCommand(int command){}

			/*! When implemented in a derived class, executes when a Pause
			command is sent to the service by the Service Control Manager (SCM).
			Specifies actions to take when a service pauses.
			*/
			virtual void onPause(void){}

			/*! When implemented in a derived class, executes when the computer's
			power status has changed. This applies to laptop computers when they
			go into suspended mode, which is not the same as a system shutdown.
			*/
			virtual bool onPowerEvent(long pwb_status) { return true; }

			/*! When implemented in a derived class, executes when the system is
			shutting down. Specifies what should happen immediately prior to
			the system shutting down.
			*/
			virtual void onShutdown(void) { }

			/*! When implemented in a derived class, executes when a Start command
			is sent to the service by the Service Control Manager (SCM) or when
			the operating system starts (for a service that starts automatically).
			Specifies actions to take when the service starts.
			*/
			virtual void onStart(const std::vector< std::string >& args) = 0; // {}

			/*! When implemented in a derived class, executes when a Stop command
			is sent to the service by the Service Control Manager (SCM).
			Specifies actions to take when a service stops running.
			*/
			virtual void onStop(void)  = 0; //{ }
			
		private:
			Win32ServicePrivate* m_p;
		};
	}
}

