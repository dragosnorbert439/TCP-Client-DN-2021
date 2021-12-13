#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QFile>
#include <QException>

#include "utils.h"

namespace Ui { class LoginDialog; }

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QString& userId,
                         QString& userName,
                         QWidget *parent = nullptr);
    ~LoginDialog();

private:
    Ui::LoginDialog *ui;
    void setUpStyle();
};

#endif // LOGINDIALOG_H
