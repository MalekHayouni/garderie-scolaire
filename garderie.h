#ifndef GARDERIE_H
#define GARDERIE_H

#include <QMainWindow>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSortFilterProxyModel>
#include <QTextTableFormat>
#include <QStandardItemModel>
#include <QDialog>
#include <QDesktopWidget>
#include <QTextStream>
#include <QDataStream>
#include <QTextDocument>
#include <QFileDialog>
#include <QSettings>
#include <QFile>
#include <QDataStream>


#include "activite.h"


namespace Ui {
class Garderie;
}

class Garderie : public QMainWindow
{
    Q_OBJECT

public:
    explicit Garderie(QWidget *parent = nullptr);
    ~Garderie();

    void show_tables();
    void sendMail(QString,QString);

 /*************** activité *********************/

    QString get_id_activite() const;
    QString get_nom_activite() const;
    QString get_description_activite() const;
    QString get_etablissement_activite() const;
    int get_duree_activite() const;

    void fill_form_activite(QString);
    void clear_form_activite();

    activite tmp_activite;
    QSortFilterProxyModel *proxy_activite;



private slots:

/*************** activité *********************/
    void on_ajouter_activite_clicked();
    void on_modifier_activite_clicked();
    void on_supprimer_activite_clicked();
    void show_table_activite();

    void on_stat_activite_clicked();

    void on_tableau_activite_clicked(const QModelIndex &index);

    void on_recherche_activite_textChanged(const QString &arg1);

    void on_tableau_activite_doubleClicked(const QModelIndex &index);

    void on_sort_combo_activite_currentIndexChanged(int index);


private:
    Ui::Garderie *ui;
    QString selected_activite="";
    QString mail_pass="!211JMT7298!";
};

#endif // GARDERIE_H
