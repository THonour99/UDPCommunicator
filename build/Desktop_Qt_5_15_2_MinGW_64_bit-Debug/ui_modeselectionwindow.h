/********************************************************************************
** Form generated from reading UI file 'modeselectionwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODESELECTIONWINDOW_H
#define UI_MODESELECTIONWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ModeSelectionWindow
{
public:
    QGridLayout *gridLayout;
    QPushButton *localButton;
    QPushButton *remoteButton;
    QLabel *label;

    void setupUi(QWidget *ModeSelectionWindow)
    {
        if (ModeSelectionWindow->objectName().isEmpty())
            ModeSelectionWindow->setObjectName(QString::fromUtf8("ModeSelectionWindow"));
        ModeSelectionWindow->resize(400, 300);
        gridLayout = new QGridLayout(ModeSelectionWindow);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        localButton = new QPushButton(ModeSelectionWindow);
        localButton->setObjectName(QString::fromUtf8("localButton"));

        gridLayout->addWidget(localButton, 1, 0, 1, 1);

        remoteButton = new QPushButton(ModeSelectionWindow);
        remoteButton->setObjectName(QString::fromUtf8("remoteButton"));

        gridLayout->addWidget(remoteButton, 1, 1, 1, 1);

        label = new QLabel(ModeSelectionWindow);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setPointSize(21);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 0, 0, 1, 2);


        retranslateUi(ModeSelectionWindow);

        QMetaObject::connectSlotsByName(ModeSelectionWindow);
    } // setupUi

    void retranslateUi(QWidget *ModeSelectionWindow)
    {
        ModeSelectionWindow->setWindowTitle(QCoreApplication::translate("ModeSelectionWindow", "Form", nullptr));
        localButton->setText(QCoreApplication::translate("ModeSelectionWindow", "\346\234\254\345\234\260\346\250\241\345\274\217", nullptr));
        remoteButton->setText(QCoreApplication::translate("ModeSelectionWindow", "\350\277\234\347\250\213\346\250\241\345\274\217", nullptr));
        label->setText(QCoreApplication::translate("ModeSelectionWindow", "\345\212\237\350\203\275\351\200\211\346\213\251", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ModeSelectionWindow: public Ui_ModeSelectionWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODESELECTIONWINDOW_H
