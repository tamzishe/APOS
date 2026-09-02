#pragma once
#include <QString>
#include <QMediaPlayer>
#include <QAudioOutput>

class MusicPlayer {
private:
    QMediaPlayer player;
    QAudioOutput audioOut;
public:
    void playSong(const QString &songPath);
    void pauseSong();
    void resume();
    void togglePlayPause();
    void restart();
    qint64 position() const;
    void increaseVolume();
    void decreaseVolume();
    float getVolume();
    MusicPlayer();
};


