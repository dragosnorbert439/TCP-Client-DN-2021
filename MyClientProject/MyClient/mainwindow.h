#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define _CRT_SECURE_NO_WARNINGS

#include <QMainWindow>
#include <QDebug>
#include <QScrollBar>
#include <QKeyEvent>
#include <QKeyCombination>

#include <string.h>
#include <stdlib.h>

#include "myclientthread.h"
#include "logindialog.h"
#include "contact.h"
#include "privatecontact.h"
#include "groupcontact.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
// [EN] constructor & destructor
    MainWindow(QWidget *parent = nullptr);    
    ~MainWindow();

private:
// [EN] private members
    Ui::MainWindow *ui;
    bool connected;
    MyClientThread* receiveThread;
    SOCKET clientSocket;
    sockaddr_in serverAddress;
    QScrollBar* sb;

    QString userId;
    QString userName;
    QString sendToId;
    QString sendToName;
    unsigned short dataType; // msg or file
    unsigned short sendType; // group or private

    enum { GROUP_MSG, PRIVATE_MSG };
    enum { MSG, FILE };

// [EN] private functinos
    void setUp();
    void setUpConnects();
    void setUpStyle();

    void loadDLL();
    void initSocket();
    void initSockaddr();

    void connectToServer();
    void disconnectFromServer();
    void receiveDatagrams();

    void sendMessage();
    void sendTestFile();

    void logIn();
    void setUpContacts();
    void setUpGroups();

private slots:
    void messageReceived(QString string);

};
#endif // MAINWINDOW_H
