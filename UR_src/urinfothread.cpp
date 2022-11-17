#include "urinfothread.h"

URInfoThread::URInfoThread(QObject *parent) : QThread(parent)
  ,urPtr(nullptr)
  ,runflag(true)
{
}

void URInfoThread::run()
{
    sixDoubleStruct tcpActPos, tcpJoiPos;
    while(runflag) {
        // UR必须处于已同步状态，才会尝试获取UR数据
        if(urPtr != nullptr && urPtr->GetConnectionStatus() == SYNCING){
            // 获取位置信息、角度信息
            urPtr->GetTcpActualPos(tcpActPos);
            urPtr->GetTcpJointsPos(tcpJoiPos);

            emit sendPosInfo(tcpActPos);
            emit sendJoiInfo(tcpJoiPos);
        }
        QThread::msleep(200);
    }
}

void URInfoThread::recvUR_ptr(IURInterface *ur_ptr)
{
    urPtr = ur_ptr;
}
