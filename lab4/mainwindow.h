#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QDateEdit>
#include <QComboBox>
#include <QPushButton>
#include <QListWidget>
#include <QTextEdit>
#include <QLabel>
#include <QTabWidget>
#include <QMessageBox>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "room.h"
#include "animal.h"
#include "unit.h"
#include "roomtype.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addAnimal();
    void addUnit();
    void addRoom();
    void addUnitToRoom();
    void removeRoom();
    void removeUnitFromRoom();
    void roomSelectionChanged();
    void unitSelectionChanged();
    void saveToFile();
    void loadFromFile();
    void clearAll();
    void showRoomDetails();

private:
    void setupUI();
    void updateRoomList();
    void updateUnitList();
    void updateAnimalList();
    void clearInputs();

    // UI Components
    QWidget *m_centralWidget;
    QTabWidget *m_tabWidget;

    // Animal
    QWidget *m_animalTab;
    QLineEdit *m_animalNameEdit;
    QLineEdit *m_animalCountryEdit;
    QLineEdit *m_animalMenuEdit;
    QDateEdit *m_animalBirthDateEdit;
    QPushButton *m_addAnimalButton;
    QListWidget *m_animalList;

    // Unit
    QWidget *m_unitTab;
    QComboBox *m_unitAnimalCombo;
    QDateEdit *m_unitArrivalDateEdit;
    QSpinBox *m_unitMaintenanceCostSpin;
    QPushButton *m_addUnitButton;
    QListWidget *m_unitList;

    // Room Tab
    QWidget *m_roomTab;
    QComboBox *m_roomTypeCombo;
    QSpinBox *m_roomNumberSpin;
    QDoubleSpinBox *m_roomSizeSpin;
    QSpinBox *m_roomCleaningCostSpin;
    QPushButton *m_addRoomButton;
    QListWidget *m_roomList;

    // Room Management
    QWidget *m_roomManagementTab;
    QComboBox *m_selectedRoomCombo;
    QComboBox *m_availableUnitCombo;
    QPushButton *m_addUnitToRoomButton;
    QPushButton *m_removeUnitFromRoomButton;
    QPushButton *m_removeRoomButton;
    QListWidget *m_roomUnitsList;
    QTextEdit *m_roomDetailsText;
    QPushButton *m_showRoomDetailsButton;

    QPushButton *m_saveButton;
    QPushButton *m_loadButton;
    QPushButton *m_clearButton;

    // Data
    QList<Animal> m_animals;
    QList<Unit> m_units;
    QList<Room> m_rooms;
};

#endif // MAINWINDOW_H
