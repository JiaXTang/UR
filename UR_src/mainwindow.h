#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QMessageBox>
#include <QTimer>

#include "urinfothread.h"
#include "URInterface.h"
#pragma comment(lib, "F:\\QT_Project\\UR\\UR\\UR_src\\Dll_Interface.lib") //最好取绝对路径

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    // 停掉pt_timer所指向的定时器，并断开该定时器连接的所有槽函数
    void shutDownTimer(QTimer* pt_timer);

private:
    Ui::MainWindow *ui;
    QString ipStr;
    IURInterface *ptr_UR;
    QTimer* timerTcpChgeDir;    // Timer_TCP_Change_Direction的缩写：表示负责TCP末端方向改变要用到的定时器
    QTimer* timerTcpChgePos;    // Timer_TCP_Change_Postion的缩写：表示负责TCP末端位置改变要用到的定时器
    QTimer* timerAxisChge;      // Timer_Axis_Change的缩写：表示负责UR机械臂6个轴单独运动时要用到的定时器
    URInfoThread* urInfoThr;    // 子线程

private slots:
    void on_pBtn_ConnectUR_clicked();
    void on_pBtn_DisconnectUR_clicked();
    void on_pBtn_BackZero_clicked();
    void on_pBtn_BackStart_clicked();
    void on_pBtn_StopJoint_clicked();
    void on_pBtn_Powerdown_clicked();
    void on_pBtn_BreakRelease_clicked();
    void on_pBtn_Poweron_clicked();
    void on_pBtn_Poweroff_clicked();

    void on_tBtn_TCPZDirDec_pressed();
    void on_tBtn_TCPZDirDec_released();
    void on_tBtn_TCPZDirAdd_pressed();
    void on_tBtn_TCPZDirAdd_released();
    void on_tBtn_TCPXDirDec_pressed();
    void on_tBtn_TCPXDirDec_released();
    void on_tBtn_TCPXDirAdd_pressed();
    void on_tBtn_TCPXDirAdd_released();
    void on_tBtn_TCPYDirDec_pressed();
    void on_tBtn_TCPYDirDec_released();
    void on_tBtn_TCPYDirAdd_pressed();
    void on_tBtn_TCPYDirAdd_released();

    void on_tBtn_TCPZPosDec_pressed();
    void on_tBtn_TCPZPosDec_released();
    void on_tBtn_TCPZPosAdd_pressed();
    void on_tBtn_TCPZPosAdd_released();
    void on_tBtn_TCPXPosDec_pressed();
    void on_tBtn_TCPXPosDec_released();
    void on_tBtn_TCPXPosAdd_pressed();
    void on_tBtn_TCPXPosAdd_released();
    void on_tBtn_TCPYPosDec_pressed();
    void on_tBtn_TCPYPosDec_released();
    void on_tBtn_TCPYPosAdd_pressed();
    void on_tBtn_TCPYPosAdd_released();

    void on_tBtn_URBaseDec_pressed();
    void on_tBtn_URBaseDec_released();
    void on_tBtn_URBaseAdd_pressed();
    void on_tBtn_URBaseAdd_released();
    void on_tBtn_URShoulderDec_pressed();
    void on_tBtn_URShoulderDec_released();
    void on_tBtn_URShoulderAdd_pressed();
    void on_tBtn_URShoulderAdd_released();
    void on_tBtn_URElbowDec_pressed();
    void on_tBtn_URElbowDec_released();
    void on_tBtn_URElbowAdd_pressed();
    void on_tBtn_URElbowAdd_released();
    void on_tBtn_URWrist1Dec_pressed();
    void on_tBtn_URWrist1Dec_released();
    void on_tBtn_URWrist1Add_pressed();
    void on_tBtn_URWrist1Add_released();
    void on_tBtn_URWrist2Dec_pressed();
    void on_tBtn_URWrist2Dec_released();
    void on_tBtn_URWrist2Add_pressed();
    void on_tBtn_URWrist2Add_released();
    void on_tBtn_URWrist3Dec_pressed();
    void on_tBtn_URWrist3Dec_released();
    void on_tBtn_URWrist3Add_pressed();
    void on_tBtn_URWrist3Add_released();

    void on_pBtn_MoveTo_clicked();

signals:
    void sendUR_ptr(IURInterface* ur_ptr);
};
#endif // MAINWINDOW_H
