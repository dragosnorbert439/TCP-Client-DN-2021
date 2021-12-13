#ifndef MYCLIENTTHREAD_H
#define MYCLIENTTHREAD_H

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <QWidget>
#include <QObject>
#include <QThread>
#include <QDebug>

#include "WinSock2.h"

class MyClientThread : public QThread
{
    Q_OBJECT

    SOCKET mySocket;

    void run();

public:
    MyClientThread(SOCKET mySocket);

signals:
    void newSentMessage(QString string);
};

#endif // MYCLIENTTHREAD_H
