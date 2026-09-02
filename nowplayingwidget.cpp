#include "nowplayingwidget.h"
#include <QVBoxLayout>
#include <QPixmap>

NowPlayingWidget::NowPlayingWidget(QWidget *parent)
    : QWidget(parent)
{
    m_backButton = new QPushButton("< Back", this);

    m_coverLabel = new QLabel(this);
    m_coverLabel->setAlignment(Qt::AlignCenter);
    m_coverLabel->setFixedSize(300, 300); // enlarged, vs. ~64px in the list row

    m_titleLabel = new QLabel(this);
    m_titleLabel->setAlignment(Qt::AlignCenter);
    QFont titleFont = m_titleLabel->font();
    titleFont.setBold(true);
    titleFont.setPointSize(titleFont.pointSize() + 4);
    m_titleLabel->setFont(titleFont);

    m_artistLabel = new QLabel(this);
    m_artistLabel->setAlignment(Qt::AlignCenter);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(m_backButton, 0, Qt::AlignLeft);
    layout->addStretch();
    layout->addWidget(m_coverLabel, 0, Qt::AlignCenter);
    layout->addWidget(m_titleLabel);
    layout->addWidget(m_artistLabel);
    layout->addStretch();
    
    // add progress bar/slider later

    connect(m_backButton, &QPushButton::clicked, this, &NowPlayingWidget::backRequested);
}

void NowPlayingWidget::setSong(const Song &song)
{
    m_titleLabel->setText(song.title);
    m_artistLabel->setText(song.artist);

    if (!song.coverArt.isNull()) {
        QPixmap pixmap = QPixmap::fromImage(song.coverArt).scaled(
            m_coverLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        m_coverLabel->setPixmap(pixmap);
    } else {
        m_coverLabel->clear();
        m_coverLabel->setStyleSheet("background-color: palette(mid);");
    }
}