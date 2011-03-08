//////////////////////////////////////////////////////////////////////////
// SystemLevelSingleton - An Interface that guarantees system level unique
// instance of derived class.
//
// Author: Liu Peng
// Email:  liupengee@126.com
// Copyright (c) 2010, GKHY
//
// You may freely use or modify this code provided this
// Copyright is included in all derived versions.
//
// Created : Jan 22, 2010 Liu Peng
//
// Use this interface as a base class, and implement onInstanceExists()
// method. This onInstanceExists() method is called when it fails to
// construct due to an instance already exists.
//
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "gkhy/mfcminus/mfcminus_global.hpp"

class LockPair;

namespace gkhy
{
	namespace MfcMinus
	{			
		class MFCMINUS_API SystemLevelSingleton
		{		
		public:
			SystemLevelSingleton(char* name);	
			virtual ~SystemLevelSingleton();		
		private:
			LockPair& m_lockPair;

 		};
	}
}