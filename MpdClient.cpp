
#include <MpdClient.h>
#include <util.h>

#include <stdlib.h> /* for getenv, atoi */
#include <assert.h>
#include <QTimer>

MpdClient::MpdClient(QObject *parent) : QObject(parent)
{
	conn = NULL;
	status = NULL;
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

	if (conn->error) {
		error(conn->errorStr);
		return false;
	}

	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));
	timer->start(1000);

	return true;
}

void MpdClient::update()
{
	mpd_sendCommandListOkBegin(conn);
	mpd_sendStatusCommand(conn);

	if (status == NULL)
		mpd_sendPlaylistInfoCommand(conn, -1);
	else
		mpd_sendPlChangesCommand(conn, status->playlist);

	mpd_sendCommandListEnd(conn);

	status = mpd_getStatus(conn);
	assert(status);
	mpd_nextListOkCommand(conn);

	mpd_InfoEntity *entity;
	while ((entity = mpd_getNextInfoEntity(conn))) {
		assert(entity->type == MPD_INFO_ENTITY_TYPE_SONG);

		mpd_Song *song = mpd_songDup(entity->info.song);
		mpd_freeInfoEntity(entity);

		assert(song->pos <= playlist.size());

		if (song->pos == playlist.size())
			playlist += song;
		else {
			mpd_freeSong(playlist[song->pos]);
			playlist[song->pos] = song;
		}
	}

	mpd_finishCommand(conn);

	/* remove extra songs if the playlist was shortened */
	for (int i = playlist.size() - 1; i >= status->playlistLength; i--) {
		mpd_freeSong(playlist[i]);
		playlist.removeAt(i);
	}
}

mpd_Song* MpdClient::currentSong()
{
	assert(status);
	return playlist[status->song];
}
