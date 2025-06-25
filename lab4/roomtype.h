#ifndef ROOMTYPE_H
#define ROOMTYPE_H

#include <QString>
#include <QJsonObject>

class RoomType
{
public:
    enum Type {
        CAGE,
        ENCLOSURE,
        AQUARIUM,
        TERRARIUM
    };

    RoomType();
    RoomType(Type type);
    RoomType(const QString& typeString);

    Type getType() const;
    void setType(Type type);
    void setType(const QString& typeString);

    QString toString() const;
    QString toShortString() const;

    //json
    QJsonObject toJson() const;
    void fromJson(const QJsonObject& json);

    static QString typeToString(Type type);
    static Type stringToType(const QString& str);

private:
    Type m_type;
};

#endif // ROOMTYPE_H
