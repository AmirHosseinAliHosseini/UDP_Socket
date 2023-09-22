#include <QCoreApplication>
#include <myudp.h>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyUDP client(1234);


    return a.exec();
}
