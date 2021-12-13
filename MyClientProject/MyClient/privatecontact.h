#ifndef PRIVATECONTACT_H
#define PRIVATECONTACT_H

#include <QObject>
#include <QWidget>

#include "contact.h"

class PrivateContact : public Contact
{
public:
    PrivateContact(QString userId, QString userName);
};

#endif // PRIVATECONTACT_H
