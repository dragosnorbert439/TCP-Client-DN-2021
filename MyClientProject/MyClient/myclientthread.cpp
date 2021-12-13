#include "myclientthread.h"

MyClientThread::MyClientThread(SOCKET mySocket)
{
    this->mySocket = mySocket;
}

void MyClientThread::run()
{
    qDebug() << "MyClientThread::Recevide thread started";

    // [EN] Variables
    int iResult = 0;
    int bufLen = 1024;
    int bytes = 0;
    unsigned short messageSize = 0;
    unsigned short messageOrFile = 0;
    unsigned short groupOrPrivate = 0;
    std::string fromWhoId;
    std::string toWhomId;
    char recvBuf[1024] = " ";
    char helpBuf[1024] = " ";
    char sendBuf[1024] = "";
    char holder;
    bool informationIsRead = false;

    while (true)
    {
        // [EN] Receive
        iResult = recv(mySocket, recvBuf, bufLen, 0);
        if (iResult <= 0) break;

        if (bytes < 10)
        {
            for (int i = 0; i < iResult - 1; ++i)
            {
                holder = recvBuf[i];

                // [EN] message length
                if (i == 0) messageSize += atoi(&holder) * 1000;
                if (i == 1) messageSize += atoi(&holder) * 100;
                if (i == 2) messageSize += atoi(&holder) * 10;
                if (i == 3) messageSize += atoi(&holder);

                // [EN] message or file
                //if (i == 4) messageOrFile = atoi(&holder); // used for debugging

                // [EN] group or private
                //if (i == 5) groupOrPrivate = atoi(&holder); // used for debugging

                // [EN] from who id
                if (i == 6) fromWhoId.push_back(holder);
                if (i == 7) fromWhoId.push_back(holder);

                // [EN] to whom id
                if (i == 8) toWhomId.push_back(holder);
                if (i == 9) toWhomId.push_back(holder);
            }
        }

        strcat_s(sendBuf, recvBuf);
        bytes += iResult - 1;

        if (bytes > 9 && !informationIsRead)
        {
            memcpy(helpBuf, recvBuf + 10, strlen(recvBuf) - 9);
            informationIsRead = true;
        }
        else if (bytes > 9 && informationIsRead)
        {
            strcat_s(helpBuf, recvBuf);
        }

        qDebug() << messageSize << bytes;

        if (messageSize + 10 == bytes)
        {
            emit newSentMessage(sendBuf);

            // [EN] clearing all the used variables for next message
            strcpy_s(sendBuf, "");
            messageSize = 0;
            informationIsRead = false;
            fromWhoId.clear();
            toWhomId.clear();
            bytes = 0;
        }

        strcpy_s(helpBuf, "");
    }

    qDebug() << "MyClientThread::Receive thread stopped";
}
