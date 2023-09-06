#include "stat_duree.h"
#include "ui_stat_duree.h"

stat_duree::stat_duree(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::stat_duree)
{
    ui->setupUi(this);
}

stat_duree::~stat_duree()
{
    delete ui;
}

//pie chart
    void stat_duree::choix_pie()
    {
    QSqlQuery q1,q2,q3,q4;
    qreal tot=0,c1=0,c2=0,c3=0;

    q1.prepare("SELECT * FROM activite");
    q1.exec();

    q2.prepare("SELECT * FROM activite WHERE duree < 2 ");
    q2.exec();

    q3.prepare("SELECT * FROM activite WHERE duree >= 2 and duree <= 4");
    q3.exec();

    q4.prepare("SELECT * FROM activite WHERE duree > 4");
    q4.exec();

    while (q1.next()){tot++;}
    while (q2.next()){c1++;}
    while (q3.next()){c2++;}
    while (q4.next()){c3++;}

    c1=c1/tot;
    c2=c2/tot;
    c3=c3/tot;

    // Define slices and percentage of whole they take up
    QPieSeries *series = new QPieSeries();
    series->append("-2h",c1);
    series->append("2h - 4h",c2);
    series->append("+4h",c3);




    // Create the chart widget
    QChart *chart = new QChart();

    // Add data to chart with title and show legend
    chart->addSeries(series);
    chart->legend()->show();


    // Used to display the chart
    chartView = new QChartView(chart,ui->label_stat);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(400,400);

    chartView->show();
    }
