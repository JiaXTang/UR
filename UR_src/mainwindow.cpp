#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 获取界面的ip字符串后创建控制UR的自定义对象(very very very iiiimportanttttt!)
    ipStr = ui->lineEdt_IPAdress->text();
    ptr_UR = CreateURer(ipStr.toUtf8().data());
    ui->pBtn_DisconnectUR->setDisabled(true);

    // 创建定时器
    timerTcpChgeDir = new QTimer(this);
    timerTcpChgePos = new QTimer(this);
    timerAxisChge = new QTimer(this);

    // 创建子线程、传递pt_UR到子线程、启动子线程
    urInfoThr = new URInfoThread(this);
    connect(this, &MainWindow::sendUR_ptr, urInfoThr, &URInfoThread::recvUR_ptr);
    emit sendUR_ptr(ptr_UR);
    urInfoThr->start();

    // 通过匿名槽函数，更新界面的数据
    connect(urInfoThr, &URInfoThread::sendPosInfo, this, [=](sixDoubleStruct posInfo){
        ui->lineEdit_X->setText(QString::number(posInfo.v_1, 'f', 2));
        ui->lineEdit_Y->setText(QString::number(posInfo.v_2, 'f', 2));
        ui->lineEdit_Z->setText(QString::number(posInfo.v_3 - 400, 'f', 2));
        ui->lineEdit_RX->setText(QString::number(posInfo.v_4, 'f', 2));
        ui->lineEdit_RY->setText(QString::number(posInfo.v_5, 'f', 2));
        ui->lineEdit_RZ->setText(QString::number(posInfo.v_6, 'f', 2));
    });

    connect(urInfoThr, &URInfoThread::sendJoiInfo, this, [=](sixDoubleStruct joiInfo){
        ui->lineEdit_base->setText(QString::number(joiInfo.v_1, 'f', 2));
        ui->lineEdit_shoulder->setText(QString::number(joiInfo.v_2, 'f', 2));
        ui->lineEdit_elbow->setText(QString::number(joiInfo.v_3, 'f', 2));
        ui->lineEdit_wrist1->setText(QString::number(joiInfo.v_4, 'f', 2));
        ui->lineEdit_wrist2->setText(QString::number(joiInfo.v_5, 'f', 2));
        ui->lineEdit_wrist3->setText(QString::number(joiInfo.v_6, 'f', 2));
        ui->Slider_Base->setValue(static_cast<int>(round(joiInfo.v_1)));
        ui->Slider_Shoulder->setValue(static_cast<int>(round(joiInfo.v_2)));
        ui->Slider_Elbow->setValue(static_cast<int>(round(joiInfo.v_3)));
        ui->Slider_Wrist1->setValue(static_cast<int>(round(joiInfo.v_4)));
        ui->Slider_Wrist2->setValue(static_cast<int>(round(joiInfo.v_5)));
        ui->Slider_Wrist3->setValue(static_cast<int>(round(joiInfo.v_6)));
    });
    //设置tabWidget的当前活动页
    ui->tabWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    if(ptr_UR->GetConnectionStatus() != STOPPED) {
        ptr_UR->CloseConnectToUR();
    }

    // 停止并销毁子线程资源
    urInfoThr->runflag = false; //关闭线程启动阀门
    urInfoThr->exit();
    urInfoThr->wait();

    delete ptr_UR;
    delete ui;
}

void MainWindow::shutDownTimer(QTimer* pt_timer) {
    if(pt_timer != nullptr) {
        pt_timer->stop();
        pt_timer->disconnect();
    }
}

void MainWindow::on_pBtn_ConnectUR_clicked()
{
    if(ptr_UR->ConnectToUR() == true) {
        QMessageBox::information(this, "Connection Status", "Connect Success!");
        ui->pBtn_ConnectUR->setDisabled(true);
        ui->pBtn_DisconnectUR->setEnabled(true);
    } else {
        QMessageBox::critical(this, "Connection Status", "Connect Failed!");
    }
}

void MainWindow::on_pBtn_DisconnectUR_clicked()
{
    ptr_UR->CloseConnectToUR();
    QMessageBox::information(this, "Connection Status", "Disable Connection!");
    ui->pBtn_ConnectUR->setEnabled(true);
    ui->pBtn_DisconnectUR->setDisabled(true);
}

void MainWindow::on_pBtn_BackZero_clicked()
{
    if(QMessageBox::question(this, "Caution!" ,"Really to Go Back to Zero Point?") == QMessageBox::Yes){
        ptr_UR->GoBackZero();
    }
}

void MainWindow::on_pBtn_BackStart_clicked()
{
    ptr_UR->GoBackStart();
}

void MainWindow::on_pBtn_StopJoint_clicked()
{
    ptr_UR->StopAllJoint();
}

void MainWindow::on_pBtn_Powerdown_clicked()
{
    string msg = ptr_UR->Shutdown();
    QMessageBox::information(this, "UR Status", QString::fromStdString(msg));
}

void MainWindow::on_pBtn_BreakRelease_clicked()
{
    string msg = ptr_UR->BreakRelease();
    QMessageBox::information(this, "UR Status", QString::fromStdString(msg));
}

