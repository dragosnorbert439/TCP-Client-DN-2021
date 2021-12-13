#include "mainwindow.h"
#include "ui_mainwindow.h"

// [EN] constructor
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    loadDLL();
    initSocket();
    initSockaddr();

    setUp();
    setUpConnects();
    setUpStyle();
}

// [EN] destructor
MainWindow::~MainWindow()
{
    WSACleanup();
    receiveThread->terminate();
    delete receiveThread;
    delete ui;
}

// [EN] initializes some variables
void MainWindow::setUp()
{
    connected = false;
    sb = ui->recvFieldTE->verticalScrollBar();
    sb->setValue(sb->maximum());
    receiveThread = new MyClientThread(clientSocket);
    ui->connectButton->setEnabled(false);
    ui->sendButton->setEnabled(false);
    ui->recvFieldTE->setEnabled(false);
}

// [EN] qt feature - sets up connects / signal-slots
void MainWindow::setUpConnects()
{
    connect(ui->connectButton, &QPushButton::clicked, [&]()
    {
        if (connected)
        {
            connected = false;
            ui->connectButton->setText("Connect");

            disconnectFromServer();
        }
        else
        {
            connected = true;
            ui->connectButton->setText("Disconnect");

            connectToServer();
        }
    });
    connect(ui->sendButton, &QPushButton::clicked, this, &MainWindow::sendMessage);
    connect(receiveThread, &MyClientThread::newSentMessage, this, &MainWindow::messageReceived);
    connect(ui->sendFieldTE, &QTextEdit::textChanged, [&]()
    {
       /// TODO: make ENTER send message instantly
    });
    connect(ui->logInButton, &QPushButton::clicked, this, &MainWindow::logIn);
    connect(ui->friendListLW, &QListWidget::itemClicked, [&]()
    {
        dataType = MSG;
        sendType = static_cast<Contact*>(ui->friendListLW->currentItem())->contactType;

        sendToId = static_cast<Contact*>(ui->friendListLW->currentItem())->id;
        sendToName = static_cast<Contact*>(ui->friendListLW->currentItem())->name;

        ui->recvFieldTE->setText(static_cast<Contact*>(ui->friendListLW->currentItem())->sentMessages);
        ui->sendButton->setEnabled(true);

    });
    connect(ui->sendFileButton, &QPushButton::clicked, this, &MainWindow::sendTestFile);
}

// [EN] sets up style fonts colors etc
void MainWindow::setUpStyle()
{
    QString buttonStyle = "QPushButton { background-color: #638fd6; color: #131829; font-size: 24px; font-family: serif; }";
    QString textEditStyle = "QTextEdit { background-color: #ecbaff; color: #000000; font-size: 18px; }";
    QString centralWidgetStyle = "QWidget { background-color: #7d3bb8 }";
    QString listWidgetStyle = "QListWidget { background-color: #94b0f7; font-size: 16px;}";

    ui->centralwidget->setStyleSheet(centralWidgetStyle);
    ui->recvFieldTE->setStyleSheet(textEditStyle);
    ui->sendFieldTE->setStyleSheet(textEditStyle);
    ui->connectButton->setStyleSheet(buttonStyle);
    ui->sendButton->setStyleSheet(buttonStyle);
    ui->logInButton->setStyleSheet(buttonStyle);
    ui->sendFileButton->setStyleSheet(buttonStyle);
    ui->friendListLW->setStyleSheet(listWidgetStyle);
}

// [EN] WSAStartup
void MainWindow::loadDLL()
{
    qDebug() << "Loaded DLL";
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != NO_ERROR) qDebug() << "Hiba a WSAStartup()–nal";
}

// [EN] SOCKET
void MainWindow::initSocket()
{
    qDebug() << "Initialized SOCKET";
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET) WSACleanup();
}

// [EN] sockaddr
void MainWindow::initSockaddr()
{
    qDebug() << "Initialized sockaddr";
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddress.sin_port = htons(13000);
}

