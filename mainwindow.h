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

    void on_startButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
