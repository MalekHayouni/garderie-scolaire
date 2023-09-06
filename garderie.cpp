#include "garderie.h"
#include "ui_garderie.h"

Garderie::Garderie(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Garderie)
{
    ui->setupUi(this);
    setWindowTitle("Service workspace");


    //show database content
    show_tables();
}

Garderie::~Garderie()
{
    delete ui;
}

//recuperation des donnees du formulaire activite
QString Garderie::get_id_activite() const { return ui->id_activite->text();}
QString Garderie::get_nom_activite() const { return ui->nom_activite->text();}
QString Garderie::get_description_activite() const { return ui->description_activite->text();}
QString Garderie::get_etablissement_activite() const {return ui->etablissement_activite->currentText();}
int Garderie::get_duree_activite() const{ return ui->duree_activite->value();}

//remplissage des champs du formulaire activite a partir de la base
void Garderie::fill_form_activite(QString selected_activite ) {
    QSqlQuery query;
    query.prepare("select * from activite where id= :sel");
    query.bindValue(":sel", selected_activite);
    query.exec();
    while(query.next()){
        ui->id_activite->setText(selected_activite);
        ui->nom_activite->setText(query.value(1).toString());
        ui->description_activite->setText(query.value(2).toString());
        ui->duree_activite->setValue(query.value(4).toInt());
        ui->etablissement_activite->setCurrentText(query.value(3).toString());

    }
}

//clear the form activite
void Garderie::clear_form_activite(){
ui->id_activite->clear();
ui->nom_activite->clear();
ui->description_activite->clear();
ui->etablissement_activite->setCurrentIndex(0);
ui->duree_activite->setValue(0);
}
//------------------------------------------------------------------------------------------
//recuperation des donnees du formulaire etablissement
QString Garderie::get_id_etablissement() const { return ui->id_etablissement->text();}
QString Garderie::get_nom_etablissement() const { return ui->nom_etablissement->text();}
QString Garderie::get_addresse_etablissement() const { return ui->addresse_etablissement->text();}
QString Garderie::get_tel_etablissement() const { return ui->tel_etablissement->text();}

//remplissage des champs du formulaire etablissement a partir de la base
void Garderie::fill_form_etablissement(QString selected_etablissement ) {
    QSqlQuery query;
    query.prepare("select * from etablissement where id= :sel");
    query.bindValue(":sel", selected_etablissement);
    query.exec();
    while(query.next()){
        ui->id_etablissement->setText(selected_activite);
        ui->nom_etablissement->setText(query.value(1).toString());
        ui->addresse_etablissement->setText(query.value(2).toString());
        ui->tel_etablissement->setText(query.value(3).toString());
    }
}

//clear the form etablissement
void Garderie::clear_form_etablissement(){
ui->id_etablissement->clear();
ui->nom_etablissement->clear();
ui->addresse_etablissement->clear();
ui->tel_etablissement->clear();
}

//*******************************************[ CRUD ]*******************************************//

