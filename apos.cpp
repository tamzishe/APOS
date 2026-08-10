#include "apos.h"
#include "ui_apos.h"

APOS::APOS(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::APOS)
{
    ui->setupUi(this);
}

APOS::~APOS()
{
    delete ui;
}
