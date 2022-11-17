#ifndef LINESCANNING_H
#define LINESCANNING_H

#include <QWidget>

namespace Ui {
class LineScanning;
}

class LineScanning : public QWidget
{
    Q_OBJECT

public:
    explicit LineScanning(QWidget *parent = nullptr);
    ~LineScanning();

private:
    Ui::LineScanning *ui;
};

#endif // LINESCANNING_H
