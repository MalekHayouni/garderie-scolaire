#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "garderie.h"
#include "connexion.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Garderie *gs;

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    Connexion c;
};
#endif // MAINWINDOW_H
