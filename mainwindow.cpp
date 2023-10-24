#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "directories.h"

ClientsDir clientsDirectory(10);
InsurancesDir insurancesDirectory(100);

bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->clientsSearchField->setValidator(new QRegularExpressionValidator(QRegularExpression("[A-Za-z0-9_.+]{0,255}"), this));
    ui->clientsAddNameEdit->setValidator(new QRegularExpressionValidator(QRegularExpression("[A-Za-z_]{0,255}"), this));
    ui->clientsAddBirthdateEdit->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9.]{0,255}"), this));
    ui->clientsAddPhoneEdit->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9+]{0,255}"), this));
    ui->clientsAddIDEdit->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]{0,255}"), this));
    ui->clientsRemoveEdit->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]{0,255}"), this));
    ui->tabWidget->setDisabled(true);
    ui->fileSection->setDisabled(true);
    ui->clientsSizeEdit->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]{0,5}"), this));
    ui->agentsSizeEdit->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]{0,5}"), this));
    ui->insurancesSizeEdit->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]{0,5}"), this));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_loadButton_clicked()
{
    bool load_fail = 0;
    std::string clients_file_path = "../" + ui->fileForm->text().toStdString() + "/clients.txt";
    load_fail = clientsDirectory.LOAD(clients_file_path);

    if (load_fail) {
        ui->statusbar->showMessage(QString("Такой директории не существует"), 3000);
        return;
    }




    ui->clientsTable->clear();
    ui->clientsTable->setColumnCount(4);
    ui->clientsTable->setRowCount(clientsDirectory.clientsList.size());
    ui->clientsTable->setHorizontalHeaderLabels(QStringList() << "Имя" << "Дата рождения" << "Номер телефона" << "Паспорт");
    ui->clientsTable->setColumnWidth(0, 320);
    ui->clientsTable->setColumnWidth(1, 150);
    ui->clientsTable->setColumnWidth(2, 150);
    ui->clientsTable->setColumnWidth(3, 130);

    for (int i = 0; i < clientsDirectory.clientsList.size(); i++) {
        int j = 0;
        QTableWidgetItem* name = new QTableWidgetItem(QString::fromStdString(clientsDirectory.clientsList[i].name));
        ui->clientsTable->setItem(i, j, name);
        j++;
        QTableWidgetItem* birthday = new QTableWidgetItem(QString::fromStdString(clientsDirectory.clientsList[i].birthday));
        ui->clientsTable->setItem(i, j, birthday);
        j++;
        QTableWidgetItem* phone = new QTableWidgetItem(QString::fromStdString(clientsDirectory.clientsList[i].phone_number));
        ui->clientsTable->setItem(i, j, phone);
        j++;
        QTableWidgetItem* id = new QTableWidgetItem(QString::fromStdString(clientsDirectory.clientsList[i].ID));
        ui->clientsTable->setItem(i, j, id);
//        client_ref = client_ref->next;
    }

    ui->statusbar->showMessage(QString("Справочники загружены"), 3000);
}


void MainWindow::on_saveButton_clicked()
{
    std::string clients_file_path = "../" + ui->fileForm->text().toStdString() + "/clients.txt";
    int save_status = clientsDirectory.SAVE(clients_file_path);

    if (save_status == 2) {
        ui->statusbar->showMessage(QString("Файл повреждён"), 3000);
        return;
    }
    if (save_status == 1) {
        ui->statusbar->showMessage(QString("Такой директории не существует"), 3000);
        return;
    }
    ui->statusbar->showMessage(QString("Справочники сохранены"), 3000);
}