// [EN] CONNECT
void MainWindow::connectToServer()
{
    qDebug() << "Connect";
    if (::connect(clientSocket, (SOCKADDR*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR)
    {
        qDebug() << "Hiba a kapcsolódásnál a következő hibakóddal:" << WSAGetLastError();
        WSACleanup();
    }
    else
    {
        ui->connectButton->setEnabled(true);

        // [EN] first, we tell the server who we are
        char sendBuf[3];
        strcpy_s(sendBuf, userId.toLatin1());
        if (::send(clientSocket, sendBuf, strlen(sendBuf) + 1, 0) == SOCKET_ERROR)
        {
            qDebug() << "Hiba a küldesnel a kovetkezo hibakoddal: " <<  WSAGetLastError();
            closesocket(clientSocket);
            WSACleanup(); // [HU] WSACleanup befejezi a Windows Sockets működését minden szálban
        }

        // [EN] recv
        receiveDatagrams();
    }
}

// [EN] breaks the connection
void MainWindow::disconnectFromServer()
{
    qDebug() << "Disconnect";
    shutdown(clientSocket, SD_SEND);
}

// [EN] starts up the receiver thread
void MainWindow::receiveDatagrams()
{
    qDebug() << "Receive thread started";
    receiveThread->start();
}

// [EN] sends the message from the input field
void MainWindow::sendMessage()
{
    if (!connected) return;

    qDebug() << "Message sent";

    char sendBuf[1024] = " ";
    unsigned short messageSize = strlen(ui->sendFieldTE->toPlainText().toStdString().c_str()) + userName.size() + 2;

    // [EN] length of the message
    _itoa(messageSize / 1000, &sendBuf[0], 10);
    _itoa((messageSize / 100) % 10, &sendBuf[1], 10);
    _itoa((messageSize / 10) % 10, &sendBuf[2], 10);
    _itoa(messageSize % 10, &sendBuf[3], 10);

    // [EN] message or file 0/1
    _itoa(dataType, &sendBuf[4], 10);

    // [EN] group or private 0/1
    _itoa(sendType, &sendBuf[5], 10);

    // [EN] from who id
    sendBuf[6] = userId[0].toLatin1();
    sendBuf[7] = userId[1].toLatin1();

    // [EN] to whom id
    sendBuf[8] = sendToId[0].toLatin1();
    sendBuf[9] = sendToId[1].toLatin1();

    strcat_s(sendBuf, userName.toLatin1());
    strcat_s(sendBuf, ": ");
    strcat_s(sendBuf, ui->sendFieldTE->toPlainText().toStdString().c_str());

    if (::send(clientSocket, sendBuf, strlen(sendBuf) + 1, 0) == SOCKET_ERROR)
    {
        qDebug() << "Hiba a küldesnel a kovetkezo hibakoddal: " <<  WSAGetLastError();
        closesocket(clientSocket);
        WSACleanup(); // [HU] WSACleanup befejezi a Windows Sockets működését minden szálban
    }
    ui->sendFieldTE->clear();
}

// [EN] demo file sending
void MainWindow::sendTestFile()
{
    if (!connected) return;

    dataType = FILE;

    qDebug() << "File sent";

    QFile file(FILE_DEMO);
    if (!file.open(QIODevice::ReadOnly)) return;
    QByteArray blob = file.readAll();
    file.close();

    if (blob.size() > 9999)
    {
        qDebug() << "File size too large!";
        return;
    }

    char sendBuf[1024] = " ";
    unsigned short messageSize = blob.size();
    qDebug() << "File size: " << messageSize;

    // [EN] length of the message
    _itoa(messageSize / 1000, &sendBuf[0], 10);
    _itoa((messageSize / 100) % 10, &sendBuf[1], 10);
    _itoa((messageSize / 10) % 10, &sendBuf[2], 10);
    _itoa(messageSize % 10, &sendBuf[3], 10);

    // [EN] message or file 0/1
    _itoa(dataType, &sendBuf[4], 10);

    // [EN] group or private 0/1
    _itoa(sendType, &sendBuf[5], 10);

    // [EN] from who id
    sendBuf[6] = userId[0].toLatin1();
    sendBuf[7] = userId[1].toLatin1();

    // [EN] to whom id
    sendBuf[8] = sendToId[0].toLatin1();
    sendBuf[9] = sendToId[1].toLatin1();

    strcat_s(sendBuf, blob);

    qDebug() << blob;

    if (::send(clientSocket, sendBuf, strlen(sendBuf) + 1, 0) == SOCKET_ERROR)
    {
        qDebug() << "Hiba a küldesnel a kovetkezo hibakoddal: " <<  WSAGetLastError();
        closesocket(clientSocket);
        WSACleanup(); // [HU] WSACleanup befejezi a Windows Sockets működését minden szálban
    }
}

// [EN] log in feature - pops up login dialog
void MainWindow::logIn()
{
    LoginDialog loginDialog(userId, userName, this);
    loginDialog.setModal(true);
    if (loginDialog.exec() == QDialog::Accepted)
    {
        qDebug() << "Login success.";
        ui->connectButton->setEnabled(true);
        setUpContacts();
        setUpGroups();
    }
    else
    {
        qDebug() << "Login failed.";
    }
}

// [EN] initializes the friends to add to the friend list
void MainWindow::setUpContacts()
{
    QFile inputFile(FILE_NAME);
    QString fileUserName;
    QString fileUserId;

    if (inputFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
       while (!inputFile.atEnd())
       {
           try
           {
               QByteArray line = inputFile.readLine().trimmed();
               fileUserName = line.split(',')[1];
               fileUserId = line.split(',')[0];

               if (fileUserName == userName && fileUserId == userId) continue;

               Contact *newContact = new PrivateContact(fileUserId, fileUserName);
               ui->friendListLW->addItem(newContact);
           }
           catch (QException e)
           {
                qDebug() << "LoginDialog::LoginDialog::Could not read the line.";
           }
       }
       inputFile.close();
    }
    else
    {
        qDebug() << "Could not open file!";
    }
}

// [EN] initializes the groups to add to the friendlist
void MainWindow::setUpGroups()
{
    QFile inputFile(FILE_NAME_GROUPS);
    QString fileGroupName;
    QString fileGroupId;

    if (inputFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
       while (!inputFile.atEnd())
       {
           try
           {
               QByteArray line = inputFile.readLine().trimmed();
               QList<QByteArray> elements = line.split(',');
               bool isInGroup = false;

               fileGroupId = elements[0];
               fileGroupName = elements[1];

               for (int i = 2; i < elements.size(); ++i)
               {
                   if (elements[i] == userId) isInGroup = true;
               }

               if (isInGroup)
               {
                   elements.remove(0, 2);
                   Contact *newContact = new GroupContact(fileGroupId, fileGroupName, elements);
                   ui->friendListLW->addItem(newContact);
                   ui->friendListLW->setCurrentItem(newContact);
               }
           }
           catch (QException e)
           {
                qDebug() << "LoginDialog::LoginDialog::Could not read the line.";
           }
       }
       inputFile.close();
    }
    else
    {
        qDebug() << "Could not open file!";
    }
}

// [EN] Updates the received messages and the TextEdit
void MainWindow::messageReceived(QString string)
{
    qDebug() << "Message received:" << string;

    char holder;
    holder = string.at(4).toLatin1();
    unsigned short messageOrFile = atoi(&holder);
    holder = string.at(5).toLatin1();
    unsigned short groupOrPrivate = atoi(&holder);
    QString fromWhoId; fromWhoId.append(string.at(6)).append(string.at(7));
    QString toWhomId; toWhomId.append(string.at(8)).append(string.at(9));

    string.remove(0, 10);
    //qDebug() << messageOrFile << groupOrPrivate << toWhomId << string;

    if (messageOrFile == MSG && groupOrPrivate == PRIVATE_MSG)
    {
        for (int i = 0; i < ui->friendListLW->count(); ++i)
        {
            if (static_cast<Contact*>(ui->friendListLW->item(i))->id == toWhomId &&
                    static_cast<Contact*>(ui->friendListLW->item(i))->contactType == PRIVATE_MSG)
            {
                static_cast<Contact*>(ui->friendListLW->item(i))->sentMessages.append(string).append("\n");
            }

            if (static_cast<Contact*>(ui->friendListLW->item(i))->id == fromWhoId &&
                    static_cast<Contact*>(ui->friendListLW->item(i))->contactType == PRIVATE_MSG)
            {
                static_cast<Contact*>(ui->friendListLW->item(i))->sentMessages.append(string).append("\n");
            }
        }
    }
    else if (messageOrFile == MSG && groupOrPrivate == GROUP_MSG)
    {
        for (int i = 0; i < ui->friendListLW->count(); ++i)
        {
            if (static_cast<Contact*>(ui->friendListLW->item(i))->id == toWhomId &&
                    static_cast<Contact*>(ui->friendListLW->item(i))->contactType == GROUP_MSG)
            {
                static_cast<Contact*>(ui->friendListLW->item(i))->sentMessages.append(string).append("\n");
            }
        }
    }
    else if (messageOrFile == FILE && groupOrPrivate == PRIVATE_MSG)
    {
        QFile file("File_to_" + userName);
        if (!file.open(QIODevice::WriteOnly))
        {
            qDebug() << "Could not open file";
            return;
        }

        file.write(string.toUtf8());

        file.close();
    }

    ui->recvFieldTE->setText(static_cast<Contact*>(ui->friendListLW->currentItem())->sentMessages);
}



















