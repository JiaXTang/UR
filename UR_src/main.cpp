#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    // 适配高分屏
    if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0)) {
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling,true);
    }
    QApplication a(argc, argv);
    // 注册自定义结构sixDoubleStruct
    qRegisterMetaType<sixDoubleStruct>("sixDoubleStruct");
    MainWindow w;
    w.show();

    return a.exec();
}
