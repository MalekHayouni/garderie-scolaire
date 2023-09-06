#include "etablissement.h"

etablissement::etablissement()
{

}

etablissement::etablissement(QString s1 ,QString s2,QString s3 ,QString s4){
    id=s1;
    nom=s2;
    addresse=s3;
    tel=s4;

}


bool etablissement::ajouter(){

    QSqlQuery query;


    query.prepare("INSERT INTO ETABLISSEMENT (id, nom,addresse,tel) VALUES (:id, :nom, :addresse,:tel)");

    //remplir variable querry avec valeur dans qt d'une maniere securisée
    query.bindValue(":id", id);
    query.bindValue(":nom",nom);
    query.bindValue(":addresse", addresse);
    query.bindValue(":tel", tel);

    return    query.exec();

}

bool etablissement::modifier(QString selected){

    QSqlQuery query;


    query.prepare(" UPDATE ETABLISSEMENT SET nom= :nom ,addresse= :addresse , tel= :tel where id= :id");

    query.bindValue(":id", selected);
    query.bindValue(":nom",nom);
    query.bindValue(":addresse", addresse);
    query.bindValue(":tel", tel);

    return    query.exec();

}

 QSqlQueryModel * etablissement::afficher(){

     QSqlQueryModel * modal=new QSqlQueryModel();
     modal->setQuery("SELECT * FROM ETABLISSEMENT");

     return modal;

 }
  bool etablissement::supprimer(QString selected){

      QSqlQuery query;
      query.prepare("Delete from ETABLISSEMENT where id = :sel ");
      query.bindValue(":sel", selected);
      return    query.exec();


  }

  QSqlQueryModel * etablissement::liste_etablissement(){
      QSqlQueryModel * modal=new QSqlQueryModel();
      modal->setQuery("SELECT nom FROM ETABLISSEMENT");

      return modal;
  }
