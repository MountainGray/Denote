#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <QDataStream>
#include <QByteArray>
#include <QIODevice>

class Serializable
{
public:
    virtual void serializeRead(QDataStream &in) = 0;
    virtual void serializeWrite(QDataStream &out) = 0;
    void selfCheck(){
        QByteArray data;
        QDataStream out(&data, QIODevice::WriteOnly);
        serializeWrite(out);
        QDataStream in(&data, QIODevice::ReadOnly);
        serializeRead(in);
    }

    virtual ~Serializable() = default;
};

#endif // SERIALIZABLE_H