void Garderie::show_tables(){
    show_table_activite();
    show_table_etablissement();
    ui->etablissement_activite->setModel(tmp_etablissement.liste_etablissement());
}
//------------------------------------------------------------------------------------------
//ajout activite
void Garderie::on_ajouter_activite_clicked()
{
    //recuperation des donnees
        int i=get_duree_activite();
        QString s1=get_id_activite();
        QString s2=get_nom_activite();
        QString s3=get_description_activite();
        QString s4=get_etablissement_activite();

    //ajout
        activite a(s1,s2,s3,s4,i);
        a.ajouter();

    //refresh du tableau (affichage)
     show_tables();
     clear_form_activite();

     //send mail
     QString msg=s4+"has added a "+QString::number(i)+" h activity '"+s2+"' : "+s3;
    sendMail("New Activity",msg);
}
//recuperer l'id, on l'appelle selected activite
void Garderie::on_tableau_activite_clicked(const QModelIndex &index){ selected_activite=ui->tableau_activite->model()->data(index).toString();}
//remplissage form activite
void Garderie::on_tableau_activite_doubleClicked(const QModelIndex &index){ fill_form_activite(selected_activite);}
//mofdifier tableau activite
void Garderie::on_modifier_activite_clicked()
{
    //recuperation des donnees
    int i=get_duree_activite();
    QString s2=get_nom_activite();
    QString s3=get_description_activite();
    QString s4=get_etablissement_activite();
    //recuperer nom activite a partir de la base
    QSqlQuery query;
    QString activity="";
    query.prepare("select * from activite where id= :sel");
    query.bindValue(":sel", selected_activite);
    query.exec();
    while(query.next()){activity=query.value(1).toString(); }

    //mofication
      activite a(selected_activite,s2,s3,s4,i);
      a.modifier(selected_activite);


    //refresh du tableau (affichage)
     show_tables();
     clear_form_activite();

     //send mail
     QString msg=s4+"has edited the activity :" + activity + ". Duration : "+ QString::number(i)+ " h . Description : "+ s3;
     sendMail("Edited Activity",msg);
}
//supprimer activite
void Garderie::on_supprimer_activite_clicked()
{
    //recuperer nom activite a partir de la base
    QSqlQuery query;
    QString activity="";
    query.prepare("select * from activite where id= :sel");
    query.bindValue(":sel", selected_activite);
    query.exec();
    while(query.next()){activity=query.value(1).toString(); }

    activite a;
    a.supprimer(selected_activite);


 //refresh du tableau (affichage)
    show_tables();

    //send mail
    QString msg="The activity :" + activity + " was deleted." ;
    sendMail("Deleted Activity",msg);
}
//affichage activite + metier tri activite
void Garderie::show_table_activite(){
//creation model (masque du tableau) : permet recherche et tri
    proxy_activite = new QSortFilterProxyModel();

 //definir la source (tableau original)
    proxy_activite->setSourceModel(tmp_activite.afficher());

 //pour la recherche
    proxy_activite->setFilterCaseSensitivity(Qt::CaseInsensitive); // S=s (pas de difference entre majiscule et miniscule)
    proxy_activite->setFilterKeyColumn(-1); // chercher dans tout le tableau (-1) ou donner le numero de la colone
   //remplissage tableau avec le masque
    ui->tableau_activite->setModel(proxy_activite);
}
//------------------------------------------------------------------------------------------
//ajout etablissement
void Garderie::on_ajouter_etablissement_clicked()
{
    //recuperation des donnees
        QString s1=get_id_etablissement();
        QString s2=get_nom_etablissement();
        QString s3=get_addresse_etablissement();
        QString s4=get_tel_etablissement();

    //ajout
        etablissement e(s1,s2,s3,s4);
        e.ajouter();

    //refresh du tableau (affichage)
     show_tables();
     clear_form_etablissement();
}
//recuperer l'id, on l'appelle selected etablissement
void Garderie::on_tableau_etablissement_clicked(const QModelIndex &index){ selected_etablissement=ui->tableau_etablissement->model()->data(index).toString();}
//remplissage form etablissement
void Garderie::on_tableau_etablissement_doubleClicked(const QModelIndex &index){ fill_form_etablissement(selected_etablissement);}
//mofdifier tableau etablissement
void Garderie::on_modifier_etablissement_clicked()
{
    //recuperation des donnees
    QString s2=get_nom_etablissement();
    QString s3=get_addresse_etablissement();
    QString s4=get_tel_etablissement();

    //mofication
      etablissement e(selected_etablissement,s2,s3,s4);
      e.modifier(selected_etablissement);

    //refresh du tableau (affichage)
     show_tables();
     clear_form_etablissement();
}
//supprimer etablissement
void Garderie::on_supprimer_etablissement_clicked()
{
    etablissement e;
    e.supprimer(selected_etablissement);

 //refresh du tableau (affichage)
    show_tables();
}
//affichage activite + metier tri activite
void Garderie::show_table_etablissement(){
//creation model (masque du tableau) : permet recherche et tri
    proxy_etablissement = new QSortFilterProxyModel();

 //definir la source (tableau original)
    proxy_etablissement->setSourceModel(tmp_etablissement.afficher());

 //pour la recherche
    proxy_etablissement->setFilterCaseSensitivity(Qt::CaseInsensitive); // S=s (pas de difference entre majiscule et miniscule)
    proxy_etablissement->setFilterKeyColumn(-1); // chercher dans tout le tableau (-1) ou donner le numero de la colone
   //remplissage tableau avec le masque
    ui->tableau_etablissement->setModel(proxy_etablissement);
}

//*******************************************[ METIER ]*******************************************//
//recherche dynamique activite
void Garderie::on_recherche_activite_textChanged(const QString &arg1){proxy_activite->setFilterFixedString(arg1);}
//select sorting creteria activite
void Garderie::on_sort_combo_activite_currentIndexChanged(int index){ proxy_activite->setFilterKeyColumn(ui->sort_combo_activite->currentIndex()-1);}


//------------------------------------------------------------------------------------------
//recherche dynamique etablissement
void Garderie::on_recherche_etablissement_textChanged(const QString &arg1){proxy_etablissement->setFilterFixedString(arg1);}
//select sorting creteria
void Garderie::on_sort_combo_etablissement_currentIndexChanged(int index){proxy_etablissement->setFilterKeyColumn(ui->sort_combo_etablissement->currentIndex()-1);}//combox et tableau indice decalé par 1






