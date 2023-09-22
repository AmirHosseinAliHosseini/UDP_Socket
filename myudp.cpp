#include <QThread>
#include <myudp.h>
#include <data.h>

MyUDP::MyUDP(int port) : m_port(port)
{
   m_timer.start(1000, this);
   connect(&m_socket, SIGNAL(readyRead()), SLOT(readyRead()));
   m_socket.bind(QHostAddress::LocalHost, port);
}

void MyUDP::timerEvent(QTimerEvent* ev)
{
   if (ev->timerId() != m_timer.timerId())
       return;
   sendUDP();
}

void MyUDP::sendUDP()
{
   static MyStruct data(1, 200, "test");

   QByteArray buf;
   QDataStream s(&buf, QIODevice::WriteOnly);
   s << data;


   QThread::sleep(1);
   m_socket.writeDatagram(buf, QHostAddress::LocalHost, m_port);
   qDebug() << "Send packet";
   data.m_value1++;
}

void MyUDP::readyRead()
{
   QHostAddress sender;
   quint16 senderPort;

   MyStruct data;
   while (m_socket.hasPendingDatagrams())
   {
      QByteArray buf(m_socket.pendingDatagramSize(), Qt::Uninitialized);
      QDataStream str(&buf, QIODevice::ReadOnly);
      m_socket.readDatagram(buf.data(), buf.size(), &sender, &senderPort);
      str >> data;

      qDebug() << "Message from: " << sender;
      qDebug() << "Message port: " << senderPort;
      qDebug() << "Message: " << data.m_string << "\t" << data.m_value1 << "\t" << data.m_value2;
   }
}