void MainWindow::on_clientsNameSearch_clicked()
{
    if (clientsDirectory.clientsList.size() == 0) {
        ui->statusbar->showMessage(QString("Справочник пуст"), 1000);
        return;
    }
    if (ui->clientsSearchField->text() == "") {
        ui->statusbar->showMessage(QString("Поле для поиска не задано"), 1000);
        return;
    }
    std::string field_to_find = ui->clientsSearchField->text().toStdString();
    NodeClientTree* node = clientsDirectory.clientsNameTree.searchTree(field_to_find);
    if (node->val.head == nullptr) {
        ui->statusbar->showMessage(QString("Поле не найдено"), 2000);
        return;
    }
    ui->clientsSearchResult->clear();
    ui->clientsSearchResult->setColumnCount(5);
    ui->clientsSearchResult->setRowCount(node->val.size());
    ui->clientsSearchResult->setHorizontalHeaderLabels(QStringList() << "В массиве" << "Имя" << "Дата рождения" << "Номер телефона" << "Паспорт");
    ui->clientsSearchResult->setColumnWidth(0, 70);
    ui->clientsSearchResult->setColumnWidth(1, 250);
    ui->clientsSearchResult->setColumnWidth(2, 150);
    ui->clientsSearchResult->setColumnWidth(3, 150);
    ui->clientsSearchResult->setColumnWidth(4, 130);

    NodeClientList* p = node->val.head;
    int i = 0;
    while (p) {
        int j = 0;
        QTableWidgetItem* order = new QTableWidgetItem(QString::number(p->val.order));
        ui->clientsSearchResult->setItem(i, j, order);
        j++;
        QTableWidgetItem* name = new QTableWidgetItem(QString::fromStdString(p->val.name));
        ui->clientsSearchResult->setItem(i, j, name);
        j++;
        QTableWidgetItem* birthday = new QTableWidgetItem(QString::fromStdString(p->val.birthday));
        ui->clientsSearchResult->setItem(i, j, birthday);
        j++;
        QTableWidgetItem* phone = new QTableWidgetItem(QString::fromStdString(p->val.phone_number));
        ui->clientsSearchResult->setItem(i, j, phone);
        j++;
        QTableWidgetItem* id = new QTableWidgetItem(QString::fromStdString(p->val.ID));
        ui->clientsSearchResult->setItem(i, j, id);
        p = p->next;
        i++;
    }
    int comparisons_done = clientsDirectory.clientsNameTree.countSearchComparisons(field_to_find);
    ui->statusbar->showMessage(QString("Найдено " + QString::number(i) + " записей. Выполнено " + QString::number(comparisons_done) + " сравнений."));
}


void MainWindow::on_clientsBirthdaySearch_clicked()
{
    if (clientsDirectory.clientsList.size() == 0) {
        ui->statusbar->showMessage(QString("Справочник пуст"), 1000);
        return;
    }
    if (ui->clientsSearchField->text() == "") {
        ui->statusbar->showMessage(QString("Поле для поиска не задано"), 1000);
        return;
    }
    std::string field_to_find = ui->clientsSearchField->text().toStdString();
    NodeClientTree* node = clientsDirectory.clientsBirthdayTree.searchTree(field_to_find);
    if (node->val.head == nullptr) {
        ui->statusbar->showMessage(QString("Поле не найдено"), 2000);
        return;
    }
    ui->clientsSearchResult->clear();
    ui->clientsSearchResult->setColumnCount(5);
    ui->clientsSearchResult->setRowCount(node->val.size());
    ui->clientsSearchResult->setHorizontalHeaderLabels(QStringList() << "В массиве" << "Имя" << "Дата рождения" << "Номер телефона" << "Паспорт");
    ui->clientsSearchResult->setColumnWidth(0, 70);
    ui->clientsSearchResult->setColumnWidth(1, 250);
    ui->clientsSearchResult->setColumnWidth(2, 150);
    ui->clientsSearchResult->setColumnWidth(3, 150);
    ui->clientsSearchResult->setColumnWidth(4, 130);

    NodeClientList* p = node->val.head;
    int i = 0;
    while (p) {
        int j = 0;
        QTableWidgetItem* order = new QTableWidgetItem(QString::number(p->val.order));
        ui->clientsSearchResult->setItem(i, j, order);
        j++;
        QTableWidgetItem* name = new QTableWidgetItem(QString::fromStdString(p->val.name));
        ui->clientsSearchResult->setItem(i, j, name);
        j++;
        QTableWidgetItem* birthday = new QTableWidgetItem(QString::fromStdString(p->val.birthday));
        ui->clientsSearchResult->setItem(i, j, birthday);
        j++;
        QTableWidgetItem* phone = new QTableWidgetItem(QString::fromStdString(p->val.phone_number));
        ui->clientsSearchResult->setItem(i, j, phone);
        j++;
        QTableWidgetItem* id = new QTableWidgetItem(QString::fromStdString(p->val.ID));
        ui->clientsSearchResult->setItem(i, j, id);
        p = p->next;
        i++;
    }
    int comparisons_done = clientsDirectory.clientsBirthdayTree.countSearchComparisons(field_to_find);
    ui->statusbar->showMessage(QString("Найдено " + QString::number(i) + " записей. Выполнено " + QString::number(comparisons_done) + " сравнений."));
}


