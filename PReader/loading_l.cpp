#include "loading_l.h"
#include "ui_loading_l.h"

Loading_l::Loading_l(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Loading_l)
{
    ui->setupUi(this);
}

Loading_l::~Loading_l()
{
    delete ui;
}
