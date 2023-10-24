#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_loadButton_clicked();

    void on_saveButton_clicked();

    void on_clientsNameSearch_clicked();

    void on_clientsBirthdaySearch_clicked();

    void on_clientsNumSearch_clicked();

    void on_clientsIDSearch_clicked();

    void on_clientsAdd_clicked();

    void on_clientsDebug_clicked();

    void on_clientsRemove_clicked();

    void on_insurancesDebug_clicked();

    void on_insurancesNameSearch_clicked();

    void on_insurancesClientIDSearch_clicked();

    void on_insurancesAgentIDSearch_clicked();

    void on_insurancesCostSearch_clicked();

    void on_insurancesAdd_clicked();

    void on_insurancesRemove_clicked();

    void on_insurancesUniqueSearch_clicked();

    void on_agentsAdd_clicked();

    void on_agentsRemove_clicked();

    void on_agentsIDSearch_clicked();

    void on_agentsNameSearch_clicked();

    void on_agentsNumSearch_clicked();

    void on_agentsFeeSearch_clicked();

    void on_agentsDebug_clicked();

    void on_startButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