void MainWindow::on_pBtn_Poweron_clicked()
{
    string msg = ptr_UR->PowerOn();
    QMessageBox::information(this, "UR Status", QString::fromStdString(msg));
}

void MainWindow::on_pBtn_Poweroff_clicked()
{
    string msg = ptr_UR->PowerOff();
    QMessageBox::information(this, "UR Status", QString::fromStdString(msg));
}

void MainWindow::on_tBtn_TCPZDirDec_pressed()
{
    //启动定时器timerTcpChgeDir，每隔180ms发送一次指令
    timerTcpChgeDir->start(180);
    connect(timerTcpChgeDir, &QTimer::timeout, [=](){
        this->ptr_UR->TcpDirZDec();
    });
}

void MainWindow::on_tBtn_TCPZDirDec_released()
{
    shutDownTimer(timerTcpChgeDir);
}

void MainWindow::on_tBtn_TCPZDirAdd_pressed()
{
    timerTcpChgeDir->start(180);
    connect(timerTcpChgeDir, &QTimer::timeout, [=](){
        this->ptr_UR->TcpDirZAdd();
    });
}

void MainWindow::on_tBtn_TCPZDirAdd_released()
{
    shutDownTimer(timerTcpChgeDir);
}

void MainWindow::on_tBtn_TCPXDirDec_pressed()
{
    timerTcpChgeDir->start(180);
    connect(timerTcpChgeDir, &QTimer::timeout, [=](){
        this->ptr_UR->TcpDirXDec();
    });
}

void MainWindow::on_tBtn_TCPXDirDec_released()
{
    shutDownTimer(timerTcpChgeDir);
}

void MainWindow::on_tBtn_TCPXDirAdd_pressed()
{
    timerTcpChgeDir->start(180);
    connect(timerTcpChgeDir, &QTimer::timeout, [=](){
        this->ptr_UR->TcpDirXAdd();
    });
}

void MainWindow::on_tBtn_TCPXDirAdd_released()
{
    shutDownTimer(timerTcpChgeDir);
}

void MainWindow::on_tBtn_TCPYDirDec_pressed()
{
    timerTcpChgeDir->start(180);
    connect(timerTcpChgeDir, &QTimer::timeout, [=](){
        this->ptr_UR->TcpDirYDec();
    });
}

void MainWindow::on_tBtn_TCPYDirDec_released()
{
    shutDownTimer(timerTcpChgeDir);
}

void MainWindow::on_tBtn_TCPYDirAdd_pressed()
{
    timerTcpChgeDir->start(180);
    connect(timerTcpChgeDir, &QTimer::timeout, [=](){
        this->ptr_UR->TcpDirYAdd();
    });
}

void MainWindow::on_tBtn_TCPYDirAdd_released()
{
    shutDownTimer(timerTcpChgeDir);
}

void MainWindow::on_tBtn_TCPZPosDec_pressed()
{
    connect(timerTcpChgePos, &QTimer::timeout, [=](){
        this->ptr_UR->TcpPosZDec();
    });
    timerTcpChgePos->start(180);
}

void MainWindow::on_tBtn_TCPZPosDec_released()
{
    shutDownTimer(timerTcpChgePos);
}

void MainWindow::on_tBtn_TCPZPosAdd_pressed()
{
    connect(timerTcpChgePos, &QTimer::timeout, [=](){
        this->ptr_UR->TcpPosZAdd();
    });
    timerTcpChgePos->start(180);
}

void MainWindow::on_tBtn_TCPZPosAdd_released()
{
    shutDownTimer(timerTcpChgePos);
}

void MainWindow::on_tBtn_TCPXPosDec_pressed()
{
    connect(timerTcpChgePos, &QTimer::timeout, [=](){
        this->ptr_UR->TcpPosXDec();
    });
    timerTcpChgePos->start(180);
}

void MainWindow::on_tBtn_TCPXPosDec_released()
{
    shutDownTimer(timerTcpChgePos);
}

void MainWindow::on_tBtn_TCPXPosAdd_pressed()
{
    connect(timerTcpChgePos, &QTimer::timeout, [=](){
        this->ptr_UR->TcpPosXAdd();
    });
    timerTcpChgePos->start(180);
}

void MainWindow::on_tBtn_TCPXPosAdd_released()
{
    shutDownTimer(timerTcpChgePos);
}

void MainWindow::on_tBtn_TCPYPosDec_pressed()
{
    connect(timerTcpChgePos, &QTimer::timeout, [=](){
        this->ptr_UR->TcpPosYDec();
    });
    timerTcpChgePos->start(180);
}

void MainWindow::on_tBtn_TCPYPosDec_released()
{
    shutDownTimer(timerTcpChgePos);
}

void MainWindow::on_tBtn_TCPYPosAdd_pressed()
{
    connect(timerTcpChgePos, &QTimer::timeout, [=](){
        this->ptr_UR->TcpPosYAdd();
    });
    timerTcpChgePos->start(180);
}

