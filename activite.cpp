#include "activite.h"

activite::activite()
{

}

activite::activite(QString s1 ,QString s2,QString s3 ,QString s4,int i){
    id=s1;
    nom=s2;
    description=s3;
    etablissement=s4;
    duree=i;

}


bool activite::ajouter(){

    QSqlQuery query;


    query.prepare("INSERT INTO activite (id, nom,description,etablissement,duree) VALUES (:id, :nom, :description,:etablissement,:duree)");

    //remplir variable querry avec valeur dans qt d'une maniere securisée
    query.bindValue(":id", id);
    query.bindValue(":nom",nom);
    query.bindValue(":description", description);
    query.bindValue(":duree", duree);
    query.bindValue(":etablissement", etablissement);

    return    query.exec();

}

bool activite::modifier(QString selected){

    QSqlQuery query;


    query.prepare(" UPDATE activite SET nom= :nom ,description= :description ,etablissement= :etablissement, duree= :duree where id= :id");

    query.bindValue(":id", selected);
    query.bindValue(":nom",nom);
    query.bindValue(":description", description);
    query.bindValue(":etablissement", etablissement);
    query.bindValue(":duree", duree);

    return    query.exec();

}

 QSqlQueryModel * activite::afficher(){

     QSqlQueryModel * modal=new QSqlQueryModel();
     modal->setQuery("SELECT * FROM activite");

     return modal;

 }
  bool activite::supprimer(QString selected){

      QSqlQuery query;
      query.prepare("Delete from activite where id = :sel ");
      query.bindValue(":sel", selected);
      return    query.exec();


  }
