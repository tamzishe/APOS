#include "mainwindow.h"
#include "musicscanner.h"
#include "musicplayer.h"
#include "songdelegate.h"
#include <QKeyEvent>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_model = new SongModel(this);

    m_listView = new QListView(this);
    m_listView->setModel(m_model);
    m_listView->setItemDelegate(new SongDelegate(this));
    m_listView->setFocusPolicy(Qt::NoFocus);

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
    // resize(400, 600);
    setFixedSize(320, 480);

    setFocusPolicy(Qt::StrongFocus);
    setFocus();

    // Hardcoded for now, per the current scope
    // swap for a folder picker (QFileDialog::getExistingDirectory) once this works.
    QTimer::singleShot(0, this, [this]() {
        loadMusicFolder("C:/Users/tamzm/Music");
    });
}

void MainWindow::loadMusicFolder(const QString &folder_path){
    const QVector<Song> songs = MusicScanner::scanFolder(folder_path);
    m_model->setSongs(songs);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Left:
        onPreviousPressed();
        break;
 
    case Qt::Key_Right:
        onNextPressed();
        break;
 
    case Qt::Key_Down:
        if (m_stack->currentWidget() == m_nowPlaying) {
            m_stack->setCurrentWidget(m_listView);
        } else {
            moveSelection(1);
        }
        break;
 
    case Qt::Key_Up:
        if (m_stack->currentWidget() == m_nowPlaying) {
            mp->togglePlayPause();
        } else {
            moveSelection(-1);
        }
        break;
 
    case Qt::Key_Return:
    case Qt::Key_Enter:
        activateSong(m_listView->currentIndex());
        break;
 
    case Qt::Key_Plus:
    case Qt::Key_Equal: // '+' and '='
        mp->increaseVolume();
        break;
 
    case Qt::Key_Minus:
        mp->decreaseVolume();
        break;
 
    default:
        QMainWindow::keyPressEvent(event);
        break;
    }
}
 
void MainWindow::activateSong(const QModelIndex &idx){
    if (!idx.isValid())
        return;
 
    if (idx.row() == m_currentRow) {
        Song song;
        song.title    = idx.data(SongModel::TitleRole).toString();
        song.artist   = idx.data(SongModel::ArtistRole).toString();
        song.coverArt = idx.data(SongModel::CoverArtRole).value<QImage>();
 
        m_nowPlaying->setSong(song);
        m_stack->setCurrentWidget(m_nowPlaying);
    } else {
        playRow(idx.row());
    }
}

void MainWindow::onSongClicked(const QModelIndex &idx){
    activateSong(idx);
}
void MainWindow::playRow(int row)
{
    const int rowCount = m_model->rowCount();
    if (rowCount == 0)
        return;

    row = std::clamp(row, 0, rowCount - 1);

    const QModelIndex idx = m_model->index(row, 0);
    const QString filePath = idx.data(SongModel::FilePathRole).toString();

    mp->playSong(filePath);
    m_currentRow = row;

    // highlighted row
    m_listView->setCurrentIndex(idx);

    // update the NowPlayingWidget with the current song's info
    Song song;
    song.title    = idx.data(SongModel::TitleRole).toString();
    song.artist   = idx.data(SongModel::ArtistRole).toString();
    song.coverArt = idx.data(SongModel::CoverArtRole).value<QImage>();
    m_nowPlaying->setSong(song);
}
 
void MainWindow::moveSelection(int delta){
    const int rowCount = m_model->rowCount();
    if (rowCount == 0)
        return;
 
    const QModelIndex current = m_listView->currentIndex();
    int row = current.isValid() ? current.row() : 0;
    row = std::clamp(row + delta, 0, rowCount - 1);
 
    m_listView->setCurrentIndex(m_model->index(row, 0));
}
 
void MainWindow::onPreviousPressed(){
    constexpr qint64 restartThresholdMs = 3000; // in milliseconds
 
    if (mp->position() < restartThresholdMs) {
        playRow(m_currentRow - 1); 
    } else {
        mp->restart();
    }
}
 
void MainWindow::onNextPressed(){
    playRow(m_currentRow + 1); 
}
 