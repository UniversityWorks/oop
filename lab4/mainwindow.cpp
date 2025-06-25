#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUI();
    setWindowTitle("lab4");
    resize(800, 600);
}

MainWindow::~MainWindow() {}

void MainWindow::setupUI()
{
    m_centralWidget = new QWidget(this);
    setCentralWidget(m_centralWidget);

    m_tabWidget = new QTabWidget(m_centralWidget);

    // Animal Tab
    m_animalTab = new QWidget();
    QVBoxLayout *animalLayout = new QVBoxLayout(m_animalTab);

    QGroupBox *animalInputGroup = new QGroupBox("Додати тварину");
    QFormLayout *animalFormLayout = new QFormLayout(animalInputGroup);

    m_animalNameEdit = new QLineEdit();
    m_animalCountryEdit = new QLineEdit();
    m_animalMenuEdit = new QLineEdit();
    m_animalBirthDateEdit = new QDateEdit(QDate::currentDate());
    m_animalBirthDateEdit->setCalendarPopup(true);
    m_addAnimalButton = new QPushButton("Додати тварину");

    animalFormLayout->addRow("Назва:", m_animalNameEdit);
    animalFormLayout->addRow("Країна походження:", m_animalCountryEdit);
    animalFormLayout->addRow("Меню:", m_animalMenuEdit);
    animalFormLayout->addRow("Дата народження:", m_animalBirthDateEdit);
    animalFormLayout->addRow(m_addAnimalButton);

    m_animalList = new QListWidget();

    animalLayout->addWidget(animalInputGroup);
    animalLayout->addWidget(new QLabel("Список тварин:"));
    animalLayout->addWidget(m_animalList);

    // Unit
    m_unitTab = new QWidget();
    QVBoxLayout *unitLayout = new QVBoxLayout(m_unitTab);

    QGroupBox *unitInputGroup = new QGroupBox("Додати одиницю обліку");
    QFormLayout *unitFormLayout = new QFormLayout(unitInputGroup);

    m_unitAnimalCombo = new QComboBox();
    m_unitArrivalDateEdit = new QDateEdit(QDate::currentDate());
    m_unitArrivalDateEdit->setCalendarPopup(true);
    m_unitMaintenanceCostSpin = new QSpinBox();
    m_unitMaintenanceCostSpin->setRange(0, 999999);
    m_unitMaintenanceCostSpin->setSuffix(" грн");
    m_addUnitButton = new QPushButton("Додати одиницю обліку");

    unitFormLayout->addRow("Тварина:", m_unitAnimalCombo);
    unitFormLayout->addRow("Дата прибуття:", m_unitArrivalDateEdit);
    unitFormLayout->addRow("Вартість утримання:", m_unitMaintenanceCostSpin);
    unitFormLayout->addRow(m_addUnitButton);

    m_unitList = new QListWidget();

    unitLayout->addWidget(unitInputGroup);
    unitLayout->addWidget(new QLabel("Список одиниць обліку:"));
    unitLayout->addWidget(m_unitList);

    // Room
    m_roomTab = new QWidget();
    QVBoxLayout *roomLayout = new QVBoxLayout(m_roomTab);

    QGroupBox *roomInputGroup = new QGroupBox("Додати приміщення");
    QFormLayout *roomFormLayout = new QFormLayout(roomInputGroup);

    m_roomTypeCombo = new QComboBox();
    m_roomTypeCombo->addItems({"Клітка", "Вольєр", "Акваріум", "Терраріум"});
    m_roomNumberSpin = new QSpinBox();
    m_roomNumberSpin->setRange(1, 9999);
    m_roomSizeSpin = new QDoubleSpinBox();
    m_roomSizeSpin->setRange(0.1, 9999.9);
    m_roomSizeSpin->setSuffix(" кв.м");
    m_roomSizeSpin->setDecimals(1);
    m_roomCleaningCostSpin = new QSpinBox();
    m_roomCleaningCostSpin->setRange(0, 999999);
    m_roomCleaningCostSpin->setSuffix(" грн");
    m_addRoomButton = new QPushButton("Додати приміщення");

    roomFormLayout->addRow("Тип приміщення:", m_roomTypeCombo);
    roomFormLayout->addRow("Номер:", m_roomNumberSpin);
    roomFormLayout->addRow("Розмір:", m_roomSizeSpin);
    roomFormLayout->addRow("Вартість прибирання:", m_roomCleaningCostSpin);
    roomFormLayout->addRow(m_addRoomButton);

    m_roomList = new QListWidget();

    roomLayout->addWidget(roomInputGroup);
    roomLayout->addWidget(new QLabel("Список приміщень:"));
    roomLayout->addWidget(m_roomList);

    // Room Management
    m_roomManagementTab = new QWidget();
    QVBoxLayout *roomMgmtLayout = new QVBoxLayout(m_roomManagementTab);

    QGroupBox *roomMgmtGroup = new QGroupBox("Управління приміщеннями");
    QFormLayout *roomMgmtFormLayout = new QFormLayout(roomMgmtGroup);

    m_selectedRoomCombo = new QComboBox();
    m_availableUnitCombo = new QComboBox();
    m_addUnitToRoomButton = new QPushButton("Додати тварину в приміщення");
    m_removeUnitFromRoomButton = new QPushButton("Видалити тварину з приміщення");
    m_removeRoomButton = new QPushButton("Видалити приміщення");
    m_showRoomDetailsButton = new QPushButton("Показати деталі приміщення");

    roomMgmtFormLayout->addRow("Приміщення:", m_selectedRoomCombo);
    roomMgmtFormLayout->addRow("Доступні одиниці обліку:", m_availableUnitCombo);

    QHBoxLayout *buttonLayout1 = new QHBoxLayout();
    buttonLayout1->addWidget(m_addUnitToRoomButton);
    buttonLayout1->addWidget(m_removeUnitFromRoomButton);
    roomMgmtFormLayout->addRow(buttonLayout1);

    QHBoxLayout *buttonLayout2 = new QHBoxLayout();
    buttonLayout2->addWidget(m_removeRoomButton);
    buttonLayout2->addWidget(m_showRoomDetailsButton);
    roomMgmtFormLayout->addRow(buttonLayout2);

    m_roomUnitsList = new QListWidget();
    m_roomDetailsText = new QTextEdit();
    m_roomDetailsText->setReadOnly(true);

    roomMgmtLayout->addWidget(roomMgmtGroup);
    roomMgmtLayout->addWidget(new QLabel("Тварини в приміщенні:"));
    roomMgmtLayout->addWidget(m_roomUnitsList);
    roomMgmtLayout->addWidget(new QLabel("Деталі приміщення:"));
    roomMgmtLayout->addWidget(m_roomDetailsText);

    // tabs
    m_tabWidget->addTab(m_animalTab, "Тварини");
    m_tabWidget->addTab(m_unitTab, "Одиниці обліку");
    m_tabWidget->addTab(m_roomTab, "Приміщення");
    m_tabWidget->addTab(m_roomManagementTab, "Управління");

    // File operations
    QHBoxLayout *fileLayout = new QHBoxLayout();
    m_saveButton = new QPushButton("Зберегти в JSON");
    m_loadButton = new QPushButton("Завантажити з JSON");
    m_clearButton = new QPushButton("Очистити все");

    fileLayout->addWidget(m_saveButton);
    fileLayout->addWidget(m_loadButton);
    fileLayout->addWidget(m_clearButton);
    fileLayout->addStretch();

    // Main layout
    QVBoxLayout *mainLayout = new QVBoxLayout(m_centralWidget);
    mainLayout->addWidget(m_tabWidget);
    mainLayout->addLayout(fileLayout);

    // signals
    connect(m_addAnimalButton, &QPushButton::clicked, this, &MainWindow::addAnimal);
    connect(m_addUnitButton, &QPushButton::clicked, this, &MainWindow::addUnit);
    connect(m_addRoomButton, &QPushButton::clicked, this, &MainWindow::addRoom);
    connect(m_addUnitToRoomButton, &QPushButton::clicked, this, &MainWindow::addUnitToRoom);
    connect(m_removeUnitFromRoomButton, &QPushButton::clicked, this, &MainWindow::removeUnitFromRoom);
    connect(m_removeRoomButton, &QPushButton::clicked, this, &MainWindow::removeRoom);
    connect(m_showRoomDetailsButton, &QPushButton::clicked, this, &MainWindow::showRoomDetails);
    connect(m_selectedRoomCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::roomSelectionChanged);
    connect(m_roomUnitsList, &QListWidget::currentRowChanged, this, &MainWindow::unitSelectionChanged);
    connect(m_saveButton, &QPushButton::clicked, this, &MainWindow::saveToFile);
    connect(m_loadButton, &QPushButton::clicked, this, &MainWindow::loadFromFile);
    connect(m_clearButton, &QPushButton::clicked, this, &MainWindow::clearAll);
}

