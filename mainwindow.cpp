#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "directories.h"

ClientsDir clientsDirectory(10);
InsurancesDir insurancesDirectory(100);
AgentsDir agentsDirectory(100);

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
        bool load_fail_1 = 0;
        std::string agents_file_path = "../" + ui->fileForm->text().toStdString() + "/agents.txt";
        load_fail_1 = agentsDirectory.LOAD(agents_file_path);

        if (load_fail_1) {
            ui->statusbar->showMessage(QString("Такой директории не существует"), 3000);
            return;
        }
    bool load_fail_2 = 0;
    std::string ins_file_path = "../" + ui->fileForm->text().toStdString() + "/ins.txt";
    load_fail_2 = insurancesDirectory.LOAD(ins_file_path);

    if (load_fail_2) {
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

    ui->agentsTable->clear();
    ui->agentsTable->setColumnCount(4);
    ui->agentsTable->setRowCount(agentsDirectory.agents.size());
    ui->agentsTable->setHorizontalHeaderLabels(QStringList() << "ФИО" << "Номер телефона" << "Процент" << "Паспорт");
    ui->agentsTable->setColumnWidth(0, 320);
    ui->agentsTable->setColumnWidth(1, 150);
    ui->agentsTable->setColumnWidth(2, 150);
    ui->agentsTable->setColumnWidth(3, 130);

    for (int i = 0; i < agentsDirectory.agents.size(); i++)
    {
        int j = 0;
        QTableWidgetItem* fio = new QTableWidgetItem(QString::fromStdString(agentsDirectory.agents[i].fio));
        ui->agentsTable->setItem(i, j, fio);
        j++;
        QTableWidgetItem* number = new QTableWidgetItem(QString::fromStdString(agentsDirectory.agents[i].number));
        ui->agentsTable->setItem(i, j, number);
        j++;
        QTableWidgetItem* percent = new QTableWidgetItem(QString::number(agentsDirectory.agents[i].percent));
        ui->agentsTable->setItem(i, j, percent);
        j++;
        QTableWidgetItem* pass = new QTableWidgetItem(QString::fromStdString(agentsDirectory.agents[i].pass));
        ui->agentsTable->setItem(i, j, pass);
    }




    ui->insurancesTable->clear();
    ui->insurancesTable->setColumnCount(4);
    ui->insurancesTable->setRowCount(insurancesDirectory.insurancesList.size());
    ui->insurancesTable->setHorizontalHeaderLabels(QStringList() << "Название" << "пасспорт клиента" << "пасспорт агента" << "стоимость");
    ui->insurancesTable->setColumnWidth(0, 320);
    ui->insurancesTable->setColumnWidth(1, 150);
    ui->insurancesTable->setColumnWidth(2, 150);
    ui->insurancesTable->setColumnWidth(3, 130);

    for (int i = 0; i < insurancesDirectory.insurancesList.size(); i++) {
        int j = 0;
        QTableWidgetItem* strah = new QTableWidgetItem(QString::fromStdString(insurancesDirectory.insurancesList[i].strah));
        ui->insurancesTable->setItem(i, j, strah);
        j++;
        QTableWidgetItem* client = new QTableWidgetItem(QString::fromStdString(insurancesDirectory.insurancesList[i].clientpass));
        ui->insurancesTable->setItem(i, j, client);
        j++;
        QTableWidgetItem* agent= new QTableWidgetItem(QString::fromStdString(insurancesDirectory.insurancesList[i].agentpass));
        ui->insurancesTable->setItem(i, j, agent);
        j++;
        QTableWidgetItem* stoim = new QTableWidgetItem(QString::fromStdString(insurancesDirectory.insurancesList[i].stoim));
        ui->insurancesTable->setItem(i, j, stoim);
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

    std::string agents_file_path = "../" + ui->fileForm->text().toStdString() + "/agents.txt";
    save_status = agentsDirectory.SAVE(agents_file_path);
    if (save_status == 2) {
        ui->statusbar->showMessage(QString("Файл повреждён"), 3000);
        return;
    }
    if (save_status == 1) {
        ui->statusbar->showMessage(QString("Такой директории не существует"), 3000);
        return;
    }

    std::string ins_file_path = "../" + ui->fileForm->text().toStdString() + "/ins.txt";
    save_status = insurancesDirectory.SAVE(ins_file_path);
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
    key temp;
    node* cur;
    temp.clientpass = ui->clientsRemoveEdit->text().toStdString();
//    if (insurancesDirectory.insurancesClientIdTree.find(temp, insurancesDirectory.insurancesClientIdTree.root, cur) != nullptr) {
//        ui->statusbar->showMessage(QString("Удаление невозможно. Клиент использован в страховке."), 3000);
//        return;
//    }
    node* check_result = insurancesDirectory.insurancesClientIdTree.find(temp, insurancesDirectory.insurancesClientIdTree.root, cur);
    if (check_result != nullptr) {
        ui->statusbar->showMessage(QString("Удаление невозможно. Клиент использован в страховке."), 3000);
        return;
    }

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

void MainWindow::on_insurancesDebug_clicked()
{

        for (int i = 0; i < insurancesDirectory.insurancesList.size(); i++) {
            std::cout << insurancesDirectory.insurancesList[i].agentpass << " - Birthday: " << insurancesDirectory.insurancesList[i].stoim << " - Phone number: "
                      << insurancesDirectory.insurancesList[i].clientpass << " - ID: " << insurancesDirectory.insurancesList[i].id << std::endl;
        }
        std::cout << std::endl;
        insurancesDirectory.insurancesAgentIdTree.print();
        std::cout << std::endl;
        insurancesDirectory.insurancesClientIdTree.print();
        std::cout << std::endl;
        insurancesDirectory.insurancesTypeTree.print();
        std::cout << std::endl;
        insurancesDirectory.insurancesCostTree.print();
        std::cout << std::endl;
        insurancesDirectory.insurancesHashTable.print();
        std::cout<<std::endl;
        ui->statusbar->showMessage(QString("Отладочные данные выведены в консоль"), 3000);

}


void MainWindow::on_insurancesNameSearch_clicked()
{
        if (insurancesDirectory.insurancesList.size() == 0) {
            ui->statusbar->showMessage(QString("Справочник пуст"), 1000);
            return;
        }
        if (ui->insurancesSearchField->text() == "") {
            ui->statusbar->showMessage(QString("Поле для поиска не задано"), 1000);
            return;
        }
        std::string field_to_find = ui->insurancesSearchField->text().toStdString();
        key temp;
        temp.strah = field_to_find;
        node* cur;
        node* nodes = insurancesDirectory.insurancesTypeTree.find(temp,insurancesDirectory.insurancesTypeTree.root,cur);
        if (nodes == nullptr) {
            ui->statusbar->showMessage(QString("Поле не найдено"), 2000);
            return;
        }
        ui->insurancesSearchResult->clear();
        ui->insurancesSearchResult->setColumnCount(5);
        ui->insurancesSearchResult->setRowCount(nodes->data.size());
        ui->insurancesSearchResult->setHorizontalHeaderLabels(QStringList() << "стоимость" << "Страхование" << "Агенты" << "Клиенты" << "В массиве");
        ui->insurancesSearchResult->setColumnWidth(0, 70);
        ui->insurancesSearchResult->setColumnWidth(1, 250);
        ui->insurancesSearchResult->setColumnWidth(2, 150);
        ui->insurancesSearchResult->setColumnWidth(3, 150);
        ui->insurancesSearchResult->setColumnWidth(4, 130);

        nodes->data.get(0);
        int i = 0;
        while (nodes->data.get(i) != nullptr) {
            int j = 0;
            QTableWidgetItem* cost = new QTableWidgetItem(QString::fromStdString(nodes->data.get(i)->stoim));
            ui->insurancesSearchResult->setItem(i, j, cost);
            j++;
            QTableWidgetItem* type = new QTableWidgetItem(QString::fromStdString(nodes->data.get(i)->strah));
            ui->insurancesSearchResult->setItem(i, j, type);
            j++;
            QTableWidgetItem* agent = new QTableWidgetItem(QString::fromStdString(nodes->data.get(i)->agentpass));
            ui->insurancesSearchResult->setItem(i, j, agent);
            j++;
            QTableWidgetItem* client = new QTableWidgetItem(QString::fromStdString(nodes->data.get(i)->clientpass));
            ui->insurancesSearchResult->setItem(i, j, client);
            j++;
            QTableWidgetItem* id = new QTableWidgetItem(QString::number(nodes->data.get(i)->id));
            ui->insurancesSearchResult->setItem(i, j, id);
            i++;
        }

        int comparisons_done = insurancesDirectory.insurancesTypeTree.find_k(temp,insurancesDirectory.insurancesTypeTree.root);
        ui->statusbar->showMessage(QString("Найдено " + QString::number(i) + " записей. Выполнено " + QString::number(comparisons_done) + " сравнений."));
}


void MainWindow::on_insurancesClientIDSearch_clicked()
{
        if (insurancesDirectory.insurancesList.size() == 0) {
            ui->statusbar->showMessage(QString("Справочник пуст"), 1000);
            return;
        }
        if (ui->insurancesSearchField->text() == "") {
            ui->statusbar->showMessage(QString("Поле для поиска не задано"), 1000);
            return;
        }
        std::string field_to_find = ui->insurancesSearchField->text().toStdString();
        key temp;
        node* cur;
        temp.clientpass = field_to_find;
        node* nodes = insurancesDirectory.insurancesClientIdTree.find(temp,insurancesDirectory.insurancesClientIdTree.root,cur);
        if (nodes == nullptr) {
            ui->statusbar->showMessage(QString("Поле не найдено"), 2000);
            return;
        }
        ui->insurancesSearchResult->clear();
        ui->insurancesSearchResult->setColumnCount(5);
        ui->insurancesSearchResult->setRowCount(nodes->data.size());
        ui->insurancesSearchResult->setHorizontalHeaderLabels(QStringList() << "стоимость" << "Страхование" << "Агенты" << "Клиенты" << "В массиве");
        ui->insurancesSearchResult->setColumnWidth(0, 70);
        ui->insurancesSearchResult->setColumnWidth(1, 250);
        ui->insurancesSearchResult->setColumnWidth(2, 150);
        ui->insurancesSearchResult->setColumnWidth(3, 150);
        ui->insurancesSearchResult->setColumnWidth(4, 130);

        nodes->data.get(0);
        int i = 0;
        while (nodes->data.get(i) != nullptr) {
            int j = 0;
            QTableWidgetItem* cost = new QTableWidgetItem(QString::fromStdString(nodes->data.get(i)->stoim));
            ui->insurancesSearchResult->setItem(i, j, cost);
            j++;
            QTableWidgetItem* type = new QTableWidgetItem(QString::fromStdString(nodes->data.get(i)->strah));
            ui->insurancesSearchResult->setItem(i, j, type);
            j++;
            QTableWidgetItem* agent = new QTableWidgetItem(QString::fromStdString(nodes->data.get(i)->agentpass));
            ui->insurancesSearchResult->setItem(i, j, agent);
            j++;
            QTableWidgetItem* client = new QTableWidgetItem(QString::fromStdString(nodes->data.get(i)->clientpass));
            ui->insurancesSearchResult->setItem(i, j, client);
            j++;
            QTableWidgetItem* id = new QTableWidgetItem(QString::number(nodes->data.get(i)->id));
            ui->insurancesSearchResult->setItem(i, j, id);
            i++;
        }

        int comparisons_done = insurancesDirectory.insurancesClientIdTree.find_k(temp,insurancesDirectory.insurancesClientIdTree.root);
        ui->statusbar->showMessage(QString("Найдено " + QString::number(i) + " записей. Выполнено " + QString::number(comparisons_done) + " сравнений."));
}


void MainWindow::on_insurancesAgentIDSearch_clicked()
{
        if (insurancesDirectory.insurancesList.size() == 0) {
            ui->statusbar->showMessage(QString("Справочник пуст"), 1000);
            return;
        }
        if (ui->insurancesSearchField->text() == "") {
            ui->statusbar->showMessage(QString("Поле для поиска не задано"), 1000);
            return;
        }
        std::string field_to_find = ui->insurancesSearchField->text().toStdString();
        key temp;
        temp.agentpass = field_to_find;
        node* cur;
        node* nodes = insurancesDirectory.insurancesAgentIdTree.find(temp,insurancesDirectory.insurancesAgentIdTree.root,cur);
        if (nodes == nullptr) {
            ui->statusbar->showMessage(QString("Поле не найдено"), 2000);
            return;
        }
        ui->insurancesSearchResult->clear();
        ui->insurancesSearchResult->setColumnCount(5);
        ui->insurancesSearchResult->setRowCount(nodes->data.size());
        ui->insurancesSearchResult->setHorizontalHeaderLabels(QStringList() << "стоимость" << "Страхование" << "Агенты" << "Клиенты" << "В массиве");
        ui->insurancesSearchResult->setColumnWidth(0, 70);
        ui->insurancesSearchResult->setColumnWidth(1, 250);
        ui->insurancesSearchResult->setColumnWidth(2, 150);
        ui->insurancesSearchResult->setColumnWidth(3, 150);
        ui->insurancesSearchResult->setColumnWidth(4, 130);


        int i = 0;
        while (nodes->data.get(i) != nullptr) {
            int j = 0;
            QTableWidgetItem* cost = new QTableWidgetItem(QString::fromStdString(nodes->data.get(i)->stoim));
            ui->insurancesSearchResult->setItem(i, j, cost);
            j++;
            QTableWidgetItem* type = new QTableWidgetItem(QString::fromStdString(nodes->data.get(i)->strah));
            ui->insurancesSearchResult->setItem(i, j, type);
            j++;
            QTableWidgetItem* agent = new QTableWidgetItem(QString::fromStdString(nodes->data.get(i)->agentpass));
            ui->insurancesSearchResult->setItem(i, j, agent);
            j++;
            QTableWidgetItem* client = new QTableWidgetItem(QString::fromStdString(nodes->data.get(i)->clientpass));
            ui->insurancesSearchResult->setItem(i, j, client);
            j++;
            QTableWidgetItem* id = new QTableWidgetItem(QString::number(nodes->data.get(i)->id));
            ui->insurancesSearchResult->setItem(i, j, id);
            i++;
        }

        int comparisons_done = insurancesDirectory.insurancesAgentIdTree.find_k(temp,insurancesDirectory.insurancesAgentIdTree.root);
        ui->statusbar->showMessage(QString("Найдено " + QString::number(i) + " записей. Выполнено " + QString::number(comparisons_done) + " сравнений."));
}


void MainWindow::on_insurancesCostSearch_clicked()
{
        if (insurancesDirectory.insurancesList.size() == 0) {
            ui->statusbar->showMessage(QString("Справочник пуст"), 1000);
            return;
        }
        if (ui->insurancesSearchField->text() == "") {
            ui->statusbar->showMessage(QString("Поле для поиска не задано"), 1000);
            return;
        }
        std::string field_to_find = ui->insurancesSearchField->text().toStdString();
        key temp;
        temp.stoim = field_to_find;
        node* cur;
        node* nodes = insurancesDirectory.insurancesCostTree.find(temp,insurancesDirectory.insurancesCostTree.root,cur);
        if (nodes == nullptr) {
            ui->statusbar->showMessage(QString("Поле не найдено"), 2000);
            return;
        }
        ui->insurancesSearchResult->clear();
        ui->insurancesSearchResult->setColumnCount(5);
        ui->insurancesSearchResult->setRowCount(nodes->data.size());
        ui->insurancesSearchResult->setHorizontalHeaderLabels(QStringList() << "стоимость" << "Страхование" << "Агенты" << "Клиенты" << "В массиве");
        ui->insurancesSearchResult->setColumnWidth(0, 70);
        ui->insurancesSearchResult->setColumnWidth(1, 250);
        ui->insurancesSearchResult->setColumnWidth(2, 150);
        ui->insurancesSearchResult->setColumnWidth(3, 150);
        ui->insurancesSearchResult->setColumnWidth(4, 130);

        nodes->data.get(0);
        int i = 0;
        while (nodes->data.get(i) != nullptr) {
            int j = 0;
            QTableWidgetItem* cost = new QTableWidgetItem(QString::fromStdString(nodes->data.get(i)->stoim));
            ui->insurancesSearchResult->setItem(i, j, cost);
            j++;
            QTableWidgetItem* type = new QTableWidgetItem(QString::fromStdString(nodes->data.get(i)->strah));
            ui->insurancesSearchResult->setItem(i, j, type);
            j++;
            QTableWidgetItem* agent = new QTableWidgetItem(QString::fromStdString(nodes->data.get(i)->agentpass));
            ui->insurancesSearchResult->setItem(i, j, agent);
            j++;
            QTableWidgetItem* client = new QTableWidgetItem(QString::fromStdString(nodes->data.get(i)->clientpass));
            ui->insurancesSearchResult->setItem(i, j, client);
            j++;
            QTableWidgetItem* id = new QTableWidgetItem(QString::number(nodes->data.get(i)->id));
            ui->insurancesSearchResult->setItem(i, j, id);
            i++;
        }

        int comparisons_done = insurancesDirectory.insurancesCostTree.find_k(temp,insurancesDirectory.insurancesCostTree.root);
        ui->statusbar->showMessage(QString("Найдено " + QString::number(i) + " записей. Выполнено " + QString::number(comparisons_done) + " сравнений."));
}


void MainWindow::on_insurancesAdd_clicked()
{
        if (ui->insurancesAddNameEdit->text() == "" || ui->insurancesAddAgentIdEdit->text() == "" || ui->insurancesAddClientIdEdit->text() == "" || ui->insurancesAddCostEdit->text() == "") {
            ui->statusbar->showMessage(QString("Поля не заполнены полностью"), 1000);
            return;
        }
        if (!is_number(ui->insurancesAddAgentIdEdit->text().toStdString())) {
            ui->statusbar->showMessage(QString("Паспорт агента задан некорректно"), 1000);
            return;
        }
        if (!is_number(ui->insurancesAddClientIdEdit->text().toStdString())) {
            ui->statusbar->showMessage(QString("Паспорт клиента задан некорректно"), 1000);
            return;
        }
        if (!is_number(ui->insurancesAddCostEdit->text().toStdString())) {
            ui->statusbar->showMessage(QString("Стоимость задана некорректно"), 1000);
            return;
        }
        key record_to_add;
        record_to_add.strah=ui->insurancesAddNameEdit->text().toStdString(), record_to_add.agentpass =ui->insurancesAddAgentIdEdit->text().toStdString(), record_to_add.clientpass =ui->insurancesAddClientIdEdit->text().toStdString(), record_to_add.stoim = ui->insurancesAddCostEdit->text().toStdString();

        if (clientsDirectory.clientsHashTable.Search(record_to_add.clientpass) == -1 || agentsDirectory.agentsHashTable.find(record_to_add.agentpass) == nullptr) {
            ui->statusbar->showMessage(QString("Такого клиента или агента не существует"), 1000);
            return;
        }


        insurancesDirectory.ADD(record_to_add);

        ui->insurancesTable->clear();
        ui->insurancesTable->setColumnCount(4);
        ui->insurancesTable->setRowCount(insurancesDirectory.insurancesList.size());
        ui->insurancesTable->setHorizontalHeaderLabels(QStringList() << "Название" << "Агенты" << "Клиенты" << "Стоимость");
        ui->insurancesTable->setColumnWidth(0, 320);
        ui->insurancesTable->setColumnWidth(1, 150);
        ui->insurancesTable->setColumnWidth(2, 150);
        ui->insurancesTable->setColumnWidth(3, 130);

        for (int i = 0; i < insurancesDirectory.insurancesList.size(); i++) {
            int j = 0;
            QTableWidgetItem* name = new QTableWidgetItem(QString::fromStdString(insurancesDirectory.insurancesList[i].strah));
            ui->insurancesTable->setItem(i, j, name);
            j++;
            QTableWidgetItem* agent = new QTableWidgetItem(QString::fromStdString(insurancesDirectory.insurancesList[i].agentpass));
            ui->insurancesTable->setItem(i, j, agent);
            j++;
            QTableWidgetItem* client = new QTableWidgetItem(QString::fromStdString(insurancesDirectory.insurancesList[i].clientpass));
            ui->insurancesTable->setItem(i, j, client);
            j++;
            QTableWidgetItem* stoim = new QTableWidgetItem(QString::fromStdString(insurancesDirectory.insurancesList[i].stoim));
            ui->insurancesTable->setItem(i, j, stoim);
        }

        ui->statusbar->showMessage(QString("Поле добавлено"), 3000);
}


void MainWindow::on_insurancesRemove_clicked()
{
        if (insurancesDirectory.insurancesList.size() == 0) {
            ui->statusbar->showMessage(QString("Справочник пуст"), 1000);
            return;
        }
        if (ui->insurancesRemoveNameEdit->text() == "") {
            ui->statusbar->showMessage(QString("введите название"), 1000);
            return;
        }
        if (ui->insurancesRemoveAgentIdEdit->text() == "") {
            ui->statusbar->showMessage(QString("введите паспорт агента"), 1000);
            return;
        }
        if (!is_number(ui->insurancesRemoveAgentIdEdit->text().toStdString())) {
            ui->statusbar->showMessage(QString("некорректный паспорт агента"), 1000);
            return;
        }
        if (ui->insurancesRemoveClientIdEdit->text() == "") {
            ui->statusbar->showMessage(QString("введите паспорт клиента"), 1000);
            return;
        }
        if (!is_number(ui->insurancesRemoveClientIdEdit->text().toStdString())) {
            ui->statusbar->showMessage(QString("Название паспорта некорректно"), 1000);
            return;
        }
        Ins temp;
        temp.val.agentpass = ui->insurancesRemoveAgentIdEdit->text().toStdString(),temp.val.clientpass=ui->insurancesRemoveClientIdEdit->text().toStdString(),temp.val.strah=ui->insurancesRemoveNameEdit->text().toStdString();

        key del_status = insurancesDirectory.insurancesHashTable.find(temp.val.agentpass, temp.val.clientpass, temp.val.strah);
        if (del_status.id == -1) {
            ui->statusbar->showMessage(QString("Записи с такими полями нет в справочнике"), 1000);
            return;
        }

        /*
         * Место для проверки на целостность в справочнике Страховок
         */



        insurancesDirectory.REMOVE(del_status);

        ui->insurancesTable->clear();
        ui->insurancesTable->setColumnCount(4);
        ui->insurancesTable->setRowCount(insurancesDirectory.insurancesList.size());
        ui->insurancesTable->setHorizontalHeaderLabels(QStringList() << "Название" << "Клиенты" << "Агенты" << "Стоимость");
        ui->insurancesTable->setColumnWidth(0, 320);
        ui->insurancesTable->setColumnWidth(1, 150);
        ui->insurancesTable->setColumnWidth(2, 150);
        ui->insurancesTable->setColumnWidth(3, 130);

        for (int i = 0; i < insurancesDirectory.insurancesList.size(); i++) {
            int j = 0;
            QTableWidgetItem* name = new QTableWidgetItem(QString::fromStdString(insurancesDirectory.insurancesList[i].strah));
            ui->insurancesTable->setItem(i, j, name);
            j++;
            QTableWidgetItem* client = new QTableWidgetItem(QString::fromStdString(insurancesDirectory.insurancesList[i].clientpass));
            ui->insurancesTable->setItem(i, j, client);
            j++;
            QTableWidgetItem* agent = new QTableWidgetItem(QString::fromStdString(insurancesDirectory.insurancesList[i].agentpass));
            ui->insurancesTable->setItem(i, j, agent);
            j++;
            QTableWidgetItem* stoim = new QTableWidgetItem(QString::fromStdString(insurancesDirectory.insurancesList[i].stoim));
            ui->insurancesTable->setItem(i, j, stoim);
        }
        ui->statusbar->showMessage(QString("Запись удалена"), 3000);
}


void MainWindow::on_insurancesUniqueSearch_clicked()
{
        if (insurancesDirectory.insurancesList.size() == 0) {
            ui->statusbar->showMessage(QString("Справочник пуст"), 1000);
            return;
        }
        if (ui->insurancesRemoveNameEdit->text() == "") {
            ui->statusbar->showMessage(QString("введите название"), 1000);
            return;
        }
        if (ui->insurancesRemoveAgentIdEdit->text() == "") {
            ui->statusbar->showMessage(QString("введите паспорт агента"), 1000);
            return;
        }
        if (!is_number(ui->insurancesRemoveAgentIdEdit->text().toStdString())) {
            ui->statusbar->showMessage(QString("некорректный паспорт агента"), 1000);
            return;
        }
        if (ui->insurancesRemoveClientIdEdit->text() == "") {
            ui->statusbar->showMessage(QString("введите паспорт клиента"), 1000);
            return;
        }
        if (!is_number(ui->insurancesRemoveClientIdEdit->text().toStdString())) {
            ui->statusbar->showMessage(QString("Название паспорта некорректно"), 1000);
            return;
        }
        Ins temp;
        temp.val.agentpass = ui->insurancesRemoveAgentIdEdit->text().toStdString(),temp.val.clientpass=ui->insurancesRemoveClientIdEdit->text().toStdString(),temp.val.strah=ui->insurancesRemoveNameEdit->text().toStdString();

        key del_status = insurancesDirectory.insurancesHashTable.find(temp.val.agentpass, temp.val.clientpass, temp.val.strah);
        if (del_status.id == -1) {
            ui->statusbar->showMessage(QString("Записи с такими полями нет в справочнике"), 1000);
            return;
        }
        ui->insurancesSearchResult->clear();
        ui->insurancesSearchResult->setColumnCount(5);
        ui->insurancesSearchResult->setRowCount(1);
        ui->insurancesSearchResult->setHorizontalHeaderLabels(QStringList() << "стоимость" << "Страхование" << "Агенты" << "Клиенты" << "В массиве");
        ui->insurancesSearchResult->setColumnWidth(0, 70);
        ui->insurancesSearchResult->setColumnWidth(1, 250);
        ui->insurancesSearchResult->setColumnWidth(2, 150);
        ui->insurancesSearchResult->setColumnWidth(3, 150);
        ui->insurancesSearchResult->setColumnWidth(4, 130);
        int i = 0;

            int j = 0;
        QTableWidgetItem* cost = new QTableWidgetItem(QString::fromStdString(del_status.stoim));
            ui->insurancesSearchResult->setItem(i, j, cost);
            j++;
            QTableWidgetItem* type = new QTableWidgetItem(QString::fromStdString(del_status.strah));
            ui->insurancesSearchResult->setItem(i, j, type);
            j++;
            QTableWidgetItem* agent = new QTableWidgetItem(QString::fromStdString(del_status.agentpass));
            ui->insurancesSearchResult->setItem(i, j, agent);
            j++;
            QTableWidgetItem* client = new QTableWidgetItem(QString::fromStdString(del_status.clientpass));
            ui->insurancesSearchResult->setItem(i, j, client);
            j++;
            QTableWidgetItem* id = new QTableWidgetItem(QString::number(del_status.id));
            ui->insurancesSearchResult->setItem(i, j, id);
}
void MainWindow::on_agentsAdd_clicked()
{
            if (ui->agentsAddNameEdit->text() == "" || ui->agentsAddPhoneEdit->text() == "" || ui->agentsAddFeeEdit->text() == "" || ui->agentsAddIdEdit->text() == "") {
            ui->statusbar->showMessage(QString("Поля не заполнены полностью"), 1000);
            return;
            }

            if (is_number(ui->agentsAddNameEdit->text().toStdString()))
            {
            ui->statusbar->showMessage(QString("ФИО задано некорректно"), 1000);
            return;
            }
            if (!is_number(ui->agentsAddPhoneEdit->text().toStdString()))
            {
            ui->statusbar->showMessage(QString("Номер телефона задан некорректно"), 1000);
            return;
            }
            if (!is_number(ui->agentsAddFeeEdit->text().toStdString()))
            {
            ui->statusbar->showMessage(QString("Процент задан некорректно"), 1000);
            return;
            }
            if (!is_number(ui->agentsAddIdEdit->text().toStdString()))
            {
            ui->statusbar->showMessage(QString("Паспорт задан некорректно"), 1000);
            return;
            }

            AgentHTNode* del_status = new AgentHTNode();
            del_status = agentsDirectory.agentsHashTable.find(ui->agentsAddIdEdit->text().toStdString());
            if (del_status != nullptr) {
            ui->statusbar->showMessage(QString("Записи с таким паспортом уже существует"), 1000);
            return;
            }

            Agent record_to_add;
            record_to_add.fio = ui->agentsAddNameEdit->text().toStdString(), record_to_add.number = ui->agentsAddPhoneEdit->text().toStdString(), record_to_add.percent = ui->agentsAddFeeEdit->text().toInt(), record_to_add.pass = ui->agentsAddIdEdit->text().toStdString();
            agentsDirectory.ADD(record_to_add);

            ui->agentsTable->clear();
            ui->agentsTable->setColumnCount(4);
            ui->agentsTable->setRowCount(agentsDirectory.agents.size());
            ui->agentsTable->setHorizontalHeaderLabels(QStringList() << "ФИО" << "Номер телефона" << "Процент" << "Паспорт");
            ui->agentsTable->setColumnWidth(0, 320);
            ui->agentsTable->setColumnWidth(1, 150);
            ui->agentsTable->setColumnWidth(2, 150);
            ui->agentsTable->setColumnWidth(3, 130);

            for (int i = 0; i < agentsDirectory.agents.size(); i++)
            {
            int j = 0;
            QTableWidgetItem* fio = new QTableWidgetItem(QString::fromStdString(agentsDirectory.agents[i].fio));
            ui->agentsTable->setItem(i, j, fio);
            j++;
            QTableWidgetItem* number = new QTableWidgetItem(QString::fromStdString(agentsDirectory.agents[i].number));
            ui->agentsTable->setItem(i, j, number);
            j++;
            QTableWidgetItem* percent = new QTableWidgetItem(QString::number(agentsDirectory.agents[i].percent));
            ui->agentsTable->setItem(i, j, percent);
            j++;
            QTableWidgetItem* pass = new QTableWidgetItem(QString::fromStdString(agentsDirectory.agents[i].pass));
            ui->agentsTable->setItem(i, j, pass);
            }

            ui->statusbar->showMessage(QString("Поле добавлено"), 3000);
}

void MainWindow::on_agentsRemove_clicked()
{
            if (agentsDirectory.agents.size() == 0) {
            ui->statusbar->showMessage(QString("Справочник пуст"), 1000);
            return;
            }

            if (ui->agentsRemoveEdit->text() == "") {
            ui->statusbar->showMessage(QString("Введите паспорт"), 1000);
            return;
            }

            if (!is_number(ui->agentsRemoveEdit->text().toStdString()))
            {
            ui->statusbar->showMessage(QString("Паспорт задан некорректно"), 1000);
            return;
            }

            //PROVEROCHKA
            key temp;
            node* cur;
            temp.agentpass = ui->agentsRemoveEdit->text().toStdString();
            node* check_result = insurancesDirectory.insurancesAgentIdTree.find(temp, insurancesDirectory.insurancesAgentIdTree.root, cur);
            if (check_result != nullptr) {
            ui->statusbar->showMessage(QString("Удаление невозможно. Агент использован в страховке."), 3000);
            return;
            }
            //PROVEROCHKA

            AgentHTNode* del_status = new AgentHTNode();
            del_status = agentsDirectory.agentsHashTable.find(ui->agentsRemoveEdit->text().toStdString());
            if (del_status == nullptr) {
            ui->statusbar->showMessage(QString("Записи с таким паспортом нет в справочнике"), 1000);
            return;
            }
            Agent* p = new Agent();
            p->fio = del_status->value.fio;
            p->number = del_status->value.number;
            p->percent = del_status->value.percent;
            p->pass = del_status->value.pass;

            agentsDirectory.REMOVE(*p);

            ui->agentsTable->clear();
            ui->agentsTable->setColumnCount(4);
            ui->agentsTable->setRowCount(agentsDirectory.agents.size());
            ui->agentsTable->setHorizontalHeaderLabels(QStringList() << "ФИО" << "Номер телефона" << "Процент" << "Паспорт");
            ui->agentsTable->setColumnWidth(0, 320);
            ui->agentsTable->setColumnWidth(1, 150);
            ui->agentsTable->setColumnWidth(2, 150);
            ui->agentsTable->setColumnWidth(3, 130);

            for (int i = 0; i < agentsDirectory.agents.size(); i++)
            {
            int j = 0;
            QTableWidgetItem* fio = new QTableWidgetItem(QString::fromStdString(agentsDirectory.agents[i].fio));
            ui->agentsTable->setItem(i, j, fio);
            j++;
            QTableWidgetItem* number = new QTableWidgetItem(QString::fromStdString(agentsDirectory.agents[i].number));
            ui->agentsTable->setItem(i, j, number);
            j++;
            QTableWidgetItem* percent = new QTableWidgetItem(QString::number(agentsDirectory.agents[i].percent));
            ui->agentsTable->setItem(i, j, percent);
            j++;
            QTableWidgetItem* pass = new QTableWidgetItem(QString::fromStdString(agentsDirectory.agents[i].pass));
            ui->agentsTable->setItem(i, j, pass);
            }

            ui->statusbar->showMessage(QString("Запись удалена"), 3000);
}

void MainWindow::on_agentsIDSearch_clicked()
{
            if (agentsDirectory.agents.size() == 0) {
            ui->statusbar->showMessage(QString("Справочник пуст"), 1000);
            return;
            }
            if (ui->agentsSearchField->text() == "") {
            ui->statusbar->showMessage(QString("Введите значение"), 1000);
            return;
            }
            if (!is_number(ui->agentsSearchField->text().toStdString()))
            {
            ui->statusbar->showMessage(QString("Паспорт задан некорректно"), 1000);
            return;
            }
            AgentHTNode* del_status = new AgentHTNode();
            del_status = agentsDirectory.agentsHashTable.find(ui->agentsSearchField->text().toStdString());
            if (del_status == nullptr) {
            ui->statusbar->showMessage(QString("Запись не найдена"), 1000);
            return;
            }
            ui->agentsSearchResult->clear();
            ui->agentsSearchResult->setColumnCount(5);
            ui->agentsSearchResult->setRowCount(1);
            ui->agentsSearchResult->setHorizontalHeaderLabels(QStringList() << "ФИО" << "Номер телефона" << "Процент" << "Паспорт" << "В массиве");
            ui->agentsSearchResult->setColumnWidth(0, 70);
            ui->agentsSearchResult->setColumnWidth(1, 250);
            ui->agentsSearchResult->setColumnWidth(2, 150);
            ui->agentsSearchResult->setColumnWidth(3, 150);
            ui->agentsSearchResult->setColumnWidth(4, 130);
            int i = 0;

            int j = 0;
            QTableWidgetItem* fio = new QTableWidgetItem(QString::fromStdString(del_status->value.fio));
            ui->agentsSearchResult->setItem(i, j, fio);
            j++;
            QTableWidgetItem* number = new QTableWidgetItem(QString::fromStdString(del_status->value.number));
            ui->agentsSearchResult->setItem(i, j, number);
            j++;
            QTableWidgetItem* percent = new QTableWidgetItem(QString::number(del_status->value.percent));
            ui->agentsSearchResult->setItem(i, j, percent);
            j++;
            QTableWidgetItem* pass = new QTableWidgetItem(QString::fromStdString(del_status->value.pass));
            ui->agentsSearchResult->setItem(i, j, pass);
            j++;
            QTableWidgetItem* id = new QTableWidgetItem(QString::number(del_status->id));
            ui->agentsSearchResult->setItem(i, j, id);

            ui->statusbar->showMessage(QString("Запись найдена"), 3000);
}

void MainWindow::on_agentsNameSearch_clicked()
{
            if (agentsDirectory.agents.size() == 0) {
            ui->statusbar->showMessage(QString("Справочник пуст"), 1000);
            return;
            }
            if (ui->agentsSearchField->text() == "") {
            ui->statusbar->showMessage(QString("Введите значение"), 1000);
            return;
            }
            if (is_number(ui->agentsSearchField->text().toStdString()))
            {
            ui->statusbar->showMessage(QString("ФИО задано некорректно"), 1000);
            return;
            }
            std::string field_to_find = ui->agentsSearchField->text().toStdString();
            AgentTreeNode* nodes = agentsDirectory.agentFIOTree.find(field_to_find, "_", 0, "_", agentsDirectory.agentFIOTree.root);
            if (nodes == nullptr) {
            ui->statusbar->showMessage(QString("Запись не найдена"), 2000);
            return;
            }

            int count = 1;
            AgentListNode* pp = nodes->clones.first;
            while (pp) {
            count++;
            pp = pp->next;
            }

            ui->agentsSearchResult->clear();
            ui->agentsSearchResult->setColumnCount(5);
            ui->agentsSearchResult->setRowCount(count);
            ui->agentsSearchResult->setHorizontalHeaderLabels(QStringList() << "ФИО" << "Номер телефона" << "Процент" << "Паспорт" << "В массиве");
            ui->agentsSearchResult->setColumnWidth(0, 70);
            ui->agentsSearchResult->setColumnWidth(1, 250);
            ui->agentsSearchResult->setColumnWidth(2, 150);
            ui->agentsSearchResult->setColumnWidth(3, 150);
            ui->agentsSearchResult->setColumnWidth(4, 130);


            QTableWidgetItem* fio = new QTableWidgetItem(QString::fromStdString(agentsDirectory.agents[nodes->id].fio));
            ui->agentsSearchResult->setItem(0, 0, fio);

            QTableWidgetItem* number = new QTableWidgetItem(QString::fromStdString(agentsDirectory.agents[nodes->id].number));
            ui->agentsSearchResult->setItem(0, 1, number);

            QTableWidgetItem* percent = new QTableWidgetItem(QString::number(agentsDirectory.agents[nodes->id].percent));
            ui->agentsSearchResult->setItem(0, 2, percent);

            QTableWidgetItem* pass = new QTableWidgetItem(QString::fromStdString(agentsDirectory.agents[nodes->id].pass));
            ui->agentsSearchResult->setItem(0, 3, pass);

            QTableWidgetItem* id = new QTableWidgetItem(QString::number(nodes->id));
            ui->agentsSearchResult->setItem(0, 4, id);

            AgentListNode* p = nodes->clones.first;
            int i = 1;
            while (p) {
            int j = 0;
            QTableWidgetItem* fio = new QTableWidgetItem(QString::fromStdString(agentsDirectory.agents[p->id].fio));
            ui->agentsSearchResult->setItem(i, j, fio);
            j++;
            QTableWidgetItem* number = new QTableWidgetItem(QString::fromStdString(agentsDirectory.agents[p->id].number));
            ui->agentsSearchResult->setItem(i, j, number);
            j++;
            QTableWidgetItem* percent = new QTableWidgetItem(QString::number(agentsDirectory.agents[p->id].percent));
            ui->agentsSearchResult->setItem(i, j, percent);
            j++;
            QTableWidgetItem* pass = new QTableWidgetItem(QString::fromStdString(agentsDirectory.agents[p->id].pass));
            ui->agentsSearchResult->setItem(i, j, pass);
            j++;
            QTableWidgetItem* id = new QTableWidgetItem(QString::number(p->id));
            ui->agentsSearchResult->setItem(i, j, id);
            p = p->next;
            i++;
            }
            ui->statusbar->showMessage(QString("Записи найдены"), 3000);
}

void MainWindow::on_agentsNumSearch_clicked()
{
            if (agentsDirectory.agents.size() == 0) {
            ui->statusbar->showMessage(QString("Справочник пуст"), 1000);
            return;
            }
            if (ui->agentsSearchField->text() == "") {
            ui->statusbar->showMessage(QString("Введите значение"), 1000);
            return;
            }
            if (!is_number(ui->agentsSearchField->text().toStdString()))
            {
            ui->statusbar->showMessage(QString("Номер телефона задан некорректно"), 1000);
            return;
            }
            std::string field_to_find = ui->agentsSearchField->text().toStdString();
            AgentTreeNode* nodes = agentsDirectory.agentNumTree.find("_", field_to_find, 0, "_", agentsDirectory.agentNumTree.root);
            if (nodes == nullptr) {
            ui->statusbar->showMessage(QString("Запись не найдена"), 2000);
            return;
            }

            int count = 1;
            AgentListNode* pp = nodes->clones.first;
            while (pp) {
            count++;
            pp = pp->next;
            }

            ui->agentsSearchResult->clear();
            ui->agentsSearchResult->setColumnCount(5);
            ui->agentsSearchResult->setRowCount(count);
            ui->agentsSearchResult->setHorizontalHeaderLabels(QStringList() << "ФИО" << "Номер телефона" << "Процент" << "Паспорт" << "В массиве");
            ui->agentsSearchResult->setColumnWidth(0, 70);
            ui->agentsSearchResult->setColumnWidth(1, 250);
            ui->agentsSearchResult->setColumnWidth(2, 150);
            ui->agentsSearchResult->setColumnWidth(3, 150);
            ui->agentsSearchResult->setColumnWidth(4, 130);


            QTableWidgetItem* fio = new QTableWidgetItem(QString::fromStdString(agentsDirectory.agents[nodes->id].fio));
            ui->agentsSearchResult->setItem(0, 0, fio);

            QTableWidgetItem* number = new QTableWidgetItem(QString::fromStdString(agentsDirectory.agents[nodes->id].number));
            ui->agentsSearchResult->setItem(0, 1, number);

            QTableWidgetItem* percent = new QTableWidgetItem(QString::number(agentsDirectory.agents[nodes->id].percent));
            ui->agentsSearchResult->setItem(0, 2, percent);

            QTableWidgetItem* pass = new QTableWidgetItem(QString::fromStdString(agentsDirectory.agents[nodes->id].pass));
            ui->agentsSearchResult->setItem(0, 3, pass);

            QTableWidgetItem* id = new QTableWidgetItem(QString::number(nodes->id));
            ui->agentsSearchResult->setItem(0, 4, id);

            AgentListNode* p = nodes->clones.first;
            int i = 1;
            while (p) {
            int j = 0;
            QTableWidgetItem* fio = new QTableWidgetItem(QString::fromStdString(agentsDirectory.agents[p->id].fio));
            ui->agentsSearchResult->setItem(i, j, fio);
            j++;
            QTableWidgetItem* number = new QTableWidgetItem(QString::fromStdString(agentsDirectory.agents[p->id].number));
            ui->agentsSearchResult->setItem(i, j, number);
            j++;
            QTableWidgetItem* percent = new QTableWidgetItem(QString::number(agentsDirectory.agents[p->id].percent));
            ui->agentsSearchResult->setItem(i, j, percent);
            j++;
            QTableWidgetItem* pass = new QTableWidgetItem(QString::fromStdString(agentsDirectory.agents[p->id].pass));
            ui->agentsSearchResult->setItem(i, j, pass);
            j++;
            QTableWidgetItem* id = new QTableWidgetItem(QString::number(p->id));
            ui->agentsSearchResult->setItem(i, j, id);
            p = p->next;
            i++;
            }
            ui->statusbar->showMessage(QString("Записи найдены"), 3000);
}

void MainWindow::on_agentsFeeSearch_clicked()
{
            if (agentsDirectory.agents.size() == 0) {
            ui->statusbar->showMessage(QString("Справочник пуст"), 1000);
            return;
            }
            if (ui->agentsSearchField->text() == "") {
            ui->statusbar->showMessage(QString("Введите значение"), 1000);
            return;
            }
            if (!is_number(ui->agentsSearchField->text().toStdString()))
            {
            ui->statusbar->showMessage(QString("Процент задан некорректно"), 1000);
            return;
            }
            int field_to_find = ui->agentsSearchField->text().toInt();
            AgentTreeNode* nodes = agentsDirectory.agentPerTree.find("_", "_", field_to_find, "_", agentsDirectory.agentPerTree.root);
            if (nodes == nullptr) {
            ui->statusbar->showMessage(QString("Запись не найдена"), 2000);
            return;
            }

            int count = 1;
            AgentListNode* pp = nodes->clones.first;
            while (pp) {
            count++;
            pp = pp->next;
            }

            ui->agentsSearchResult->clear();
            ui->agentsSearchResult->setColumnCount(5);
            ui->agentsSearchResult->setRowCount(count);
            ui->agentsSearchResult->setHorizontalHeaderLabels(QStringList() << "ФИО" << "Номер телефона" << "Процент" << "Паспорт" << "В массиве");
            ui->agentsSearchResult->setColumnWidth(0, 70);
            ui->agentsSearchResult->setColumnWidth(1, 250);
            ui->agentsSearchResult->setColumnWidth(2, 150);
            ui->agentsSearchResult->setColumnWidth(3, 150);
            ui->agentsSearchResult->setColumnWidth(4, 130);


            QTableWidgetItem* fio = new QTableWidgetItem(QString::fromStdString(agentsDirectory.agents[nodes->id].fio));
            ui->agentsSearchResult->setItem(0, 0, fio);

            QTableWidgetItem* number = new QTableWidgetItem(QString::fromStdString(agentsDirectory.agents[nodes->id].number));
            ui->agentsSearchResult->setItem(0, 1, number);

            QTableWidgetItem* percent = new QTableWidgetItem(QString::number(agentsDirectory.agents[nodes->id].percent));
            ui->agentsSearchResult->setItem(0, 2, percent);

            QTableWidgetItem* pass = new QTableWidgetItem(QString::fromStdString(agentsDirectory.agents[nodes->id].pass));
            ui->agentsSearchResult->setItem(0, 3, pass);

            QTableWidgetItem* id = new QTableWidgetItem(QString::number(nodes->id));
            ui->agentsSearchResult->setItem(0, 4, id);

            AgentListNode* p = nodes->clones.first;
            int i = 1;
            while (p) {
            int j = 0;
            QTableWidgetItem* fio = new QTableWidgetItem(QString::fromStdString(agentsDirectory.agents[p->id].fio));
            ui->agentsSearchResult->setItem(i, j, fio);
            j++;
            QTableWidgetItem* number = new QTableWidgetItem(QString::fromStdString(agentsDirectory.agents[p->id].number));
            ui->agentsSearchResult->setItem(i, j, number);
            j++;
            QTableWidgetItem* percent = new QTableWidgetItem(QString::number(agentsDirectory.agents[p->id].percent));
            ui->agentsSearchResult->setItem(i, j, percent);
            j++;
            QTableWidgetItem* pass = new QTableWidgetItem(QString::fromStdString(agentsDirectory.agents[p->id].pass));
            ui->agentsSearchResult->setItem(i, j, pass);
            j++;
            QTableWidgetItem* id = new QTableWidgetItem(QString::number(p->id));
            ui->agentsSearchResult->setItem(i, j, id);
            p = p->next;
            i++;
            }
            ui->statusbar->showMessage(QString("Записи найдены"), 3000);
}

void MainWindow::on_agentsDebug_clicked()
{
            for (int i = 0; i < agentsDirectory.agents.size(); i++) {
            std::cout << agentsDirectory.agents[i].fio << " - Birthday: " << agentsDirectory.agents[i].number << " - Phone number: "
                      << agentsDirectory.agents[i].percent << " - ID: " << agentsDirectory.agents[i].pass << std::endl;
            }
            std::cout << std::endl;
            agentsDirectory.agentsHashTable.print();
            std::cout << std::endl;
            agentsDirectory.agentFIOTree.print(agentsDirectory.agentFIOTree.root, 1);
            std::cout << std::endl;
            agentsDirectory.agentNumTree.print(agentsDirectory.agentNumTree.root, 1);
            std::cout << std::endl;
            agentsDirectory.agentPerTree.print(agentsDirectory.agentPerTree.root, 1);
            std::cout << std::endl;

            ui->statusbar->showMessage(QString("Отладочные данные выведены в консоль"), 3000);
}
