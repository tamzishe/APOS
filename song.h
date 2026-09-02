#pragma once
#include <QString>

// Plain data holder for one scanned audio file's info.
struct Song {
    QString title;
    QString artist;
    QString album;
    QString filePath;
};
