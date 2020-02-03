#include "cserver.h"

class CServerData : public QSharedData
{
public:

};

CServer::CServer(int PortId,QWidget *parent) : QWidget(parent),NextBlockSize(0)
{
    pServer = new QTcpServer(this);
    if(!pServer->listen(QHostAddress::Any,PortId)) {
        QMessageBox::critical(0,"Server Error","Unable to start Server:" + pServer->errorString());
        pServer->close();
        return;
    }
    connect(pServer,SIGNAL(newConnection()),this,SLOT(slotNewConnection()));
    pText = new QTextEdit;
    pText->setReadOnly(true);
    QVBoxLayout* pLayout = new QVBoxLayout;
    pLayout->addWidget(new QLabel("<H1>Server</H1>"));
    pLayout->addWidget(pText);
    setLayout(pLayout);
}


void CServer::slotNewConnection()
{
    QTcpSocket * pClientSocket = pServer->nextPendingConnection();
    connect(pClientSocket,SIGNAL(disconected()),this,SLOT(deleteLater()));
    connect(pClientSocket,SIGNAL(readyRead()),this,SLOT(slotReadClient()));
    SendToClient(pClientSocket,"You are at server now!");
}

void CServer::slotReadClient()
{
    QTcpSocket * pClientSocket = (QTcpSocket*)sender();
    QDataStream in(pClientSocket);
    in.setVersion(QDataStream::Qt_4_9);
    for( ; ; )
    {
        if(!NextBlockSize) {
            if(pClientSocket->bytesAvailable() < sizeof (quint16)) {
                break;
            }
            in >> NextBlockSize;
        }
        if(pClientSocket->bytesAvailable() < NextBlockSize) {
            break;
        }
        QTime time;
        QString str;
        in /*>> time*/ >> str;
        QString Message = /*time.toString() + " " + "Client has sended - " +*/ str;

        pText->setText(str);
        //pText->append(Message);

        NextBlockSize = 0; // следующий блок будет неизвестен

        //SendToClient(pClientSocket,"SERVER RESPONSE: \"" + str + "\"");
    }
}

void CServer::SendToClient(QTcpSocket *pSocket, const QString &line)
{
    QByteArray arrBlock;
    QDataStream out(&arrBlock,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_9);
    out << quint16(0)/* << QTime::currentTime()*/ << line;

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof (quint16));

    pSocket->write(arrBlock);
}
