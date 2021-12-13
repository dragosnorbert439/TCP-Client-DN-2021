/********************************************************************************
** Form generated from reading UI file 'logindialog.ui'
**
** Created by: Qt User Interface Compiler version 6.0.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_LoginDialog
{
public:
    QPushButton *okButton;
    QPushButton *cancelButton;
    QLineEdit *userNameFieldLE;
    QLabel *userNameLabel;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName(QString::fromUtf8("LoginDialog"));
        LoginDialog->resize(400, 300);
        okButton = new QPushButton(LoginDialog);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        okButton->setGeometry(QRect(190, 250, 91, 31));
        cancelButton = new QPushButton(LoginDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setGeometry(QRect(290, 250, 91, 31));
        userNameFieldLE = new QLineEdit(LoginDialog);
        userNameFieldLE->setObjectName(QString::fromUtf8("userNameFieldLE"));
        userNameFieldLE->setGeometry(QRect(40, 60, 321, 41));
        userNameLabel = new QLabel(LoginDialog);
        userNameLabel->setObjectName(QString::fromUtf8("userNameLabel"));
        userNameLabel->setGeometry(QRect(50, 20, 191, 31));

        retranslateUi(LoginDialog);
        QObject::connect(cancelButton, &QPushButton::clicked, LoginDialog, qOverload<>(&QDialog::close));

        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QCoreApplication::translate("LoginDialog", "Dialog", nullptr));
        okButton->setText(QCoreApplication::translate("LoginDialog", "Ok", nullptr));
        cancelButton->setText(QCoreApplication::translate("LoginDialog", "Cancel", nullptr));
        userNameLabel->setText(QCoreApplication::translate("LoginDialog", "Username:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