void MainWindow::on_clientsNumSearch_clicked()
{
    if (clientsDirectory.clientsList.size() == 0) {
        ui->statusbar->showMessage(QString("Справочник пуст"), 1000);
        return;
    }
    if (ui->clientsSearchField->text() == "") {
        ui->statusbar->showMessage(QString("Поле для поиска не задано"), 1000);
        return;
    }
    std::string field_to_find = ui->clientsSearchField->text().toStdString();
    NodeClientTree* node = clientsDirectory.clientsPhoneTree.searchTree(field_to_find);
    if (node->val.head == nullptr) {
        ui->statusbar->showMessage(QString("Поле не найдено"), 2000);
        return;
    }
    ui->clientsSearchResult->clear();
    ui->clientsSearchResult->setColumnCount(5);
    ui->clientsSearchResult->setRowCount(node->val.size());
    ui->clientsSearchResult->setHorizontalHeaderLabels(QStringList() << "В массиве" << "Имя" << "Дата рождения" << "Номер телефона" << "Паспорт");
    ui->clientsSearchResult->setColumnWidth(0, 70);
    ui->clientsSearchResult->setColumnWidth(1, 250);
    ui->clientsSearchResult->setColumnWidth(2, 150);
    ui->clientsSearchResult->setColumnWidth(3, 150);
    ui->clientsSearchResult->setColumnWidth(4, 130);

    NodeClientList* p = node->val.head;
    int i = 0;
    while (p) {
        int j = 0;
        QTableWidgetItem* order = new QTableWidgetItem(QString::number(p->val.order));
        ui->clientsSearchResult->setItem(i, j, order);
        j++;
        QTableWidgetItem* name = new QTableWidgetItem(QString::fromStdString(p->val.name));
        ui->clientsSearchResult->setItem(i, j, name);
        j++;
        QTableWidgetItem* birthday = new QTableWidgetItem(QString::fromStdString(p->val.birthday));
        ui->clientsSearchResult->setItem(i, j, birthday);
        j++;
        QTableWidgetItem* phone = new QTableWidgetItem(QString::fromStdString(p->val.phone_number));
        ui->clientsSearchResult->setItem(i, j, phone);
        j++;
        QTableWidgetItem* id = new QTableWidgetItem(QString::fromStdString(p->val.ID));
        ui->clientsSearchResult->setItem(i, j, id);
        p = p->next;
        i++;
    }
    int comparisons_done = clientsDirectory.clientsPhoneTree.countSearchComparisons(field_to_find);
    ui->statusbar->showMessage(QString("Найдено " + QString::number(i) + " записей. Выполнено " + QString::number(comparisons_done) + " сравнений."));
}


void MainWindow::on_clientsIDSearch_clicked()
{
    if (clientsDirectory.clientsList.size() == 0) {
        ui->statusbar->showMessage(QString("Справочник пуст"), 1000);
        return;
    }
    if (ui->clientsSearchField->text() == "") {
        ui->statusbar->showMessage(QString("Поле для поиска не задано"), 1000);
        return;
    }
    if (!is_number(ui->clientsSearchField->text().toStdString())) {
        ui->statusbar->showMessage(QString("Поле задано некорректно"), 1000);
        return;
    }
    std::string field_to_find = ui->clientsSearchField->text().toStdString();
    int found_index = clientsDirectory.clientsHashTable.Search(field_to_find);
    if (found_index == -1) {
        ui->statusbar->showMessage(QString("Поле не найдено"), 2000);
        return;
    }
    ui->clientsSearchResult->clear();
    ui->clientsSearchResult->setColumnCount(5);
    ui->clientsSearchResult->setRowCount(1);
    ui->clientsSearchResult->setHorizontalHeaderLabels(QStringList() << "В массиве" << "Имя" << "Дата рождения" << "Номер телефона" << "Паспорт");
    ui->clientsSearchResult->setColumnWidth(0, 70);
    ui->clientsSearchResult->setColumnWidth(1, 250);
    ui->clientsSearchResult->setColumnWidth(2, 150);
    ui->clientsSearchResult->setColumnWidth(3, 150);
    ui->clientsSearchResult->setColumnWidth(4, 130);

    int j = 0;
    QTableWidgetItem* order = new QTableWidgetItem(QString::number(clientsDirectory.clientsHashTable.getTable()[found_index]->record.order));
    ui->clientsSearchResult->setItem(0, j, order);
    j++;
    QTableWidgetItem* name = new QTableWidgetItem(QString::fromStdString(clientsDirectory.clientsHashTable.getTable()[found_index]->record.name));
    ui->clientsSearchResult->setItem(0, j, name);
    j++;
    QTableWidgetItem* birthday = new QTableWidgetItem(QString::fromStdString(clientsDirectory.clientsHashTable.getTable()[found_index]->record.birthday));
    ui->clientsSearchResult->setItem(0, j, birthday);
    j++;
    QTableWidgetItem* phone = new QTableWidgetItem(QString::fromStdString(clientsDirectory.clientsHashTable.getTable()[found_index]->record.phone_number));
    ui->clientsSearchResult->setItem(0, j, phone);
    j++;
    QTableWidgetItem* id = new QTableWidgetItem(QString::fromStdString(clientsDirectory.clientsHashTable.getTable()[found_index]->record.ID));
    ui->clientsSearchResult->setItem(0, j, id);

    ui->statusbar->showMessage(QString("Запись найдена"), 3000);
}


