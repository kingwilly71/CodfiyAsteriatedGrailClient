﻿#include "LogArea.h"
#include "DataInterface.h"
LogArea::LogArea(QWidget *parent) :
    QTextEdit(parent)
{
    setReadOnly(true);
    setStyleSheet("background-color:transparent");
    setFixedSize(259,360);
}
void LogArea::append(QString text)
{
    text.replace("[","<font color=\'yellow\'>[");
    text.replace("]","]</font>");
    QTextEdit::append(QString("<p style=\"margin:3px p2x; line-height:120%;\"><font color=\'white\'>%1</font></p>").arg(text));
}
ChatArea::ChatArea(QWidget *parent):
    QTextEdit(parent)
{
    setReadOnly(true);
    setStyleSheet("background-color:transparent");
    setFixedSize(259,246);
}
void ChatArea::append(int id,QString text)
{
    QString name=dataInterface->getPlayerList().at(id)->getRoleName();
    if(name==NULL)
        name=dataInterface->getPlayerList().at(id)->getNickname();
    if(name==NULL)
        name="玩家"+QString::number(id);
    QString msg="<p style=\"margin:3px p2x; line-height:120%;\"><font color=\'yellow\'>"+name+"</font>";
    QTextEdit::append(msg+QString("<font color=\'white\'>:%1</font></p>").arg(text));
}
ChatLine::ChatLine(QWidget *parent):
    QLineEdit(parent)
{
    setStyleSheet("color: white;"
                  "background-color:transparent");
    setFixedSize(259,25);
    connect(this,SIGNAL(returnPressed()),this,SLOT(onReturnPressed()));
    connect(this,SIGNAL(toChat(quint16, google::protobuf::Message*)),logic->getClient(),SLOT(sendMessage(quint16, google::protobuf::Message*)));
    connect(this,SIGNAL(textChanged(QString)),this,SLOT(onTextChanged(QString)));
}
void ChatLine::onReturnPressed()
{    
    if(!text().isEmpty())
    {
        network::Gossip* gossip = new network::Gossip();
        gossip->set_type(network::GOSSIP_TALK);
        QByteArray arr = text().toLatin1();
        gossip->set_txt(arr.data(), arr.length());
        emit toChat(network::MSG_GOSSIP, gossip);
    }
    clear();
}
void ChatLine::onTextChanged(QString t)
{
    qDebug()<<t;
}