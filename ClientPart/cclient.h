#ifndef CCLIENT_H
#define CCLIENT_H

#include <QWidget>
#include <QWidget>
#include <QTcpServer>
#include <QTextEdit>
#include <QTcpSocket>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QTime>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>


class CClient : public QWidget {
Q_OBJECT
public:
    explicit CClient(const QString& HostName,int PortId, QWidget *parent = nullptr);
private:
    QTcpSocket * pClientSocket;
    QTextEdit * pTextInfo; //ОТОБРАЖЕНИЕ ИНФОРМАЦИИ
    QLineEdit * pTextInput; //ВВОД ИНФОРМАЦИИ
    quint16 NextBlockSize;

private slots:
    void slotReadyRead();
    void slotError(QAbstractSocket::SocketError);
    void slotSendToServer();
    void slotConnected();

private:
    bool wasClicked;
protected:
    void keyPressEvent(QKeyEvent * event);
};
#endif // CCLIENT_H
