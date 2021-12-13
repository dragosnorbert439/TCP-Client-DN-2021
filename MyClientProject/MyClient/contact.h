#ifndef CONTACT_H
#define CONTACT_H

#include <QObject>
#include <QWidget>
#include <QListWidgetItem>
#include <QMouseEvent>

class Contact : public QListWidgetItem
{
public:
    Contact();

    int contactType;
    QString id;
    QString name;
    QString sentMessages;

    enum { GROUP_MSG, PRIVATE_MSG };
};

#endif // CONTACT_H
