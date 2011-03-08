#pragma once

#include <QTextEdit>
#include <QTextBlockUserData>

namespace gkhy
{
	namespace QZebraLib
	{
		class BlockLogRuntime : public QTextBlockUserData
		{
		public:
			BlockLogRuntime(QString d) : QTextBlockUserData() { m_directory = d; }
			QString directory() { return m_directory; }
		private:
			QString m_directory;
		};

		class LogRuntime : public QTextEdit
		{
			Q_OBJECT
		public:
			/**
			* The constructor
			*/
			LogRuntime(QWidget * parent = 0);
			/**
			* Called by the mainimpl to set the pointer with the address of the main window.
			*/
			//void setMainImpl( MainImpl *mainImpl ) { m_mainImpl = mainImpl; }
			static bool containsError(QString message, QString & file, uint & line);
			static bool containsWarning(QString message, QString & file, uint & line);
		protected:	
			/**
			* When the user double-click on a error or warning line, the file is opened in a editor.
			*/
			void mouseDoubleClickEvent( QMouseEvent * event );
			public slots:
				/**
				* In main window, the signal message(QString, QString) of the class Build is connected
				*			to the slot slotMessagesBuild in this class.
				*/
				void slotMessagesBuild(QString list, QString directory);
		private:
			/** 
			* A pointer to the MainImpl class 
			*/
			//MainImpl* m_mainImpl;
		signals:
			void incErrors();
			void incWarnings();
		};

	}
}

