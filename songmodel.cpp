#include "songmodel.h"

SongModel::SongModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int SongModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return m_songs.size();
}

QVariant SongModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_songs.size())
        return QVariant();

    const Song &song = m_songs.at(index.row());

    switch (role) {
    case Qt::DisplayRole:
    case TitleRole:
        return song.title;
    case ArtistRole:
        return song.artist;
    case AlbumRole:
        return song.album;
    case FilePathRole:
        return song.filePath;
    default:
        return QVariant();
    }
}

void SongModel::setSongs(const QVector<Song> &songs)
{
    beginResetModel();
    m_songs = songs;
    endResetModel();
}

QHash<int, QByteArray> SongModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[TitleRole] = "title";
    roles[ArtistRole] = "artist";
    roles[AlbumRole] = "album";
    roles[FilePathRole] = "filePath";
    return roles;
}
