
#ifndef _MPDCLIENT_H_
#define _MPDCLIENT_H_

#include <libmpdclient.h>
#include <QObject>
#include <QList>

class MpdClient : public QObject
{
	Q_OBJECT

public:
	MpdClient(QObject *parent = 0);

	/* connect to mpd and start the update timer */
	bool start();

	const mpd_Song* currentSong() const;

public slots:
	void update();

signals:
	void changedSong(const mpd_Song *new_song);

private:
	void updatePlaylist(long long version);

	mpd_Connection *conn;
	mpd_Status *status;

	QList<mpd_Song*> playlist;
};

extern MpdClient *mpdclient;

#endif
