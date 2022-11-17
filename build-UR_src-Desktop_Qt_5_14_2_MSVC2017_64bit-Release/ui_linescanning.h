/********************************************************************************
** Form generated from reading UI file 'linescanning.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LINESCANNING_H
#define UI_LINESCANNING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LineScanning
{
public:

    void setupUi(QWidget *LineScanning)
    {
        if (LineScanning->objectName().isEmpty())
            LineScanning->setObjectName(QString::fromUtf8("LineScanning"));
        LineScanning->resize(668, 451);

        retranslateUi(LineScanning);

        QMetaObject::connectSlotsByName(LineScanning);
    } // setupUi

    void retranslateUi(QWidget *LineScanning)
    {
        LineScanning->setWindowTitle(QCoreApplication::translate("LineScanning", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LineScanning: public Ui_LineScanning {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LINESCANNING_H
