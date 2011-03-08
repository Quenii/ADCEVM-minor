#include "ControlPanel.h"
#include "AdcBoard.hpp"

#include <QStandardItemModel>
#include <QStringList>

ControlPanel::ControlPanel(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	ui.setupUi(this);

	/*QStandardItemModel **/
	devListModel = new QStandardItemModel(0, 3, ui.devicesView);
	devListModel->setHeaderData(0, Qt::Horizontal, QObject::tr("No."));
	devListModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Dev Name"));
	devListModel->setHeaderData(2, Qt::Horizontal, QObject::tr("INF Name"));	

	ui.devicesView->setModel(devListModel);

	bool okay = connect(ui.devicesView, SIGNAL(clicked(const QModelIndex&)),
		this, SLOT(devItemClicked(const QModelIndex&)));
	Q_ASSERT(okay);

	okay = connect(this, SIGNAL(changeSettings(const SignalSettings&)),
		ui.signalSettingsWidget, SLOT(setSettings(const SignalSettings&)));
	Q_ASSERT(okay);

	okay = connect(this, SIGNAL(changeSettings(const AdcSettings&)),
		ui.adcSettingsWidget, SLOT(setSettings(const AdcSettings&)));
	Q_ASSERT(okay);

	tdReportModel = new QStandardItemModel(0, 2, ui.treeViewTdReport);
	//tdReportModel->setHeaderData(0, Qt::Horizontal, QObject::tr("Addr"));
	tdReportModel->setHeaderData(0, Qt::Horizontal, QObject::tr("Name"));
	tdReportModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Value"));	

	ui.treeViewTdReport->setModel(tdReportModel);

	//ui.groupBox_DeviceList->hide();
	//ui.adcSettingsWidget->hide();
	//ui.signalSettingsWidget->hide();
	ui.tabWidget->hide();
	ui.groupBox_powerStatus->hide();
	ui.labl_2->hide();
	ui.treeViewTdReport->hide();
	
	AdcBoard& board = *(AdcBoard::instance());
	board.adcSettings(adcSettings);
	ui.adcSettingsWidget->setSettings(adcSettings);

	board.signalSettings(signalSettings);
	ui.signalSettingsWidget->setSettings(signalSettings);
}

ControlPanel::~ControlPanel()
{
	
}

void ControlPanel::setDevList(const QList<AdcBoardInfo>& lst)
{
	devListModel->removeRows(0, devListModel->rowCount());

	for (int i = 0; i < lst.size(); ++i)
	{
		devListModel->insertRow(0);

		//devListModel->setData(devListModel->index(0, 0), lst[i].usbAddr);
		//devListModel->item(0, 0)->setEditable(false);
		devListModel->setData(devListModel->index(0, 0), lst[i].index);
		devListModel->item(0, 0)->setEditable(false);

		devListModel->setData(devListModel->index(0, 1), lst[i].devName);
		devListModel->item(0, 1)->setEditable(false);

		devListModel->setData(devListModel->index(0, 2), lst[i].infName);
		devListModel->item(0, 2)->setEditable(false);
		
	}

	if (lst.size() > 0)
	{
		// choose the first device by default...
		ui.devicesView->selectionModel()->select(devListModel->index(0, 0), QItemSelectionModel::Select | QItemSelectionModel::Rows);
		devItemClicked(devListModel->index(0, 0));
	}	
}

void ControlPanel::devItemClicked(const QModelIndex& index)
{
	QString infName = devListModel->data(devListModel->index(index.row(), 2)).toString();
	emit devSelected(infName);
	//int usbAddress = devListModel->data(devListModel->index(index.row(), 0)).toInt();
	//emit devSelected(usbAddress);
}

