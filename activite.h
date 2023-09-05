#ifndef ACTIVITE_H
#define ACTIVITE_H

#include <QSqlQuery>
#include <QSqlQueryModel>

class activite
{
public:
    activite();
    activite(QString,QString,QString,QString,int);


    bool ajouter();
    bool modifier(QString);
    QSqlQueryModel * afficher();
    bool supprimer(QString);

      int duree;
      QString description, nom, id, etablissement;
};

#endif // ACTIVITE_H
