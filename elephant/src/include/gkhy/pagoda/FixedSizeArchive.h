//////////////////////////////////////////////////////////////////////////
// DataScan 
//
// Author: Liu Peng
// Email:  liupengee@126.com
// Copyright(c)2010, GKHY
//
// You may freely use or modify this code provided this
// Copyright is included in all derived versions.
//
// Created : Feb 22, 2010 Liu Peng
//
// 
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "gkhy/pagoda/pagoda_global.h"
#include "gkhy/pagoda/qunbufferedfile.h"

#include <QString>

namespace gkhy
{
	namespace pagoda
	{	
		class PAGODA_EXPORT FixedSizeArchive : QObject
		{
			Q_OBJECT

		public:
			FixedSizeArchive(QObject* parent = 0);
			virtual ~FixedSizeArchive();

		private:
			Q_DISABLE_COPY(FixedSizeArchive)
		
		public:
			bool open(QString fileNameBase, QString fileNameExt, qint64 perFileSize);
			void close();	
			bool isOpen() const { return m_file.isOpen(); }

			qint64 write(const char* buf, qint64 len);

			qint64 currentSize() const { return m_file.size(); }			
			qint64 totalSize() const { return m_totalSize; }

		signals:
			void fileCreated(QString fileName);

		private:
			QString newFileName();

		private:
			QString m_fileNameBase;
			QString m_fileNameExt;
			qint64 m_fileNameSN;
			qint64 m_perFileSize;
			QUnbufferedFile m_file;
			qint64 m_totalSize;
		};
	}
}

