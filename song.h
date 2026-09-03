#pragma once
#include <QString>
#include <QImage>

struct Song {
    QString title;
    QString artist;
    QString album;
    QString filePath;
    QImage coverArt;
};
