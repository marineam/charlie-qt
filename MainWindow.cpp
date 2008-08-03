
#include "MainWindow.h"
#include "CurrentStatus.h"
#include "MpdClient.h"

MpdClient *mpdclient;

MainWindow::MainWindow() : QTabWidget()
{
	resize(800, 480);

	mpdclient = new MpdClient(this);

	addTab(new CurrentStatus(), "Current Status");
	addTab(new QWidget(), "Test2");

	mpdclient->start();
}
