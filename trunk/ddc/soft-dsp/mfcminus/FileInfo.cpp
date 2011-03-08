#include "stdafx.h"
#include "gkhy/mfcminus/FileInfo.hpp"

#pragma warning(disable : 4996)

using namespace gkhy::MfcMinus;

FileInfo::FileInfo(const std::string filePath)
{
	m_filePath = filePath;
}

std::string FileInfo::fileName()
{                        
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];

	_splitpath( m_filePath.c_str(), drive, dir, fname, ext ); 
	return std::string(fname) + std::string(ext);
}
