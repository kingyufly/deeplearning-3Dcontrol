#include <QtCore>
#include <QtWidgets>
#include <QVector>

#include <stdio.h>

#include "qextserialport.h"
#include "qextserialenumerator.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

QVector<int> content;
QVector<QString> content_str;

int n = 0, n_tmp = 0;

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    foreach (QextPortInfo info, QextSerialEnumerator::getPorts())
        ui->portBox->addItem(info.portName);
    //make sure user can input their own port name!
    ui->portBox->setEditable(true);

    ui->baudRateBox->addItem("19200", BAUD19200);
    ui->baudRateBox->addItem("38400", BAUD38400);
    ui->baudRateBox->addItem("57600", BAUD57600);
    ui->baudRateBox->addItem("115200", BAUD115200);
    ui->baudRateBox->setCurrentIndex(3);

    ui->parityBox->addItem("NONE", PAR_NONE);
    ui->parityBox->addItem("ODD", PAR_ODD);
    ui->parityBox->addItem("EVEN", PAR_EVEN);
    ui->parityBox->setCurrentIndex(0);

    ui->dataBitsBox->addItem("6", DATA_6);
    ui->dataBitsBox->addItem("7", DATA_7);
    ui->dataBitsBox->addItem("8", DATA_8);
    ui->dataBitsBox->setCurrentIndex(2);

    ui->stopBitsBox->addItem("1", STOP_1);
    ui->stopBitsBox->addItem("2", STOP_2);
    ui->stopBitsBox->setCurrentIndex(0);

    ui->led->turnOff();

    PortSettings settings = {BAUD115200, DATA_8, PAR_NONE, STOP_1, FLOW_OFF, 10};
    port = new QextSerialPort(ui->portBox->currentText(), settings, QextSerialPort::EventDriven);

    enumerator = new QextSerialEnumerator(this);
    enumerator->setUpNotifications();

    connect(ui->baudRateBox, SIGNAL(currentIndexChanged(int)), SLOT(onBaudRateChanged(int)));
    connect(ui->parityBox, SIGNAL(currentIndexChanged(int)), SLOT(onParityChanged(int)));
    connect(ui->dataBitsBox, SIGNAL(currentIndexChanged(int)), SLOT(onDataBitsChanged(int)));
    connect(ui->stopBitsBox, SIGNAL(currentIndexChanged(int)), SLOT(onStopBitsChanged(int)));
    connect(ui->portBox, SIGNAL(editTextChanged(QString)), SLOT(onPortNameChanged(QString)));
    connect(ui->openCloseButton, SIGNAL(clicked()), SLOT(onOpenCloseButtonClicked()));

    port->setQueryMode((QextSerialPort::QueryMode)1);

    connect(port, SIGNAL(readyRead()), SLOT(onReadyRead()));

    connect(enumerator, SIGNAL(deviceDiscovered(QextPortInfo)), SLOT(onPortAddedOrRemoved()));
    connect(enumerator, SIGNAL(deviceRemoved(QextPortInfo)), SLOT(onPortAddedOrRemoved()));

    setWindowTitle(tr("XYZ Robot Control"));

    ui->startStopButton->setEnabled(false);
    ui->pauseResumeButton->setEnabled(false);
}

Dialog::~Dialog()
{
    delete ui;
    delete port;
}

void Dialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void Dialog::onPortNameChanged(const QString & /*name*/)
{
    if (port->isOpen()) {
        port->close();
        ui->led->turnOff();
    }
}

void Dialog::onBaudRateChanged(int idx)
{
    port->setBaudRate((BaudRateType)ui->baudRateBox->itemData(idx).toInt());
}

void Dialog::onParityChanged(int idx)
{
    port->setParity((ParityType)ui->parityBox->itemData(idx).toInt());
}

void Dialog::onDataBitsChanged(int idx)
{
    port->setDataBits((DataBitsType)ui->dataBitsBox->itemData(idx).toInt());
}

void Dialog::onStopBitsChanged(int idx)
{
    port->setStopBits((StopBitsType)ui->stopBitsBox->itemData(idx).toInt());
}

