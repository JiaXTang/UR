#ifndef URINFOTHREAD_H
#define URINFOTHREAD_H

#include <QThread>
#include "URInterface.h"

class URInfoThread : public QThread
{
    Q_OBJECT
public:
    explicit URInfoThread(QObject *parent = nullptr);

protected:
    void run() override;

signals:
    // (信号)发送信号，向线程之外传递数据
    void sendPosInfo(sixDoubleStruct ur_pos);
    void sendJoiInfo(sixDoubleStruct ur_joi);

public slots:
    // (槽函数)通过连接信号sendUR_ptr，实现接收主线程发来的ur_ptr
    void recvUR_ptr(IURInterface *ur_ptr);

private:
    IURInterface * urPtr;

public:
    // 线程启动阀门
    bool runflag;
};

#endif // URINFOTHREAD_H
