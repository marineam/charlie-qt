
#ifndef _CURRENT_PLAYLIST_H_
#define _CURRENT_PLAYLIST_H_

#include <QWidget>
#include <QListView>
#include <QStringList>
#include <QStringListModel>

#include "MpdClient.h"

class CurrentPlaylist : public QWidget
{
	Q_OBJECT

public:
	CurrentPlaylist(QWidget *parent=0);

public slots:
	void updateSong(const mpd_Song *new_song);

private:
	QListView *playlist_widget;
	QStringListModel *playlist_model;
	QStringList playlist;
};

#endif