void ControlPanel::updateReport(const AdcBoardReport &rpt)
{
	setUiPowerStatus(rpt.powerStatus);

	// td report
	const TimeDomainReport& tdRpt = rpt.tdReport;
	const FreqDomainReport& fdRpt = rpt.fdReport;

	tdReportModel->removeRows(0, tdReportModel->rowCount());
	tdReportModel->insertRow(0);
	tdReportModel->setData(tdReportModel->index(0, 0), "Max(V)");
	//tdReportModel->item(0, 0)->setEditable(false);

	tdReportModel->setData(tdReportModel->index(0, 1), tdRpt.max);
	//tdReportModel->item(0, 1)->setEditable(false);
	
	tdReportModel->insertRow(0);
	tdReportModel->setData(tdReportModel->index(0, 0), "Min(V)");
	//tdReportModel->item(0, 0)->setEditable(false);
	tdReportModel->setData(tdReportModel->index(0, 1), tdRpt.min);
	//tdReportModel->item(0, 1)->tdReportModel(false);

	for (int i = fdRpt.HD.size() - 1; i >= 0 ; --i)
	{
		tdReportModel->insertRow(0);
		tdReportModel->setData(tdReportModel->index(0, 0), tr("HD[%n]", "", i) );
		//tdReportModel->item(0, 0)->setEditable(false);
		tdReportModel->setData(tdReportModel->index(0, 1), fdRpt.HD[i]);
		//tdReportModel->item(0, 1)->tdReportModel(false);
	}


	tdReportModel->insertRow(0);
	tdReportModel->setData(tdReportModel->index(0, 0), "ENOB");
	//tdReportModel->item(0, 0)->setEditable(false);
	tdReportModel->setData(tdReportModel->index(0, 1), fdRpt.ENOB);
	//tdReportModel->item(0, 1)->tdReportModel(false);

	tdReportModel->insertRow(0);
	tdReportModel->setData(tdReportModel->index(0, 0), "THD");
	//tdReportModel->item(0, 0)->setEditable(false);
	tdReportModel->setData(tdReportModel->index(0, 1), fdRpt.THD);
	//tdReportModel->item(0, 1)->tdReportModel(false);

	tdReportModel->insertRow(0);
	tdReportModel->setData(tdReportModel->index(0, 0), "SINAD");
	//tdReportModel->item(0, 0)->setEditable(false);
	tdReportModel->setData(tdReportModel->index(0, 1), fdRpt.SINAD);
	//tdReportModel->item(0, 1)->tdReportModel(false);

	tdReportModel->insertRow(0);
	tdReportModel->setData(tdReportModel->index(0, 0), "SNR");
	//tdReportModel->item(0, 0)->setEditable(false);
	tdReportModel->setData(tdReportModel->index(0, 1), fdRpt.SNR);
	//tdReportModel->item(0, 1)->tdReportModel(false);

	tdReportModel->insertRow(0);
	tdReportModel->setData(tdReportModel->index(0, 0), "SFDR");
	//tdReportModel->item(0, 0)->setEditable(false);
	tdReportModel->setData(tdReportModel->index(0, 1), fdRpt.SFDR);
	//tdReportModel->item(0, 1)->tdReportModel(false);

	tdReportModel->insertRow(0);
	tdReportModel->setData(tdReportModel->index(0, 0), "Input(dB)");
	//tdReportModel->item(0, 0)->setEditable(false);
	tdReportModel->setData(tdReportModel->index(0, 1), fdRpt.AdB);
	//tdReportModel->item(0, 1)->tdReportModel(false);

	tdReportModel->insertRow(0);
	tdReportModel->setData(tdReportModel->index(0, 0), "Input(Vpp)");
	//tdReportModel->item(0, 0)->setEditable(false);
	tdReportModel->setData(tdReportModel->index(0, 1), fdRpt.A);
	//tdReportModel->item(0, 1)->tdReportModel(false);


}


void ControlPanel::on_adcSettingsWidget_settingsChanged()
{
	ui.adcSettingsWidget->settings(adcSettings);
	AdcBoard& board = *(AdcBoard::instance());
	if (!board.setAdcSettings(adcSettings))
	{
		Q_ASSERT(false);
	}
}

void ControlPanel::on_signalSettingsWidget_settingsChanged()
{
	ui.signalSettingsWidget->settings(signalSettings);
	AdcBoard& board = *(AdcBoard::instance());
	if (!board.setSignalSettings(signalSettings))
	{
		Q_ASSERT(false);
	}
}

void ControlPanel::on_pushButtonStartDynamicTest_clicked()
{	
	ui.pushButtonStartDynamicTest->setEnabled(false);
	ui.pushButtonStopDynamicTest->setEnabled(true);	
	ui.staticTestButtons->setEnabled(false);
	AdcBoard::instance()->setDynamicOn(true);
}

void ControlPanel::on_pushButtonStopDynamicTest_clicked()
{		
	ui.pushButtonStopDynamicTest->setEnabled(false);
	ui.pushButtonStartDynamicTest->setEnabled(true);	
	ui.staticTestButtons->setEnabled(true);
	AdcBoard::instance()->setDynamicOn(false);
}

void ControlPanel::on_pushButtonStartStaticTest_clicked()
{
	
	ui.pushButtonStartStaticTest->setEnabled(false);
	ui.pushButtonStopStaticTest->setEnabled(true);		
	ui.dynamicTestButtons->setEnabled(false);
}

void ControlPanel::on_pushButtonStopStaticTest_clicked()
{		
	ui.pushButtonStopStaticTest->setEnabled(false);	
	ui.pushButtonStartStaticTest->setEnabled(true);
	ui.dynamicTestButtons->setEnabled(true);
}

void ControlPanel::setUiPowerStatus(const PowerStatus& status)
{
	ui.vaLineEdit->setText(QString("%L1").arg(status.va, 0, 'f', 2));
	ui.vdLineEdit->setText(QString("%L1").arg(status.vd, 0, 'f', 2));
	ui.iaLineEdit->setText(QString("%L1").arg(status.ia, 0, 'f', 1));
	ui.idLineEdit->setText(QString("%L1").arg(status.id, 0, 'f', 1));
	ui.powerLineEdit->setText(QString("%1").arg(status.power));
}

