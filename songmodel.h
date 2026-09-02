#pragma once
#include <QAbstractListModel>
#include <QVector>
#include "song.h"

// Holds the scanned song list and feeds it to whatever view is attached
// (a QListView in our case). This is the single source of truth for
// song data — the view itself holds nothing.
class SongModel : public QAbstractListModel {
    Q_OBJECT
public:
    enum Roles {
        TitleRole = Qt::UserRole + 1,
        ArtistRole,
        AlbumRole,
        FilePathRole
    };

    explicit SongModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void setSongs(const QVector<Song> &songs);

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QVector<Song> m_songs;
};
