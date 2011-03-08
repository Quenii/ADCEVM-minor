//////////////////////////////////////////////////////////////////////////
// WorkerThread - A Worker Thread Implementation
//
// Author: Liu Peng
// Email:  liupengee@126.com
// Copyright (c) 2009, GKHY Co., Ltd
//
// You may freely use or modify this code provided this
// Copyright is included in all derived versions.
//
// Created : 8/22/09 Liu Peng//                
//
// This class implements a worker thread.
//////////////////////////////////////////////////////////////////////////

#pragma once

namespace gkhy 
{
	namespace mfcplus
	{
		class AFX_EXT_CLASS WorkerThread
		{
		public:
			WorkerThread(void);
			virtual ~WorkerThread(void);
		
		public:
			bool IsRunning()  { return m_Alive; }
		
			void Start(
				LPVOID lpvoid = NULL,
				int nPriority = THREAD_PRIORITY_NORMAL,
				UINT nStackSize = 0,
				DWORD dwCreateFlags = 0,
				LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL);
			void Stop();

		protected:			
			virtual UINT ThreadProc(LPVOID lpvoid, volatile bool& enabled);

		private:
			static UINT InternalThreadProc(LPVOID lpvoid);
			
			// bool IsAlive();

		private:
			volatile bool m_Enabled;
			volatile bool m_Alive;
			LPVOID m_lpvoid;
			CWinThread* m_pThreadObj;
		};
	};
};