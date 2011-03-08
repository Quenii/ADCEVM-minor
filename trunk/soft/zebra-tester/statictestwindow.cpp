#include "statictestwindow.h"

#ifdef _DEBUG
#	pragma comment(lib, "qwtd.lib")
#else
#	pragma comment(lib, "qwt.lib")
#endif

StaticTestWindow::StaticTestWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

StaticTestWindow::~StaticTestWindow()
{

}
