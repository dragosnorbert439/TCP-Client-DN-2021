#ifndef GROUPCONTACT_H
#define GROUPCONTACT_H

#include <QObject>
#include <QWidget>
#include <QVector>

#include "contact.h"

class GroupContact : public Contact
{
public:
    GroupContact(QString groupId, QString groupName, QList<QByteArray> userIds);
    QList<QByteArray> userIds;
};

#endif // GROUPCONTACT_H