void Dialog::onOpenCloseButtonClicked()
{
    if (!port->isOpen()) {
        if(port->open(QIODevice::ReadWrite))
        {
            port->setPortName(ui->portBox->currentText());

            ui->openCloseButton->setText("CLOSE");
            ui->led->turnOn(port->isOpen());

            ui->portBox->setEnabled(false);
            ui->baudRateBox->setEnabled(false);
            ui->dataBitsBox->setEnabled(false);
            ui->stopBitsBox->setEnabled(false);
            ui->parityBox->setEnabled(false);
            if(n == 0)
            {
                ui->startStopButton->setEnabled(false);
            }
            else
            {
                ui->startStopButton->setEnabled(true);
            }
            ui->pauseResumeButton->setEnabled(false);
        }
        else
        {
            ;
        }
    }
    else {
        port->close();
        ui->led->turnOff(!port->isOpen());
        ui->openCloseButton->setText("OPEN");
        ui->portBox->setEnabled(true);
        ui->baudRateBox->setEnabled(true);
        ui->dataBitsBox->setEnabled(true);
        ui->stopBitsBox->setEnabled(true);
        ui->parityBox->setEnabled(true);
        ui->startStopButton->setEnabled(false);
        ui->pauseResumeButton->setEnabled(false);
    }
}

void Dialog::onReadyRead()
{
    if (port->bytesAvailable()) {
        ui->recvEdit->moveCursor(QTextCursor::End);
        QString str = QString::fromLatin1(port->readAll());
        ui->recvEdit->insertPlainText("Rx: " + str + "\r\n");

        if(str.compare("OK\r\n") == 0)
        {
            if(n_tmp <= -1)
            {
                ui->startStopButton->setText("Start");
                ui->startStopButton->setEnabled(false);
                ui->pauseResumeButton->setText("Pause");
                ui->pauseResumeButton->setEnabled(false);
                ui->fileOpenButton->setEnabled(true);
                ui->openCloseButton->setEnabled(true);
                ui->recvEdit->moveCursor(QTextCursor::End);
                ui->recvEdit->insertPlainText("\r\nOVER!!\r\n\r\n");

                QMessageBox message(QMessageBox::Information, "Finished!", "Do you want to start a new operation? (The current log will be erased!)", QMessageBox::Yes | QMessageBox::No, NULL);
                int msgexec = message.exec();

                if(msgexec == QMessageBox::Yes)
                {
                    ui->recvEdit->setText("");
                    ui->dataBrowser->setText("");
                    ui->startStopButton->setEnabled(false);
                }
                else if(msgexec == QMessageBox::No)
                {
                    ;
                }
                else if(msgexec == QMessageBox::Abort)
                {
                    ;
                }
                else if(msgexec == QMessageBox::Escape)
                {
                    ;
                }
                else
                {
                    ;
                }
            }
            else
            {
                send_command(content_str[n_tmp - 2], content_str[n_tmp - 1], content_str[n_tmp]);
                n_tmp -= 3;
            }
        }
        else
        {
            ;
        }
    }
}

void Dialog::onPortAddedOrRemoved()
{
    QString current = ui->portBox->currentText();

    ui->portBox->blockSignals(true);
    ui->portBox->clear();
    foreach (QextPortInfo info, QextSerialEnumerator::getPorts())
        ui->portBox->addItem(info.portName);

    ui->portBox->setCurrentIndex(ui->portBox->findText(current));

    ui->portBox->blockSignals(false);
}

void Dialog::send_command(QString str1, QString str2, QString str3){
    if (port->isOpen()){
        QString str = str1 + ";" + str2 + ";" + str3 + "\r\n";
        port->write(str.toStdString().data(), strlen(str.toStdString().data()));

        ui->recvEdit->moveCursor(QTextCursor::End);
        ui->recvEdit->insertPlainText("Tx: " + str);
    }
}

