
#include <MpdClient.h>

#include <stdlib.h> /* for getenv, atoi */
#include <QTimer>

MpdClient::MpdClient(QObject *parent) : QObject(parent)
{
	conn = NULL;
}

bool MpdClient::start()
{
	char *host = getenv("MPD_HOST");
	char *port = getenv("MPD_PORT");

	if (host == NULL)
		host = "localhost";
	if (port == NULL)
		port = "6600";

	conn = mpd_newConnection(host, atoi(port), 10);

	if (conn->error)
		return false;

	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));
	timer->start(1000);

	return true;
}

void MpdClient::update()
{
	status = mpd_getStatus(conn);
}

