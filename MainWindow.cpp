
#include "MainWindow.h"

#include <QTabWidget>
#include <QGridLayout>

MainWindow::MainWindow()
{
	QTabWidget *tabs = new QTabWidget(this);
	QGridLayout *layout = new QGridLayout(this);

	resize(800, 480);
	setLayout(layout);
	layout->addWidget(tabs);

	tabs->addTab(new QWidget(), "Test");
	tabs->addTab(new QWidget(), "Test2");
}