void Dialog::on_fileOpenButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open Document", QDir::homePath(), "Document files (*.txt)");

    QFile f(filename);
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        ui->dataBrowser->setText("");
        ui->dataBrowser->moveCursor(QTextCursor::End);
        ui->dataBrowser->insertPlainText(QString::fromLatin1("Open Error!"));
    }
    else
    {
        if(port->isOpen())
        {
            ui->startStopButton->setEnabled(true);
        }
        ui->dataBrowser->setText("");
        ui->pauseResumeButton->setEnabled(false);

        n = 0;
        content.clear();

        QTextStream txtInput(&f);
        QString lineStr;

        while(!txtInput.atEnd())
        {
            lineStr = txtInput.readLine();
            n++;
            QStringList result = lineStr.split(";");
            for(int i = 0; i < result.size(); i++)
            {
                content.push_back(result[i].toInt());
            }
        }
//        for(int i = content.size() - 1; i > 0; i--)
//        {
//            if(i <= 2)
//            {
//                break;
//            }
//            else
//            {
//                content[i] = content[i] - content[i - 3];
//            }
//        }
        for(int i = 0; i < content.size(); i += 3)
        {
            ui->dataBrowser->moveCursor(QTextCursor::End);

            QString str;
            for(int j = 0; j < 3; j++){
                if(content[i + j] >= 0)
                {
                    ui->dataBrowser->insertPlainText(str.sprintf("+%04d", content[i + j]));
                    content_str.push_back(str);
                }
                else
                {
                    ui->dataBrowser->insertPlainText(str.sprintf("-%04d", 0 - content[i + j]));
                    content_str.push_back(str);
                }
                switch(j)
                {
                case 2:
                {
                    ui->dataBrowser->insertPlainText("\r\n\r\n");
                    break;
                }
                default:
                {
                    ui->dataBrowser->insertPlainText(";\r\n");
                    break;
                }
                }
            }
        }
    }
    f.close();
}

void Dialog::on_startStopButton_clicked()
{
    if (ui->startStopButton->text().compare("Start") == 0)
    {
        ui->fileOpenButton->setEnabled(false);
        ui->startStopButton->setText("Stop");
        ui->pauseResumeButton->setText("Pause");
        ui->pauseResumeButton->setEnabled(true);
        ui->openCloseButton->setEnabled(false);

        n_tmp = n * 3 - 1;
        if (port->isOpen()){
            QString str = "STARTSTARTSTARTST\r\n";
            port->write(str.toStdString().data(), strlen(str.toStdString().data()));

            ui->recvEdit->moveCursor(QTextCursor::End);
            ui->recvEdit->insertPlainText("Tx: " + str);
        }
    }
    else
    {
        ui->fileOpenButton->setEnabled(true);
        ui->startStopButton->setText("Start");
        ui->pauseResumeButton->setText("Pause");
        ui->pauseResumeButton->setEnabled(false);
        ui->openCloseButton->setEnabled(true);

        if (port->isOpen()){
            QString str = "STOPSTOPSTOPSTOPS\r\n";
            port->write(str.toStdString().data(), strlen(str.toStdString().data()));

            ui->recvEdit->moveCursor(QTextCursor::End);
            ui->recvEdit->insertPlainText("Tx: " + str);
        }
        ui->recvEdit->insertPlainText("\r\nSTOPPED!!\r\n\r\n");
        QMessageBox message(QMessageBox::Information, "Stopped!", "The operation has been interrupted by the user!", QMessageBox::Ok, NULL);
        int msgexec = message.exec();

        if(msgexec == QMessageBox::Ok)
        {
            ;
        }
        else if(msgexec == QMessageBox::Abort)
        {
            ;
        }
        else if(msgexec == QMessageBox::Escape)
        {
            ;
        }
        else
        {
            ;
        }
    }
}

void Dialog::on_pauseResumeButton_clicked()
{
    if (ui->pauseResumeButton->text().compare("Pause") == 0)
    {
        ui->pauseResumeButton->setText("Resume");
        if (port->isOpen()){
            QString str = "PAUSEPAUSEPAUSEPA\r\n";
            port->write(str.toStdString().data(), strlen(str.toStdString().data()));

            ui->recvEdit->moveCursor(QTextCursor::End);
            ui->recvEdit->insertPlainText("Tx: " + str);
        }
    }
    else
    {
        ui->pauseResumeButton->setText("Pause");
        if (port->isOpen()){
            QString str = "RESUMERESUMERESUM\r\n";
            port->write(str.toStdString().data(), strlen(str.toStdString().data()));

            ui->recvEdit->moveCursor(QTextCursor::End);
            ui->recvEdit->insertPlainText("Tx: " + str);
        }
    }
}
