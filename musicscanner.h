#pragma once
#include <QVector>
#include <QString>
#include "song.h"

// Walks a folder (recursively) for audio files and reads their metadata.
class MusicScanner {
public:
    static QVector<Song> scanFolder(const QString &folderPath);
};
