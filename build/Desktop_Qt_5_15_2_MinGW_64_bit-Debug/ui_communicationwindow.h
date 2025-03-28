/********************************************************************************
** Form generated from reading UI file 'communicationwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMMUNICATIONWINDOW_H
#define UI_COMMUNICATIONWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CommunicationWindow
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *ipLineEdit;
    QLabel *label_2;
    QLineEdit *portSpinBox;
    QPushButton *connectButton;
    QLabel *modeLabel;
    QTextEdit *messagesTextEdit;
    QLineEdit *messageLineEdit;
    QPushButton *backButton;
    QPushButton *sendButton;
    QLabel *statusLabel;

    void setupUi(QWidget *CommunicationWindow)
    {
        if (CommunicationWindow->objectName().isEmpty())
            CommunicationWindow->setObjectName(QString::fromUtf8("CommunicationWindow"));
        CommunicationWindow->resize(515, 389);
        gridLayout = new QGridLayout(CommunicationWindow);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(CommunicationWindow);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        ipLineEdit = new QLineEdit(CommunicationWindow);
        ipLineEdit->setObjectName(QString::fromUtf8("ipLineEdit"));

        gridLayout->addWidget(ipLineEdit, 0, 1, 1, 2);

        label_2 = new QLabel(CommunicationWindow);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 3, 1, 1);

        portSpinBox = new QLineEdit(CommunicationWindow);
        portSpinBox->setObjectName(QString::fromUtf8("portSpinBox"));

        gridLayout->addWidget(portSpinBox, 0, 4, 1, 1);

        connectButton = new QPushButton(CommunicationWindow);
        connectButton->setObjectName(QString::fromUtf8("connectButton"));

        gridLayout->addWidget(connectButton, 0, 5, 1, 1);

        modeLabel = new QLabel(CommunicationWindow);
        modeLabel->setObjectName(QString::fromUtf8("modeLabel"));

        gridLayout->addWidget(modeLabel, 3, 0, 1, 2);

        messagesTextEdit = new QTextEdit(CommunicationWindow);
        messagesTextEdit->setObjectName(QString::fromUtf8("messagesTextEdit"));

        gridLayout->addWidget(messagesTextEdit, 1, 0, 1, 6);

        messageLineEdit = new QLineEdit(CommunicationWindow);
        messageLineEdit->setObjectName(QString::fromUtf8("messageLineEdit"));

        gridLayout->addWidget(messageLineEdit, 2, 0, 1, 6);

        backButton = new QPushButton(CommunicationWindow);
        backButton->setObjectName(QString::fromUtf8("backButton"));

        gridLayout->addWidget(backButton, 3, 5, 1, 1);

        sendButton = new QPushButton(CommunicationWindow);
        sendButton->setObjectName(QString::fromUtf8("sendButton"));
        sendButton->setMinimumSize(QSize(80, 0));

        gridLayout->addWidget(sendButton, 3, 4, 1, 1);

        statusLabel = new QLabel(CommunicationWindow);
        statusLabel->setObjectName(QString::fromUtf8("statusLabel"));

        gridLayout->addWidget(statusLabel, 3, 2, 1, 2);


        retranslateUi(CommunicationWindow);

        QMetaObject::connectSlotsByName(CommunicationWindow);
    } // setupUi

    void retranslateUi(QWidget *CommunicationWindow)
    {
        CommunicationWindow->setWindowTitle(QCoreApplication::translate("CommunicationWindow", "Form", nullptr));
        label->setText(QCoreApplication::translate("CommunicationWindow", "\347\233\256\346\240\207IP:", nullptr));
        label_2->setText(QCoreApplication::translate("CommunicationWindow", "\347\253\257\345\217\243\345\217\267\357\274\232", nullptr));
        connectButton->setText(QCoreApplication::translate("CommunicationWindow", "\350\277\236\346\216\245", nullptr));
        modeLabel->setText(QCoreApplication::translate("CommunicationWindow", "TextLabel", nullptr));
        backButton->setText(QCoreApplication::translate("CommunicationWindow", "\350\277\224\345\233\236\346\214\211\351\222\256", nullptr));
        sendButton->setText(QCoreApplication::translate("CommunicationWindow", "\345\217\221\351\200\201\346\214\211\351\222\256", nullptr));
        statusLabel->setText(QCoreApplication::translate("CommunicationWindow", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CommunicationWindow: public Ui_CommunicationWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMMUNICATIONWINDOW_H
