
#include "CurrentStatus.h"

#include <QVBoxLayout>

CurrentStatus::CurrentStatus(QWidget *parent) : QWidget(parent)
{
	QVBoxLayout *layout = new QVBoxLayout(this);
	song_title = new QLabel(this);
	song_artist = new QLabel(this);

	connect(mpdclient, SIGNAL(changedSong(const mpd_Song*)),
			this, SLOT(updateSong(const mpd_Song*)));

	setLayout(layout);
	layout->addWidget(song_title);
	layout->addWidget(song_artist);
}

void CurrentStatus::updateSong(const mpd_Song *new_song)
{
	song_title->setText(new_song->title);
	song_artist->setText(new_song->artist);
}
