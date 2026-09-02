#pragma once
#include <QMainWindow>
#include <QListView>
#include "songmodel.h"
#include "musicplayer.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    QListView *m_listView;
    SongModel *m_model;
    MusicPlayer *mp;

    void loadMusicFolder(const QString &folderPath);
    void onSongClicked(const QModelIndex &idx);
};
