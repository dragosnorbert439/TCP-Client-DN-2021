#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QString& userId,
                         QString& userName,
                         QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    setUpStyle();
    connect(ui->okButton, &QPushButton::clicked, [&]()
    {
        // should enter critical section

        qDebug() << "LoginDialog::okButton clicked.";

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

                   if (fileUserName == ui->userNameFieldLE->text())
                   {
                       inputFile.close();
                       userId = fileUserId;
                       userName = fileUserName;
                       qDebug() << "LoginDialog::Found corresponding user.";

                       // leave critical section

                       done(QDialog::Accepted);
                       return;
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
            done(QDialog::Rejected);
        }

        // should leave critical section

        done(QDialog::Rejected);
    });
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::setUpStyle()
{
    QString buttonStyle = "QPushButton { background-color: #638fd6; color: #000000; }";
    QString lineEditStyle = "QLineEdit { background-color: #ecbaff; color: #000000; padding: 8px; font-size: 16px; }";
    QString centralWidgetStyle = "QWidget { background-color: #7d3bb8 }";
    QString labelStyle = "QLabel { font-size: 18px; }";

    this->setStyleSheet(centralWidgetStyle);
    ui->okButton->setStyleSheet(buttonStyle);
    ui->cancelButton->setStyleSheet(buttonStyle);
    ui->userNameFieldLE->setStyleSheet(lineEditStyle);
    ui->userNameLabel->setStyleSheet(labelStyle);
}




















