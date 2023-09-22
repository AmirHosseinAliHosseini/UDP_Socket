#pragma once

#include <QDataStream>
#include <QString>

struct MyStruct {
    int m_value1;
    int m_value2;
    QString m_string;
   MyStruct() {}
   MyStruct(int v1, int v2, QString s) : m_value1(v1), m_value2(v2), m_string(s) {}
};

template <typename T> T get(QDataStream & str)
{
   T value;
   str >> value;
   return value;
}

QDataStream & operator<<(QDataStream & str, const MyStruct & m)
{
   return str << (QString)m.m_string << (int)m.m_value1 << (int)m.m_value2;
}

QDataStream & operator>>(QDataStream & str, MyStruct & m)
{
   m.m_string = get<QString>(str);
   m.m_value1 = get<int>(str);
   m.m_value2 = get<int>(str);
   return str;
}
