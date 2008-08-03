
#ifndef _CURRENT_STATUS_H_
#define _CURRENT_STATUS_H_

#include <QWidget>
#include <QLabel>

#include "MpdClient.h"

class CurrentStatus : public QWidget
{
	Q_OBJECT

public:
	CurrentStatus(QWidget *parent=0);

public slots:
	void updateSong(const mpd_Song *new_song);

private:
	QLabel *song_title;
	QLabel *song_artist;
};

#endif