void MainWindow::on_clientsAdd_clicked()
{
    if (ui->clientsAddNameEdit->text() == "" || ui->clientsAddBirthdateEdit->text() == "" || ui->clientsAddPhoneEdit->text() == "" || ui->clientsAddIDEdit->text() == "") {
        ui->statusbar->showMessage(QString("Поля не заполнены полностью"), 1000);
        return;
    }
    if (!is_number(ui->clientsAddIDEdit->text().toStdString())) {
        ui->statusbar->showMessage(QString("Паспорт задан некорректно"), 1000);
        return;
    }
    Client record_to_add({ui->clientsAddNameEdit->text().toStdString(), ui->clientsAddBirthdateEdit->text().toStdString(), ui->clientsAddPhoneEdit->text().toStdString(), ui->clientsAddIDEdit->text().toStdString()});
    int add_status = clientsDirectory.ADD(record_to_add);
    if (add_status == 1) {
        ui->statusbar->showMessage(QString("Запись c таким паспортом уже существует"), 2000);
        return;
    }

    ui->clientsTable->clear();
    ui->clientsTable->setColumnCount(4);
    ui->clientsTable->setRowCount(clientsDirectory.clientsList.size());
    ui->clientsTable->setHorizontalHeaderLabels(QStringList() << "Имя" << "Дата рождения" << "Номер телефона" << "Паспорт");
    ui->clientsTable->setColumnWidth(0, 320);
    ui->clientsTable->setColumnWidth(1, 150);
    ui->clientsTable->setColumnWidth(2, 150);
    ui->clientsTable->setColumnWidth(3, 130);

    for (int i = 0; i < clientsDirectory.clientsList.size(); i++) {
        int j = 0;
        QTableWidgetItem* name = new QTableWidgetItem(QString::fromStdString(clientsDirectory.clientsList[i].name));
        ui->clientsTable->setItem(i, j, name);
        j++;
        QTableWidgetItem* birthday = new QTableWidgetItem(QString::fromStdString(clientsDirectory.clientsList[i].birthday));
        ui->clientsTable->setItem(i, j, birthday);
        j++;
        QTableWidgetItem* phone = new QTableWidgetItem(QString::fromStdString(clientsDirectory.clientsList[i].phone_number));
        ui->clientsTable->setItem(i, j, phone);
        j++;
        QTableWidgetItem* id = new QTableWidgetItem(QString::fromStdString(clientsDirectory.clientsList[i].ID));
        ui->clientsTable->setItem(i, j, id);
    }

    ui->statusbar->showMessage(QString("Запись добавлена"), 3000);
}



void MainWindow::on_clientsDebug_clicked()
{
    for (int i = 0; i < clientsDirectory.clientsList.size(); i++) {
        std::cout << clientsDirectory.clientsList[i].name << " - Birthday: " << clientsDirectory.clientsList[i].birthday << " - Phone number: "
                  << clientsDirectory.clientsList[i].phone_number << " - ID: " << clientsDirectory.clientsList[i].ID << std::endl;
    }
    std::cout << std::endl;
    clientsDirectory.clientsHashTable.Print();
    std::cout << std::endl;
    clientsDirectory.clientsNameTree.fancyPrint();
    std::cout << std::endl;
    clientsDirectory.clientsBirthdayTree.fancyPrint();
    std::cout << std::endl;
    clientsDirectory.clientsPhoneTree.fancyPrint();
    std::cout << std::endl;

    ui->statusbar->showMessage(QString("Отладочные данные выведены в консоль"), 3000);
}


