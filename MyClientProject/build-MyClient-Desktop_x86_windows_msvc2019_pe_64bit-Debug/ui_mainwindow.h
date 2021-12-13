/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.0.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTextEdit *recvFieldTE;
    QPushButton *connectButton;
    QPushButton *sendButton;
    QTextEdit *sendFieldTE;
    QPushButton *logInButton;
    QPushButton *sendFileButton;
    QListWidget *friendListLW;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(809, 604);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        recvFieldTE = new QTextEdit(centralwidget);
        recvFieldTE->setObjectName(QString::fromUtf8("recvFieldTE"));
        recvFieldTE->setGeometry(QRect(40, 10, 571, 451));
        recvFieldTE->setStyleSheet(QString::fromUtf8(""));
        connectButton = new QPushButton(centralwidget);
        connectButton->setObjectName(QString::fromUtf8("connectButton"));
        connectButton->setGeometry(QRect(640, 20, 141, 41));
        connectButton->setStyleSheet(QString::fromUtf8("color: rgb(199, 110, 255);"));
        sendButton = new QPushButton(centralwidget);
        sendButton->setObjectName(QString::fromUtf8("sendButton"));
        sendButton->setGeometry(QRect(480, 490, 111, 41));
        sendButton->setStyleSheet(QString::fromUtf8("color: rgb(118, 94, 255);"));
        sendFieldTE = new QTextEdit(centralwidget);
        sendFieldTE->setObjectName(QString::fromUtf8("sendFieldTE"));
        sendFieldTE->setGeometry(QRect(50, 480, 421, 61));
        logInButton = new QPushButton(centralwidget);
        logInButton->setObjectName(QString::fromUtf8("logInButton"));
        logInButton->setGeometry(QRect(640, 70, 141, 41));
        sendFileButton = new QPushButton(centralwidget);
        sendFileButton->setObjectName(QString::fromUtf8("sendFileButton"));
        sendFileButton->setGeometry(QRect(640, 120, 141, 41));
        friendListLW = new QListWidget(centralwidget);
        friendListLW->setObjectName(QString::fromUtf8("friendListLW"));
        friendListLW->setGeometry(QRect(630, 180, 161, 281));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 809, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        connectButton->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        sendButton->setText(QCoreApplication::translate("MainWindow", "Send", nullptr));
        logInButton->setText(QCoreApplication::translate("MainWindow", "Log in", nullptr));
        sendFileButton->setText(QCoreApplication::translate("MainWindow", "Send file", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