void MainWindow::addAnimal()
{
    QString name = m_animalNameEdit->text().trimmed();
    QString country = m_animalCountryEdit->text().trimmed();
    QString menu = m_animalMenuEdit->text().trimmed();
    QDate birthDate = m_animalBirthDateEdit->date();

    if (name.isEmpty() || country.isEmpty() || menu.isEmpty())
    {
        QMessageBox::warning(this, "Помилка", "Будь ласка, заповніть всі поля для тварини.");
        return;
    }

    Animal animal(name, country, menu, birthDate);
    m_animals.append(animal);

    updateAnimalList();
    clearInputs();

    QMessageBox::information(this, "Успіх", "Тварину додано успішно!");
}

void MainWindow::addUnit()
{
    if (m_unitAnimalCombo->currentIndex() < 0)
    {
        QMessageBox::warning(this, "Помилка", "Спочатку додайте тварину.");
        return;
    }

    Animal selectedAnimal = m_animals.at(m_unitAnimalCombo->currentIndex());
    QDate arrivalDate = m_unitArrivalDateEdit->date();
    int maintenanceCost = m_unitMaintenanceCostSpin->value();

    Unit unit(selectedAnimal, arrivalDate, maintenanceCost);
    m_units.append(unit);

    updateUnitList();

    QMessageBox::information(this, "Успіх", "Одиницю обліку додано успішно!");
}

