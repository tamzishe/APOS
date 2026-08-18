#include "mainwindow.h"
#include "musicscanner.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_model = new SongModel(this);

    m_listView = new QListView(this);
    m_listView->setModel(m_model);

    setCentralWidget(m_listView);
    setWindowTitle("APOS Music Player");
    resize(400, 600);

    // Hardcoded for now, per the current scope — swap for a folder
    // picker (QFileDialog::getExistingDirectory) once this works.
    loadMusicFolder("C:/Users/tamzm/Music");
}

void MainWindow::loadMusicFolder(const QString &folderPath)
{
    const QVector<Song> songs = MusicScanner::scanFolder(folderPath);
    m_model->setSongs(songs);
}
