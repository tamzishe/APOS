#include "musicplayer.h"
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QUrl>

MusicPlayer::MusicPlayer(){
    player.setAudioOutput(&audioOut);
    audioOut.setVolume(0.5);
}

void MusicPlayer::playSong(const QString &songPath){
    player.setSource(QUrl::fromLocalFile(songPath));
    player.play();
}
void MusicPlayer::pauseSong(){
    player.pause();
}
// checking out of bound is not needed, QAudioOutput clamps internally from 0 to 1
// however, i'll keep it to avoid potential errors
void MusicPlayer::increaseVolume(){
    if (audioOut.volume() >= 0.999) return;
    audioOut.setVolume(audioOut.volume()+0.1);
}
void MusicPlayer::decreaseVolume(){
    if (audioOut.volume() <= 0.001) return;
    audioOut.setVolume(audioOut.volume()-0.1);
}
float MusicPlayer::getVolume(){
    return audioOut.volume();
}
