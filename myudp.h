#pragma once

#include <QCoreApplication>
#include <QUdpSocket>
#include <QBasicTimer>

class MyUDP : public QObject
{
   Q_OBJECT
   QUdpSocket m_socket;
   QBasicTimer m_timer;
   int m_port;

   void timerEvent(QTimerEvent*ev);

public:
   MyUDP(int port);
   void sendUDP();
   Q_SLOT void readyRead();
};
