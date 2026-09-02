#pragma once
#include <QString>
#include <QImage>

// Plain data holder for one scanned audio file's info.
struct Song {
    QString title;
    QString artist;
    QString album;
    QString filePath;
    QImage coverArt;
};
