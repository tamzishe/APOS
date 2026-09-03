#pragma once
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include "song.h"

class NowPlayingWidget : public QWidget {
    Q_OBJECT
public:
    explicit NowPlayingWidget(QWidget *parent = nullptr);

    void setSong(const Song &song);

signals:
    void backRequested();

private:
    QLabel *m_coverLabel;
    QLabel *m_titleLabel;
    QLabel *m_artistLabel;
    QPushButton *m_backButton;
};