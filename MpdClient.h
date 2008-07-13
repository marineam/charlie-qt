
#ifndef _MPDCLIENT_H_
#define _MPDCLIENT_H_

#include <libmpdclient.h>
#include <QObject>

class MpdClient : public QObject
{
	Q_OBJECT

public:
	MpdClient(QObject *parent = 0);

	/* connect to mpd and start the update timer */
	bool start();

public slots:
	void update();

private:
	mpd_Connection *conn;
	mpd_Status *status;
};

#endif
