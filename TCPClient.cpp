#include "TCPClient.h"

#include <QTcpSocket>
#include <QDebug>

#include "pimpl_impl.hpp"

#include "moc_TCPClient.cpp"


class TCPClient::impl
  : public QTcpSocket
{
  Q_OBJECT

public:
  using port_type = quint16;

  impl (TCPClient * self)
    : self_ {self}
  {
  }

  ~impl ()
  {
  }

  bool isConnected(QString host, port_type port){
      if(host_ != host || port_ != port){
          disconnectFromHost();
          return false;
      }
      return state() == QTcpSocket::ConnectedState ;
  }

  void connectToHost(QString host, port_type port){
      host_ = host;
      port_ = port;

      QTcpSocket::connectToHost(host_, port_);
  }

  qint64 send(QByteArray const &message, bool crlf){
      return write(message + (crlf ? "\r\f" : ""));
  }

  TCPClient * self_;
  QString host_;
  port_type port_;
};

#include "TCPClient.moc"

TCPClient::TCPClient(QObject *parent) : QObject(parent)
  , m_ {this}
{
}

bool TCPClient::ensureConnected(QString host, port_type port, int msecs){
    if(!m_->isConnected(host, port)){
        //qDebug() << "connecting to" << host << port;
        m_->connectToHost(host, port);
    }

    return m_->waitForConnected(msecs);
}

bool TCPClient::sendNetworkMessage(QString host, port_type port, QByteArray const &message, bool crlf){
    if(!ensureConnected(host, port)){
        return false;
    }

    //qDebug() << "connecting to" << host << port;
    qint64 n = m_->send(message, crlf);
    if(n <= 0){
        return false;
    }

    //qDebug() << "sent" << n << "bytes" << message;
    return m_->flush();
}