void MainWindow::on_clientsRemove_clicked()
{
    if (clientsDirectory.clientsList.size() == 0) {
        ui->statusbar->showMessage(QString("Справочник пуст"), 1000);
        return;
    }
    if (ui->clientsRemoveEdit->text() == "") {
        ui->statusbar->showMessage(QString("Введите паспорт"), 1000);
        return;
    }
    if (!is_number(ui->clientsRemoveEdit->text().toStdString())) {
        ui->statusbar->showMessage(QString("Паспорт задан некорректно"), 1000);
        return;
    }

    int del_status = clientsDirectory.clientsHashTable.Search(ui->clientsRemoveEdit->text().toStdString());
    if (del_status == -1) {
        ui->statusbar->showMessage(QString("Записи с таким паспортом нет в справочнике"), 1000);
        return;
    }

    /*
     * Место для проверки на целостность в справочнике Страховок
     */

    int record_index_to_del = clientsDirectory.clientsHashTable.getTable()[del_status]->record.order - 1;
    Client record_to_del = clientsDirectory.clientsHashTable.getTable()[del_status]->record;

    clientsDirectory.REMOVE(record_to_del, record_index_to_del);

    ui->clientsTable->clear();
    ui->clientsTable->setColumnCount(4);
    ui->clientsTable->setRowCount(clientsDirectory.clientsList.size());
    ui->clientsTable->setHorizontalHeaderLabels(QStringList() << "Имя" << "Дата рождения" << "Номер телефона" << "Паспорт");
    ui->clientsTable->setColumnWidth(0, 320);
    ui->clientsTable->setColumnWidth(1, 150);
    ui->clientsTable->setColumnWidth(2, 150);
    ui->clientsTable->setColumnWidth(3, 130);

    for (int i = 0; i < clientsDirectory.clientsList.size(); i++) {
        int j = 0;
        QTableWidgetItem* name = new QTableWidgetItem(QString::fromStdString(clientsDirectory.clientsList[i].name));
        ui->clientsTable->setItem(i, j, name);
        j++;
        QTableWidgetItem* birthday = new QTableWidgetItem(QString::fromStdString(clientsDirectory.clientsList[i].birthday));
        ui->clientsTable->setItem(i, j, birthday);
        j++;
        QTableWidgetItem* phone = new QTableWidgetItem(QString::fromStdString(clientsDirectory.clientsList[i].phone_number));
        ui->clientsTable->setItem(i, j, phone);
        j++;
        QTableWidgetItem* id = new QTableWidgetItem(QString::fromStdString(clientsDirectory.clientsList[i].ID));
        ui->clientsTable->setItem(i, j, id);
    }
    ui->statusbar->showMessage(QString("Запись удалена"), 3000);
}


void MainWindow::on_startButton_clicked()
{
    if (ui->clientsSizeEdit->text() != "") {
        if (stoi(ui->clientsSizeEdit->text().toStdString()) == 0) {
            ui->statusbar->showMessage(QString("Размер не может быть нулевым"), 2000);
            return;
        }
    }
    if (ui->agentsSizeEdit->text() != "") {
        if (stoi(ui->agentsSizeEdit->text().toStdString()) == 0) {
            ui->statusbar->showMessage(QString("Размер не может быть нулевым"), 2000);
            return;
        }
    }
    if (ui->insurancesSizeEdit->text() != "") {
        if (stoi(ui->insurancesSizeEdit->text().toStdString()) == 0) {
            ui->statusbar->showMessage(QString("Размер не может быть нулевым"), 2000);
            return;
        }
    }

    if (ui->clientsSizeEdit->text() != "") {
        clientsDirectory.clientsHashTable.reconstruct(stoi(ui->clientsSizeEdit->text().toStdString()));
    }

    ui->defaultSizeSection->setDisabled(true);
    ui->tabWidget->setDisabled(false);
    ui->fileSection->setDisabled(false);
    ui->statusbar->showMessage(QString("Справочники инициализированы"), 2000);
}

