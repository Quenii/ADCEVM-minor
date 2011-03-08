#ifndef REGACCESSITEM_H
#define REGACCESSITEM_H

#include "ui_RegAccessItem.h"
#include <QWidget>

struct RegAccessItemData
{
	bool checked;
	int operation;
	unsigned int addr;
	unsigned int value;

	RegAccessItemData()
	{
		checked = false;
		operation = 0;
		addr = 0;
		value = 0;
	}
};

class RegAccessItem : public QWidget, public Ui::RegAccessItemClass
{
	Q_OBJECT

public:
	RegAccessItem(QWidget *parent);
	~RegAccessItem();

public:
	void showArrow(bool on = true);
	bool arrowShown();

	void setUiData(const RegAccessItemData& data);
	void UiData(RegAccessItemData& data);

private:
	bool m_bShowArrow;
	
};

#endif // REGACCESSITEM_H
