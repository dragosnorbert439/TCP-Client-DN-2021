#include "groupcontact.h"

GroupContact::GroupContact(QString groupId, QString groupName, QList<QByteArray> userIds)
{
    this->contactType = GROUP_MSG;
    this->userIds = userIds;
    this->id = groupId;
    this->name = groupName;
    this->setText(groupName);
}
