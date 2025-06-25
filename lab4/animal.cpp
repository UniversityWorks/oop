#include "animal.h"
#include <QDateTime>

Animal::Animal()
    : m_name(""), m_country(""), m_menu(""), m_birthDate(QDate::currentDate())
{
}

Animal::Animal(const QString& name, const QString& country, const QString& menu, const QDate& birthDate)
    : m_name(name), m_country(country), m_menu(menu), m_birthDate(birthDate)
{
}

QString Animal::getName() const
{
    return m_name;
}

QString Animal::getCountry() const
{
    return m_country;
}

QString Animal::getMenu() const
{
    return m_menu;
}

QDate Animal::getBirthDate() const
{
    return m_birthDate;
}

void Animal::setName(const QString& name)
{
    m_name = name;
}

void Animal::setCountry(const QString& country)
{
    m_country = country;
}

void Animal::setMenu(const QString& menu)
{
    m_menu = menu;
}

void Animal::setBirthDate(const QDate& birthDate)
{
    m_birthDate = birthDate;
}

int Animal::getAge() const
{
    return m_birthDate.daysTo(QDate::currentDate()) / 365;
}

QString Animal::toString() const
{
    return QString("Тварина: %1, Країна: %2, Меню: %3, Дата народження: %4, Вік: %5 років")
        .arg(m_name)
        .arg(m_country)
        .arg(m_menu)
        .arg(m_birthDate.toString("dd.MM.yyyy"))
        .arg(getAge());
}

QString Animal::toShortString() const
{
    return QString("%1 (%2)").arg(m_name).arg(getAge());
}

QJsonObject Animal::toJson() const
{
    QJsonObject json;
    json["name"] = m_name;
    json["country"] = m_country;
    json["menu"] = m_menu;
    json["birthDate"] = m_birthDate.toString(Qt::ISODate);
    return json;
}

void Animal::fromJson(const QJsonObject& json)
{
    m_name = json["name"].toString();
    m_country = json["country"].toString();
    m_menu = json["menu"].toString();
    m_birthDate = QDate::fromString(json["birthDate"].toString(), Qt::ISODate);
}
