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

    m_nowPlaying = new NowPlayingWidget(this);
 
    m_stack = new QStackedWidget(this);
    m_stack->addWidget(m_listView);   // index 0
    m_stack->addWidget(m_nowPlaying); // index 1

    connect(m_listView, &QListView::clicked, this, &MainWindow::onSongClicked);
    connect(m_nowPlaying, &NowPlayingWidget::backRequested, this, [this]() {
        m_stack->setCurrentWidget(m_listView);
    });

    mp = new MusicPlayer();

    setCentralWidget(m_stack);
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
    if (file_path == m_currentPlayingPath) {
        Song song;
        song.title  = idx.data(SongModel::TitleRole).toString();
        song.artist = idx.data(SongModel::ArtistRole).toString();
        song.coverArt = idx.data(SongModel::CoverArtRole).value<QImage>();

        m_nowPlaying->setSong(song);
        m_stack->setCurrentWidget(m_nowPlaying);
    } else {
        mp->playSong(file_path);
        m_currentPlayingPath = file_path;
    }
}
