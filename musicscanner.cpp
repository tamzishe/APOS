#include "musicscanner.h"

#include <QDirIterator>
#include <QFileInfo>
#include <QMediaPlayer>
#include <QMediaMetaData>
#include <QEventLoop>
#include <QUrl>

QVector<Song> MusicScanner::scanFolder(const QString &folderPath)
{
    QVector<Song> songs;

    QStringList filters;
    filters << "*.mp3" << "*.flac" << "*.wav" << "*.m4a" << "*.ogg";

    QDirIterator it(folderPath, filters, QDir::Files, QDirIterator::Subdirectories);

    while (it.hasNext()) {
        const QString filePath = it.next();

        // QMediaPlayer loads metadata asynchronously, so we spin a local
        // event loop per file and wait for it to finish (or fail) before
        // moving to the next one. Simple and fine for a first version;
        // if scanning a large library gets slow, this is the first place
        // to revisit (e.g. move scanning to a background thread).
        QMediaPlayer player;
        QEventLoop loop;

        QObject::connect(&player, &QMediaPlayer::mediaStatusChanged, &loop,
            [&loop](QMediaPlayer::MediaStatus status) {
                if (status == QMediaPlayer::LoadedMedia ||
                    status == QMediaPlayer::InvalidMedia) {
                    loop.quit();
                }
            });

        player.setSource(QUrl::fromLocalFile(filePath));
        loop.exec();

        Song song;
        song.filePath = filePath;

        const QMediaMetaData meta = player.metaData();
        song.title  = meta.stringValue(QMediaMetaData::Title);
        song.artist = meta.stringValue(QMediaMetaData::ContributingArtist);
        song.album  = meta.stringValue(QMediaMetaData::AlbumTitle);

        // Fall back to something sensible if tags are missing/empty.
        if (song.title.isEmpty())
            song.title = QFileInfo(filePath).completeBaseName();
        if (song.artist.isEmpty())
            song.artist = QStringLiteral("Unknown Artist");
        if (song.album.isEmpty())
            song.album = QStringLiteral("Unknown Album");

        songs.append(song);
    }

    return songs;
}
