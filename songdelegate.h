#pragma once
#include <QStyledItemDelegate>

class SongDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    explicit SongDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const override;
};