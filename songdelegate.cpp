#include "songdelegate.h"
#include "songmodel.h"

#include <QPainter>
#include <QApplication>

SongDelegate::SongDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

void SongDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                         const QModelIndex &index) const
{
    painter->save();

    const QString title  = index.data(SongModel::TitleRole).toString();
    const QString artist = index.data(SongModel::ArtistRole).toString();
    const QImage cover = index.data(SongModel::CoverArtRole).value<QImage>();
    const QRect rect = option.rect;

    // selection highlight
    if (option.state & QStyle::State_Selected) {
        painter->fillRect(rect, option.palette.highlight());
        painter->setPen(option.palette.color(QPalette::HighlightedText));
    } else {
        painter->setPen(option.palette.color(QPalette::Text));
    }

    const int artSize = rect.height() - 8;
    const QRect artRect(rect.left() + 4, rect.top() + 4, artSize, artSize);
    if (!cover.isNull()) {
        const QImage scaled = cover.scaled(artRect.size(),
                                           Qt::KeepAspectRatio,
                                           Qt::SmoothTransformation);

        const QPoint offset((artRect.width() - scaled.width()) / 2,
                            (artRect.height() - scaled.height()) / 2);
        painter->drawImage(artRect.topLeft() + offset, scaled);
    } else {
        painter->fillRect(artRect, option.palette.color(QPalette::Mid));
    }
    const int textLeft = artRect.right() + 12;
    const QRect textRect(textLeft, rect.top(), rect.right() - textLeft, rect.height());


    QFont titleFont = painter->font();
    titleFont.setBold(true);
    painter->setFont(titleFont);
    const QRect titleRect(textRect.left(), textRect.top(),
                          textRect.width(), textRect.height() / 2);
    painter->drawText(titleRect, Qt::AlignLeft | Qt::AlignVCenter, title);


    QFont artistFont = painter->font();
    artistFont.setBold(false);
    artistFont.setPointSize(qMax(artistFont.pointSize() - 1, 6));
    painter->setFont(artistFont);
    if (!(option.state & QStyle::State_Selected)) {
        painter->setPen(option.palette.color(QPalette::Disabled, QPalette::Text));
    }
    const QRect artistRect(textRect.left(), textRect.top() + textRect.height() / 2,
                           textRect.width(), textRect.height() / 2);
    painter->drawText(artistRect, Qt::AlignLeft | Qt::AlignVCenter, artist);

    painter->restore();
}

QSize SongDelegate::sizeHint(const QStyleOptionViewItem &option,
                             const QModelIndex &index) const
{
    QSize size = QStyledItemDelegate::sizeHint(option, index);
    size.setHeight(72);
    return size;
}