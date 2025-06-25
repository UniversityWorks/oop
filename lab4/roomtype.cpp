#include "roomtype.h"

RoomType::RoomType() : m_type(CAGE)
{
}

RoomType::RoomType(Type type) : m_type(type)
{
}

RoomType::RoomType(const QString& typeString)
{
    setType(typeString);
}

RoomType::Type RoomType::getType() const
{
    return m_type;
}

void RoomType::setType(Type type)
{
    m_type = type;
}

void RoomType::setType(const QString& typeString)
{
    m_type = stringToType(typeString);
}

QString RoomType::toString() const
{
    return typeToString(m_type);
}

QString RoomType::toShortString() const
{
    switch (m_type) {
    case CAGE: return "Кл";
    case ENCLOSURE: return "Вол";
    case AQUARIUM: return "Акв";
    case TERRARIUM: return "Тер";
    default: return "Н/В";
    }
}

QJsonObject RoomType::toJson() const
{
    QJsonObject json;
    json["type"] = toString();
    return json;
}

void RoomType::fromJson(const QJsonObject& json)
{
    setType(json["type"].toString());
}

QString RoomType::typeToString(Type type)
{
    switch (type) {
    case CAGE: return "Клітка";
    case ENCLOSURE: return "Вольєр";
    case AQUARIUM: return "Акваріум";
    case TERRARIUM: return "Терраріум";
    default: return "Невідомо";
    }
}

RoomType::Type RoomType::stringToType(const QString& str)
{
    if (str == "Клітка") return CAGE;
    if (str == "Вольєр") return ENCLOSURE;
    if (str == "Акваріум") return AQUARIUM;
    if (str == "Терраріум") return TERRARIUM;
    return CAGE;
}
