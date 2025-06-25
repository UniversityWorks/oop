#ifndef ROOM_H
#define ROOM_H

#include "roomtype.h"
#include "unit.h"
#include <QList>
#include <QJsonObject>
#include <QJsonArray>

class Room
{
public:
    Room();
    Room(const RoomType& type, int number, double size, int cleaningCost);

    RoomType getRoomType() const;
    int getNumber() const;
    double getSize() const;
    int getCleaningCost() const;
    QList<Unit> getUnits() const;

    void setRoomType(const RoomType& type);
    void setNumber(int number);
    void setSize(double size);
    void setCleaningCost(int cost);

    void addUnit(const Unit& unit);
    void removeUnit(int index);
    void clearUnits();
    int getUnitCount() const;
    Unit getUnit(int index) const;

    int getTotalMaintenanceCost() const;
    double getAverageMaintenanceCost() const;

    QString toString() const;
    QString toShortString() const;

    //json
    QJsonObject toJson() const;
    void fromJson(const QJsonObject& json);

private:
    RoomType m_roomType;
    int m_number;
    double m_size;
    int m_cleaningCost;
    QList<Unit> m_units;
};

#endif // ROOM_H
