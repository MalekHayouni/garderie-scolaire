#ifndef ETABLISSEMENT_H
#define ETABLISSEMENT_H

#include <QSqlQuery>
#include <QSqlQueryModel>

class etablissement
{
public:
    etablissement();
    etablissement(QString,QString,QString,QString);


    bool ajouter();
    bool modifier(QString);
    QSqlQueryModel * afficher();
    bool supprimer(QString);
    QSqlQueryModel * liste_etablissement();

      QString tel, nom, id, addresse;
};

#endif // ETABLISSEMENT_H
