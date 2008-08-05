
#include "CurrentPlaylist.h"

#include <assert.h>
#include <QVBoxLayout>

CurrentPlaylist::CurrentPlaylist(QWidget *parent) : QWidget(parent)
{
	QVBoxLayout *layout = new QVBoxLayout(this);
	playlist_widget = new QListView(this);
	playlist_model = new QStringListModel(this);

	playlist_model->setStringList(playlist);
	playlist_widget->setModel(playlist_model);

	connect(mpdclient, SIGNAL(changedSong(const mpd_Song*)),
			this, SLOT(updateSong(const mpd_Song*)));

	setLayout(layout);
	layout->addWidget(playlist_widget);
}

void CurrentPlaylist::updateSong(const mpd_Song *new_song)
{
	if (new_song) {
		assert(new_song->pos <= playlist.size());
		if (new_song->pos == playlist.size())
			playlist.append(new_song->file);
		else
			playlist[new_song->pos] = new_song->file;
	}
	else
		playlist.removeLast();

	playlist_model->setStringList(playlist);
}
