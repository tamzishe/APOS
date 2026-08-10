#ifndef APOS_H
#define APOS_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class APOS;
}
QT_END_NAMESPACE

class APOS : public QMainWindow
{
    Q_OBJECT

public:
    explicit APOS(QWidget *parent = nullptr);
    ~APOS() override;

private:
    Ui::APOS *ui;
};
#endif // APOS_H
