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

//    clientsDirectory.clientsList.print();
    clientsDirectory.clientsHashTable.Print();
    clientsDirectory.clientsNameTree.fancyPrint();
    std::cout << std::endl;
    clientsDirectory.clientsBirthdayTree.fancyPrint();
    std::cout << std::endl;
    clientsDirectory.clientsPhoneTree.fancyPrint();
    std::cout << std::endl;


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
    std::cout << clientsDirectory.SAVE(clients_file_path) << std::endl;

    ui->statusbar->showMessage(QString("Справочники сохранены"), 3000);
}


void MainWindow::on_clientsNameSearch_clicked()
{
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

    ui->statusbar->showMessage(QString("Запись найдена"));
}

