#include "mainwindow.h"
#include "statictestwindow.h"
#include "dynamictestwindow.h"
#include "qmdisubwindowex.h"
#include "qdactypedialog.h"
#include "qclockfreqdialog.h"

#include <QPushButton>
#include <QList>
#include <QPointer>
#include <QMessageBox>
/*
class QActionUnckecker : public QObject
{
	Q_OBJECT

public:
	QActionUnckecker(QAction* action)
	{
		d_action = action;
	}
public slots:
	void uncheck(bool b)
	{
		if (d_action && b)
		{
			d_action->setChecked(!b);
		}
	}

private:
	QPointer<QAction> d_action;
};

#include "mainwindow.moc"
*/
MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	/*QMdiSubWindowEx* a = addMdiWindow(new StaticTestWindow(0), 0);
	QMdiSubWindowEx* b = addMdiWindow(new DynamicTestWindow(0), 0);
	a->adjustSize();
	b->adjustSize();
	
	QActionUnckecker* _a = new QActionUnckecker(a->toggleViewAction());
	QActionUnckecker* _b = new QActionUnckecker(b->toggleViewAction());

	bool ok = connect(a->toggleViewAction(), SIGNAL(toggled(bool)), _b, SLOT(uncheck(bool)));
	Q_ASSERT(ok);

	ok = connect(b->toggleViewAction(), SIGNAL(toggled(bool)), _a, SLOT(uncheck(bool)));
	Q_ASSERT(ok);
	*/
}

MainWindow::~MainWindow()
{

}

void MainWindow::on_actionDacType_triggered(bool checked)
{
	QDacTypeDialog dlg;
	if (QDialog::Accepted == dlg.exec())
	{
		DacTypeSettings dacTypeSettings = dlg.settings();
		ui.dacTypeWidget->setDacTypeSettings(dacTypeSettings);
	}
}

void MainWindow::on_actionClockFrequency_triggered(bool checked)
{
	QClockFreqDialog dlg;
	if (QDialog::Accepted == dlg.exec())
	{
		float clockFreq = dlg.clockFreq();
		ui.clockFreqWidget->setClockFreq(clockFreq);
	}
}

void MainWindow::on_actionAboutCETC58DACAnalyzer_triggered(bool checked)
{
	QMessageBox::about(this, tr("About CETC58 DAC Analyzer"),
		tr("<br><b>DAC Analyzer</b> is designed to work with the USB-DAC evaluation board.<br><br><div align=center>Copyright (c) CETC58, 2011</div><br> "));
}


/*
QMdiSubWindowEx* MainWindow::addMdiWindow(QWidget* widget, QPushButton* btn)
{
	QMdiSubWindowEx* subWindow = new QMdiSubWindowEx(this, Qt::MSWindowsFixedSizeDialogHint); 
	subWindow->setWidget(widget);
	ui.mdiArea->addSubWindow(subWindow);
	ui.menuWindow->addAction(subWindow->toggleViewAction());
	ui.toolBar->addAction(subWindow->toggleViewAction());

	if (btn)
	{
		bool ok = connect(btn, SIGNAL(clicked()),
			subWindow->toggleViewAction(), SLOT(toggle()));
		Q_ASSERT(ok);
	}

	return subWindow;
}*/