#pragma once
#include <QMainWindow>
#include <QListView>
#include <QStackedWidget>
#include "songmodel.h"
#include "musicplayer.h"
#include "nowplayingwidget.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    QStackedWidget *m_stack;
    QListView *m_listView;
    SongModel *m_model;
    MusicPlayer *mp;
    QString m_currentPlayingPath;
    NowPlayingWidget *m_nowPlaying;

    void loadMusicFolder(const QString &folderPath);
    void onSongClicked(const QModelIndex &idx);
};