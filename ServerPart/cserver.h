#ifndef CSERVER_H
#define CSERVER_H

#include <QSharedDataPointer>
#include <QWidget>
#include <QTcpServer>
#include <QTextEdit>
#include <QTcpSocket>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QTime>
#include <QLabel>

//class QTcpServer;
//class QTextEdit;
//class QTcpSocket;

class CServer : public QWidget {
Q_OBJECT
private:
    QTcpServer * pServer;
    QTextEdit * pText;
    quint16 NextBlockSize;

public:
    explicit CServer(int PortId,QWidget *parent = nullptr);

private:
    void SendToClient(QTcpSocket * pSocket,const QString& line);
public slots:
    virtual void slotNewConnection();
            void slotReadClient();
signals:

};

#endif // CSERVER_H
