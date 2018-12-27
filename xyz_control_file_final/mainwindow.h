#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
    class Dialog;
}

class QextSerialPort;
class QextSerialEnumerator;

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

protected:
    void changeEvent(QEvent *e);

private Q_SLOTS:
    void onPortNameChanged(const QString &name);
    void onBaudRateChanged(int idx);
    void onParityChanged(int idx);
    void onDataBitsChanged(int idx);
    void onStopBitsChanged(int idx);
    void onOpenCloseButtonClicked();
    void onReadyRead();
    void onPortAddedOrRemoved();

    void send_command(QString str1, QString str2, QString str3);

    void on_fileOpenButton_clicked();

    void on_startStopButton_clicked();

    void on_pauseResumeButton_clicked();

private:
    Ui::Dialog *ui;
    QextSerialPort *port;
    QextSerialEnumerator *enumerator;
};

#endif // DIALOG_H
