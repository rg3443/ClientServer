#include "cclient.h"
#include <QApplication>
#include <QKeyEvent>

CClient::CClient(const QString& HostName,int PortId, QWidget *parent) : QWidget(parent),NextBlockSize(0)
{
    pClientSocket = new QTcpSocket(this);
    pClientSocket->connectToHost(HostName,PortId);

    connect( pClientSocket,SIGNAL(connected()),this,SLOT(slotConnected()) );
    connect( pClientSocket,SIGNAL(readyRead()),this,SLOT(slotReadyRead()) );
    connect( pClientSocket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(slotError(QAbstractSocket::SocketError)) );

    pTextInfo = new QTextEdit;
    pTextInput = new QLineEdit;

    connect( pTextInput,SIGNAL(returnPressed()),this,SLOT(slotSendToServer()) );
    pTextInfo->setReadOnly(true);


    //layout
    QVBoxLayout * pLayout = new QVBoxLayout;
    pLayout->addWidget(new QLabel("<H1>Client</H1>"));
    pLayout->addWidget(pTextInfo);
    pLayout->addWidget(pTextInput);
    setLayout(pLayout);
    if(wasClicked) qApp->quit();
}

void CClient::keyPressEvent(QKeyEvent *event)
{
    if(event->type() == QEvent::KeyPress)
    {
        switch (event->key()) {
        case Qt::Key_Q:
            pTextInput->insert(QString("q"));
            slotSendToServer();
        break;
        case Qt::Key_W:
            pTextInput->insert(QString("w"));
            slotSendToServer();
        break;
        case Qt::Key_E:
            pTextInput->insert(QString("e"));
            slotSendToServer();
        break;
        case Qt::Key_R:
            pTextInput->insert(QString("r"));
            slotSendToServer();
        break;
        case Qt::Key_T:
            pTextInput->insert(QString("t"));
            slotSendToServer();
        break;
        case Qt::Key_Y:
            pTextInput->insert(QString("y"));
            slotSendToServer();
        break;
        case Qt::Key_U:
            pTextInput->insert(QString("u"));
            slotSendToServer();
        break;
        case Qt::Key_I:
            pTextInput->insert(QString("i"));
            slotSendToServer();
        break;
        case Qt::Key_O:
            pTextInput->insert(QString("o"));
            slotSendToServer();
        break;
        case Qt::Key_P:
            pTextInput->insert(QString("p"));
            slotSendToServer();
        break;
        case Qt::Key_A:
            pTextInput->insert(QString("a"));
            slotSendToServer();
        break;
        case Qt::Key_S:
            pTextInput->insert(QString("s"));
            slotSendToServer();
        break;
        case Qt::Key_D:
            pTextInput->insert(QString("d"));
            slotSendToServer();
        break;
        case Qt::Key_F:
            pTextInput->insert(QString("f"));
            slotSendToServer();
        break;
        case Qt::Key_G:
            pTextInput->insert(QString("g"));
            slotSendToServer();
        break;
        case Qt::Key_H:
            pTextInput->insert(QString("h"));
            slotSendToServer();
        break;
        case Qt::Key_J:
            pTextInput->insert(QString("j"));
            slotSendToServer();
        break;
        case Qt::Key_K:
            pTextInput->insert(QString("k"));
            slotSendToServer();
        break;
        case Qt::Key_L:
            pTextInput->insert(QString("l"));
            slotSendToServer();
        break;
        case Qt::Key_Z:
            pTextInput->insert(QString("z"));
            slotSendToServer();
        break;
        case Qt::Key_X:
            pTextInput->insert(QString("x"));
            slotSendToServer();
        break;
        case Qt::Key_C:
            pTextInput->insert(QString("c"));
            slotSendToServer();
        break;
        case Qt::Key_V:
            pTextInput->insert(QString("v"));
            slotSendToServer();
        break;
        case Qt::Key_B:
            pTextInput->insert(QString("b"));
            slotSendToServer();
        break;
        case Qt::Key_N:
            pTextInput->insert(QString("n"));
            slotSendToServer();
        break;
        case Qt::Key_M:
            pTextInput->insert(QString("m"));
            slotSendToServer();
        break;
        case Qt::Key_Backspace:
            pTextInput->backspace();
            slotSendToServer();
        break;
        case Qt::Key_Space: /*это не пробел...*/
            pTextInput->insert(".");
            slotSendToServer();
        break;
        }
        wasClicked = true;
    } else {
        //return false;
    }
    if(event->key() == Qt::Key_Escape)
    {
        qApp->quit();
    }
    wasClicked = false;
}


void CClient::slotReadyRead()
{
    QDataStream in(pClientSocket); // создаем поток и указываем с какого сокета читать
    in.setVersion(QDataStream::Qt_4_9);
    for( ; ; )
    {
        int bytesAvaible = pClientSocket->bytesAvailable();
        int sizeofblock = sizeof(quint16);
        if(!NextBlockSize) {
            if(bytesAvaible < sizeofblock) {
                break;
            }
            in >> NextBlockSize;
        }
        if(pClientSocket->bytesAvailable() < NextBlockSize) {
            break;
        }
        QString str;
        in >> str;

        NextBlockSize = 0;
    }
}

void CClient::slotError(QAbstractSocket::SocketError err)
{
    QString error = "ERROR!";
    pTextInfo->append(error);
}

void CClient::slotSendToServer()
{
    QByteArray arrBlock; //создаем блок байтов для отпрaвки
    QDataStream out(&arrBlock,QIODevice::WriteOnly); // создаем поток и подвязываем к нему блок байтов для записи
    out.setVersion(QDataStream::Qt_4_9);
    out << quint16(0) /*<< QTime::currentTime()*/ << pTextInput->text(); // записываем информацию в блок

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));



    pClientSocket->write(arrBlock);
}

void CClient::slotConnected()
{
    pTextInfo->append("Соединение установлено");
}

