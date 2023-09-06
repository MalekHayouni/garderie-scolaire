#ifndef STAT_DUREE_H
#define STAT_DUREE_H

#include <QDialog>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include <QtCharts/QChartView>
#include <QtCharts/QLegend>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class stat_duree;
}

class stat_duree : public QDialog
{
    Q_OBJECT

public:
    explicit stat_duree(QWidget *parent = nullptr);
    ~stat_duree();

    QChartView *chartView ;
    void choix_pie();

private:
    Ui::stat_duree *ui;
};

#endif // STAT_DUREE_H
