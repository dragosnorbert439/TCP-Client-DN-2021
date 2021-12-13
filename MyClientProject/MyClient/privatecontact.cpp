#include "privatecontact.h"

PrivateContact::PrivateContact(QString userId, QString userName)
{
    this->contactType = PRIVATE_MSG;
    this->id = userId;
    this->name = userName;
    this->setText(userName);
}
