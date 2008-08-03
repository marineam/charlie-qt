
#include <QApplication>
#include <MainWindow.h>
#include <MpdClient.h>

MpdClient *mpdclient;

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	MainWindow window;

	mpdclient = new MpdClient(&window);
	mpdclient->start();

	window.show();
	return app.exec();
}
