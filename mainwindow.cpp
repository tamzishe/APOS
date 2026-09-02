#include "mainwindow.h"
#include "musicscanner.h"
#include "musicplayer.h"
#include "songdelegate.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_model = new SongModel(this);

    m_listView = new QListView(this);
    m_listView->setModel(m_model);
    m_listView->setItemDelegate(new SongDelegate(this));
    connect(m_listView, &QListView::clicked, this, &MainWindow::onSongClicked);
    mp = new MusicPlayer();


    setCentralWidget(m_listView);
    setWindowTitle("APOS Music Player");
    resize(400, 600);

    // Hardcoded for now, per the current scope
    // swap for a folder picker (QFileDialog::getExistingDirectory) once this works.
    loadMusicFolder("C:/Users/tamzm/Music");
}

void MainWindow::loadMusicFolder(const QString &folder_path)
{
    const QVector<Song> songs = MusicScanner::scanFolder(folder_path);
    m_model->setSongs(songs);
}

void MainWindow::onSongClicked(const QModelIndex &idx){
    QString file_path = idx.data(SongModel::FilePathRole).toString();
    mp->playSong(file_path);
}