void MainWindow::addRoom()
{
    RoomType roomType(m_roomTypeCombo->currentText());
    int number = m_roomNumberSpin->value();
    double size = m_roomSizeSpin->value();
    int cleaningCost = m_roomCleaningCostSpin->value();

    // Check if room number already exists
    for (const Room& room : m_rooms)
    {
        if (room.getNumber() == number)
        {
            QMessageBox::warning(this, "Помилка", "Приміщення з таким номером вже існує.");
            return;
        }
    }

    Room room(roomType, number, size, cleaningCost);
    m_rooms.append(room);

    updateRoomList();

    QMessageBox::information(this, "Успіх", "Приміщення додано успішно!");
}

void MainWindow::addUnitToRoom()
{
    int roomIndex = m_selectedRoomCombo->currentIndex();
    int unitIndex = m_availableUnitCombo->currentIndex();

    if (roomIndex < 0 || unitIndex < 0) {
        QMessageBox::warning(this, "Помилка", "Оберіть приміщення та одиницю обліку.");
        return;
    }

    // Check if unit is already assigned to any room
    for (const Room& room : m_rooms) {
        for (const Unit& unit : room.getUnits()) {
            if (unit.getAnimal().getName() == m_units[unitIndex].getAnimal().getName() &&
                unit.getArrivalDate() == m_units[unitIndex].getArrivalDate()) {
                QMessageBox::warning(this, "Помилка", "Ця одиниця обліку вже призначена до приміщення.");
                return;
            }
        }
    }

    m_rooms[roomIndex].addUnit(m_units[unitIndex]);
    m_units.removeAt(unitIndex);

    updateUnitList();
    updateRoomList();
    roomSelectionChanged();

    QMessageBox::information(this, "Успіх", "Тварину додано до приміщення!");
}

void MainWindow::removeUnitFromRoom()
{
    int roomIndex = m_selectedRoomCombo->currentIndex();
    int unitIndex = m_roomUnitsList->currentRow();

    if (roomIndex < 0 || unitIndex < 0) {
        QMessageBox::warning(this, "Помилка", "Оберіть приміщення та тварину для видалення.");
        return;
    }

    Unit unit = m_rooms[roomIndex].getUnit(unitIndex);
    m_units.append(unit);
    m_rooms[roomIndex].removeUnit(unitIndex);

    updateUnitList();
    roomSelectionChanged();

    QMessageBox::information(this, "Успіх", "Тварину видалено з приміщення!");
}

void MainWindow::removeRoom()
{
    int roomIndex = m_selectedRoomCombo->currentIndex();

    if (roomIndex < 0) {
        QMessageBox::warning(this, "Помилка", "Оберіть приміщення для видалення.");
        return;
    }

    QList<Unit> roomUnits = m_rooms[roomIndex].getUnits();
    for (const Unit& unit : roomUnits) {
        m_units.append(unit);
    }

    m_rooms.removeAt(roomIndex);

    updateRoomList();
    updateUnitList();

    QMessageBox::information(this, "Успіх", "Приміщення видалено!");
}

void MainWindow::roomSelectionChanged()
{
    int index = m_selectedRoomCombo->currentIndex();
    m_roomUnitsList->clear();

    if (index >= 0 && index < m_rooms.size()) {
        QList<Unit> units = m_rooms[index].getUnits();
        for (const Unit& unit : units) {
            m_roomUnitsList->addItem(unit.toShortString());
        }
    }
}

