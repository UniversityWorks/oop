#ifndef UNIT_H
#define UNIT_H

#include "animal.h"
#include <QDate>
#include <QJsonObject>

class Unit
{
public:
    Unit();
    Unit(const Animal& animal, const QDate& arrivalDate, int maintenanceCost);


    Animal getAnimal() const;
    QDate getArrivalDate() const;
    int getMaintenanceCost() const;


    void setAnimal(const Animal& animal);
    void setArrivalDate(const QDate& arrivalDate);
    void setMaintenanceCost(int cost);


    int getDaysInZoo() const;
    QString toString() const;
    QString toShortString() const;

    // json
    QJsonObject toJson() const;
    void fromJson(const QJsonObject& json);

private:
    Animal m_animal;
    QDate m_arrivalDate;
    int m_maintenanceCost;
};

#endif // UNIT_H
