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
    QLabel *modeLabel;
    QTextEdit *messagesTextEdit;
    QPushButton *sendButton;
    QPushButton *backButton;
    QLineEdit *messageLineEdit;

    void setupUi(QWidget *CommunicationWindow)
    {
        if (CommunicationWindow->objectName().isEmpty())
            CommunicationWindow->setObjectName(QString::fromUtf8("CommunicationWindow"));
        CommunicationWindow->resize(400, 300);
        gridLayout = new QGridLayout(CommunicationWindow);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        modeLabel = new QLabel(CommunicationWindow);
        modeLabel->setObjectName(QString::fromUtf8("modeLabel"));

        gridLayout->addWidget(modeLabel, 0, 1, 1, 1);

        messagesTextEdit = new QTextEdit(CommunicationWindow);
        messagesTextEdit->setObjectName(QString::fromUtf8("messagesTextEdit"));

        gridLayout->addWidget(messagesTextEdit, 1, 0, 1, 3);

        sendButton = new QPushButton(CommunicationWindow);
        sendButton->setObjectName(QString::fromUtf8("sendButton"));

        gridLayout->addWidget(sendButton, 3, 0, 1, 1);

        backButton = new QPushButton(CommunicationWindow);
        backButton->setObjectName(QString::fromUtf8("backButton"));

        gridLayout->addWidget(backButton, 3, 2, 1, 1);

        messageLineEdit = new QLineEdit(CommunicationWindow);
        messageLineEdit->setObjectName(QString::fromUtf8("messageLineEdit"));

        gridLayout->addWidget(messageLineEdit, 2, 0, 1, 3);


        retranslateUi(CommunicationWindow);

        QMetaObject::connectSlotsByName(CommunicationWindow);
    } // setupUi

    void retranslateUi(QWidget *CommunicationWindow)
    {
        CommunicationWindow->setWindowTitle(QCoreApplication::translate("CommunicationWindow", "Form", nullptr));
        modeLabel->setText(QCoreApplication::translate("CommunicationWindow", "TextLabel", nullptr));
        sendButton->setText(QCoreApplication::translate("CommunicationWindow", "\345\217\221\351\200\201\346\214\211\351\222\256", nullptr));
        backButton->setText(QCoreApplication::translate("CommunicationWindow", "\350\277\224\345\233\236\346\214\211\351\222\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CommunicationWindow: public Ui_CommunicationWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMMUNICATIONWINDOW_H
