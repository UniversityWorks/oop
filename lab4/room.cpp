#include "room.h"

Room::Room()
    : m_roomType(), m_number(0), m_size(0.0), m_cleaningCost(0)
{
}

Room::Room(const RoomType& type, int number, double size, int cleaningCost)
    : m_roomType(type), m_number(number), m_size(size), m_cleaningCost(cleaningCost)
{
}

RoomType Room::getRoomType() const
{
    return m_roomType;
}

int Room::getNumber() const
{
    return m_number;
}

double Room::getSize() const
{
    return m_size;
}

int Room::getCleaningCost() const
{
    return m_cleaningCost;
}

QList<Unit> Room::getUnits() const
{
    return m_units;
}

void Room::setRoomType(const RoomType& type)
{
    m_roomType = type;
}

void Room::setNumber(int number)
{
    m_number = number;
}

void Room::setSize(double size)
{
    m_size = size;
}

void Room::setCleaningCost(int cost)
{
    m_cleaningCost = cost;
}

void Room::addUnit(const Unit& unit)
{
    m_units.append(unit);
}

void Room::removeUnit(int index)
{
    if (index >= 0 && index < m_units.size()) {
        m_units.removeAt(index);
    }
}

void Room::clearUnits()
{
    m_units.clear();
}

int Room::getUnitCount() const
{
    return m_units.size();
}

Unit Room::getUnit(int index) const
{
    if (index >= 0 && index < m_units.size()) {
        return m_units.at(index);
    }
    return Unit();
}

int Room::getTotalMaintenanceCost() const
{
    int total = m_cleaningCost;
    for (const Unit& unit : m_units) {
        total += unit.getMaintenanceCost();
    }
    return total;
}

double Room::getAverageMaintenanceCost() const
{
    if (m_units.isEmpty()) {
        return 0.0;
    }

    int totalAnimalCost = 0;
    for (const Unit& unit : m_units) {
        totalAnimalCost += unit.getMaintenanceCost();
    }

    return static_cast<double>(totalAnimalCost) / m_units.size();
}

QString Room::toString() const
{
    QString result = QString("Приміщення №%1\nТип: %2\nРозмір: %3 кв.м\nВартість прибирання: %4 грн\nКількість тварин: %5\n")
    .arg(m_number)
    .arg(m_roomType.toString())
    .arg(m_size)
    .arg(m_cleaningCost)
    .arg(m_units.size());

    if (!m_units.isEmpty()) {
        result += "Тварини:\n";
        for (int i = 0; i < m_units.size(); ++i) {
            result += QString("%1. %2\n").arg(i + 1).arg(m_units[i].toShortString());
        }
    }

    result += QString("Загальна вартість утримання: %1 грн").arg(getTotalMaintenanceCost());

    return result;
}

QString Room::toShortString() const
{
    return QString("№%1 %2 (%3 тв.)")
        .arg(m_number)
        .arg(m_roomType.toShortString())
        .arg(m_units.size());
}

QJsonObject Room::toJson() const
{
    QJsonObject json;
    json["roomType"] = m_roomType.toJson();
    json["number"] = m_number;
    json["size"] = m_size;
    json["cleaningCost"] = m_cleaningCost;

    QJsonArray unitsArray;
    for (const Unit& unit : m_units) {
        unitsArray.append(unit.toJson());
    }
    json["units"] = unitsArray;

    return json;
}

void Room::fromJson(const QJsonObject& json)
{
    m_roomType.fromJson(json["roomType"].toObject());
    m_number = json["number"].toInt();
    m_size = json["size"].toDouble();
    m_cleaningCost = json["cleaningCost"].toInt();

    m_units.clear();
    QJsonArray unitsArray = json["units"].toArray();
    for (const QJsonValue& value : unitsArray) {
        Unit unit;
        unit.fromJson(value.toObject());
        m_units.append(unit);
    }
}
