#include "mydock.h"
#include "ui_mydock.h"

mydock::mydock(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mydock)
{
    ui->setupUi(this);
}

mydock::~mydock()
{
    delete ui;
}
