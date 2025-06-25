#ifndef ANIMAL_H
#define ANIMAL_H

#include <QString>
#include <QDate>
#include <QJsonObject>

class Animal
{
public:
    Animal();
    Animal(const QString& name, const QString& country, const QString& menu, const QDate& birthDate);

    // Getters
    QString getName() const;
    QString getCountry() const;
    QString getMenu() const;
    QDate getBirthDate() const;

    // Setters
    void setName(const QString& name);
    void setCountry(const QString& country);
    void setMenu(const QString& menu);
    void setBirthDate(const QDate& birthDate);

    // Utility methods
    int getAge() const;
    QString toString() const;
    QString toShortString() const;

    // JSON serialization
    QJsonObject toJson() const;
    void fromJson(const QJsonObject& json);

private:
    QString m_name;
    QString m_country;
    QString m_menu;
    QDate m_birthDate;
};

#endif // ANIMAL_H
