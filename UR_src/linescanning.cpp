#include "linescanning.h"
#include "ui_linescanning.h"

LineScanning::LineScanning(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LineScanning)
{
    ui->setupUi(this);
}

LineScanning::~LineScanning()
{
    delete ui;
}