void MainWindow::unitSelectionChanged() {}

void MainWindow::showRoomDetails()
{
    int index = m_selectedRoomCombo->currentIndex();

    if (index >= 0 && index < m_rooms.size()) {
        m_roomDetailsText->setPlainText(m_rooms[index].toString());
    }
    else {
        m_roomDetailsText->clear();
    }
}

void MainWindow::saveToFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Зберегти дані", "", "JSON Files (*.json)");

    if (fileName.isEmpty()) return;

    QJsonObject mainObject;

    // Save animals to json
    QJsonArray animalsArray;
    for (const Animal& animal : m_animals)
    {
        animalsArray.append(animal.toJson());
    }
    mainObject["animals"] = animalsArray;

    // Save units to json
    QJsonArray unitsArray;
    for (const Unit& unit : m_units) {
        unitsArray.append(unit.toJson());
    }
    mainObject["units"] = unitsArray;

    // Save rooms to json
    QJsonArray roomsArray;
    for (const Room& room : m_rooms) {
        roomsArray.append(room.toJson());
    }
    mainObject["rooms"] = roomsArray;

    QJsonDocument document(mainObject);

    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(document.toJson());
        file.close();
        QMessageBox::information(this, "Успіх", "Дані збережено успішно!");
    } else {
        QMessageBox::critical(this, "Помилка", "Не вдалося зберегти файл.");
    }
}

void MainWindow::loadFromFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Завантажити дані", "", "JSON Files (*.json)");

    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, "Помилка", "Не вдалося відкрити файл.");
        return;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument document = QJsonDocument::fromJson(data);
    QJsonObject mainObject = document.object();

    m_animals.clear();
    m_units.clear();
    m_rooms.clear();

    // Load animals
    QJsonArray animalsArray = mainObject["animals"].toArray();
    for (const QJsonValue& value : animalsArray) {
        Animal animal;
        animal.fromJson(value.toObject());
        m_animals.append(animal);
    }

    // Load units
    QJsonArray unitsArray = mainObject["units"].toArray();
    for (const QJsonValue& value : unitsArray) {
        Unit unit;
        unit.fromJson(value.toObject());
        m_units.append(unit);
    }

    // Load rooms
    QJsonArray roomsArray = mainObject["rooms"].toArray();
    for (const QJsonValue& value : roomsArray) {
        Room room;
        room.fromJson(value.toObject());
        m_rooms.append(room);
    }

    updateAnimalList();
    updateUnitList();
    updateRoomList();

    QMessageBox::information(this, "Успіх", "Дані завантажено успішно!");
}

void MainWindow::clearAll()
{
    int result = QMessageBox::question(this, "Підтвердження", "Ви впевнені, що хочете очистити всі дані?", QMessageBox::Yes | QMessageBox::No);

    if (result == QMessageBox::Yes)
    {
        m_animals.clear();
        m_units.clear();
        m_rooms.clear();

        updateAnimalList();
        updateUnitList();
        updateRoomList();
        clearInputs();
        m_roomDetailsText->clear();

        QMessageBox::information(this, "Успіх", "Всі дані очищено!");
    }
}

void MainWindow::updateAnimalList()
{
    m_animalList->clear();
    m_unitAnimalCombo->clear();

    for (const Animal& animal : m_animals) {
        m_animalList->addItem(animal.toShortString());
        m_unitAnimalCombo->addItem(animal.toShortString());
    }
}

void MainWindow::updateUnitList()
{
    m_unitList->clear();
    m_availableUnitCombo->clear();

    for (const Unit& unit : m_units) {
        m_unitList->addItem(unit.toShortString());
        m_availableUnitCombo->addItem(unit.toShortString());
    }
}

void MainWindow::updateRoomList()
{
    m_roomList->clear();
    m_selectedRoomCombo->clear();

    for (const Room& room : m_rooms) {
        m_roomList->addItem(room.toShortString());
        m_selectedRoomCombo->addItem(room.toShortString());
    }

    roomSelectionChanged();
}

void MainWindow::clearInputs()
{
    m_animalNameEdit->clear();
    m_animalCountryEdit->clear();
    m_animalMenuEdit->clear();
    m_animalBirthDateEdit->setDate(QDate::currentDate());

    m_unitArrivalDateEdit->setDate(QDate::currentDate());
    m_unitMaintenanceCostSpin->setValue(0);

    m_roomNumberSpin->setValue(1);
    m_roomSizeSpin->setValue(1.0);
    m_roomCleaningCostSpin->setValue(0);
}
