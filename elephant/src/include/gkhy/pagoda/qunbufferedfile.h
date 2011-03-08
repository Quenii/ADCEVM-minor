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

#include <QObject>
#include <QString>

class File;
class AlignedBuffer;

namespace gkhy
{
	namespace pagoda
	{
		class PAGODA_EXPORT QUnbufferedFile : public QObject
		{
			Q_OBJECT
		public:
			QUnbufferedFile(int writeBufferSize = 512 * 1024, QObject* parent = 0);
			virtual ~QUnbufferedFile();

		private:
			Q_DISABLE_COPY(QUnbufferedFile)

		public:		
			bool isOpen() const;
			bool open(QString fileName);

			int write(const char* buf, int len);
			void close();

			qint64 size() const;

		signals:
			void fileCreated(QString fileName);

		private:
			File& m_file;
			AlignedBuffer& m_obuf;
			int m_obufCount;
		};
	}
}

