#include "unit.h"

Unit::Unit()
    : m_animal(), m_arrivalDate(QDate::currentDate()), m_maintenanceCost(0)
{
}

Unit::Unit(const Animal& animal, const QDate& arrivalDate, int maintenanceCost)
    : m_animal(animal), m_arrivalDate(arrivalDate), m_maintenanceCost(maintenanceCost)
{
}

Animal Unit::getAnimal() const
{
    return m_animal;
}

QDate Unit::getArrivalDate() const
{
    return m_arrivalDate;
}

int Unit::getMaintenanceCost() const
{
    return m_maintenanceCost;
}

void Unit::setAnimal(const Animal& animal)
{
    m_animal = animal;
}

void Unit::setArrivalDate(const QDate& arrivalDate)
{
    m_arrivalDate = arrivalDate;
}

void Unit::setMaintenanceCost(int cost)
{
    m_maintenanceCost = cost;
}

int Unit::getDaysInZoo() const
{
    return m_arrivalDate.daysTo(QDate::currentDate());
}

QString Unit::toString() const
{
    return QString("Одиниця обліку:\n%1\nДата прибуття: %2\nДнів у зоопарку: %3\nВартість утримання: %4 грн")
        .arg(m_animal.toString())
        .arg(m_arrivalDate.toString("dd.MM.yyyy"))
        .arg(getDaysInZoo())
        .arg(m_maintenanceCost);
}

QString Unit::toShortString() const
{
    return QString("%1 - %2 грн").arg(m_animal.toShortString()).arg(m_maintenanceCost);
}

QJsonObject Unit::toJson() const
{
    QJsonObject json;
    json["animal"] = m_animal.toJson();
    json["arrivalDate"] = m_arrivalDate.toString(Qt::ISODate);
    json["maintenanceCost"] = m_maintenanceCost;
    return json;
}

void Unit::fromJson(const QJsonObject& json)
{
    m_animal.fromJson(json["animal"].toObject());
    m_arrivalDate = QDate::fromString(json["arrivalDate"].toString(), Qt::ISODate);
    m_maintenanceCost = json["maintenanceCost"].toInt();
}