void MainWindow::on_tBtn_TCPYPosAdd_released()
{
    shutDownTimer(timerTcpChgePos);
}

void MainWindow::on_tBtn_URBaseDec_pressed()
{
    connect(timerAxisChge, &QTimer::timeout, [=](){
        this->ptr_UR->DecBaseJoint();
    });
    timerAxisChge->start(180);
}

void MainWindow::on_tBtn_URBaseDec_released()
{
    shutDownTimer(timerAxisChge);
}

void MainWindow::on_tBtn_URBaseAdd_pressed()
{
    connect(timerAxisChge, &QTimer::timeout, [=](){
        this->ptr_UR->AddBaseJoint();
    });
    timerAxisChge->start(180);
}

void MainWindow::on_tBtn_URBaseAdd_released()
{
    shutDownTimer(timerAxisChge);
}

void MainWindow::on_tBtn_URShoulderDec_pressed()
{
    connect(timerAxisChge, &QTimer::timeout, [=](){
        this->ptr_UR->DecShoulderJoint();
    });
    timerAxisChge->start(180);
}

void MainWindow::on_tBtn_URShoulderDec_released()
{
    shutDownTimer(timerAxisChge);
}

void MainWindow::on_tBtn_URShoulderAdd_pressed()
{
    connect(timerAxisChge, &QTimer::timeout, [=](){
        this->ptr_UR->AddShoulderJoint();
    });
    timerAxisChge->start(180);
}

void MainWindow::on_tBtn_URShoulderAdd_released()
{
    shutDownTimer(timerAxisChge);
}

void MainWindow::on_tBtn_URElbowDec_pressed()
{
    connect(timerAxisChge, &QTimer::timeout, [=](){
        this->ptr_UR->DecElbowJoint();
    });
    timerAxisChge->start(180);
}

void MainWindow::on_tBtn_URElbowDec_released()
{
    shutDownTimer(timerAxisChge);
}

void MainWindow::on_tBtn_URElbowAdd_pressed()
{
    connect(timerAxisChge, &QTimer::timeout, [=](){
        this->ptr_UR->AddElbowJoint();
    });
    timerAxisChge->start(180);
}

void MainWindow::on_tBtn_URElbowAdd_released()
{
    shutDownTimer(timerAxisChge);
}

void MainWindow::on_tBtn_URWrist1Dec_pressed()
{
    connect(timerAxisChge, &QTimer::timeout, [=](){
        this->ptr_UR->DecWrist1Joint();
    });
    timerAxisChge->start(180);
}

void MainWindow::on_tBtn_URWrist1Dec_released()
{
    shutDownTimer(timerAxisChge);
}

void MainWindow::on_tBtn_URWrist1Add_pressed()
{
    connect(timerAxisChge, &QTimer::timeout, [=](){
        this->ptr_UR->AddWrist1Joint();
    });
    timerAxisChge->start(180);
}

void MainWindow::on_tBtn_URWrist1Add_released()
{
    shutDownTimer(timerAxisChge);
}

void MainWindow::on_tBtn_URWrist2Dec_pressed()
{
    connect(timerAxisChge, &QTimer::timeout, [=](){
        this->ptr_UR->DecWrist2Joint();
    });
    timerAxisChge->start(180);
}

void MainWindow::on_tBtn_URWrist2Dec_released()
{
    shutDownTimer(timerAxisChge);
}

void MainWindow::on_tBtn_URWrist2Add_pressed()
{
    connect(timerAxisChge, &QTimer::timeout, [=](){
        this->ptr_UR->AddWrist2Joint();
    });
    timerAxisChge->start(180);
}

void MainWindow::on_tBtn_URWrist2Add_released()
{
    shutDownTimer(timerAxisChge);
}

void MainWindow::on_tBtn_URWrist3Dec_pressed()
{
    connect(timerAxisChge, &QTimer::timeout, [=](){
        this->ptr_UR->DecWrist3Joint();
    });
    timerAxisChge->start(180);
}

void MainWindow::on_tBtn_URWrist3Dec_released()
{
    shutDownTimer(timerAxisChge);
}

void MainWindow::on_tBtn_URWrist3Add_pressed()
{
    connect(timerAxisChge, &QTimer::timeout, [=](){
        this->ptr_UR->AddWrist3Joint();
    });
    timerAxisChge->start(180);
}

void MainWindow::on_tBtn_URWrist3Add_released()
{
    shutDownTimer(timerAxisChge);
}

void MainWindow::on_pBtn_MoveTo_clicked()
{
    sixDoubleStruct targetPos;
    targetPos.v_1 = ui->lineEdit_X_target->text().toDouble();
    targetPos.v_2 = ui->lineEdit_Y_target->text().toDouble();
    targetPos.v_3 = ui->lineEdit_Z_target->text().toDouble() + 400.0;
    targetPos.v_4 = ui->lineEdit_RX_target->text().toDouble();
    targetPos.v_5 = ui->lineEdit_RY_target->text().toDouble();
    targetPos.v_6 = ui->lineEdit_RZ_target->text().toDouble();

    ptr_UR->GoToTargetPos(targetPos);
}
