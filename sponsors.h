#ifndef SPONSORS_H
#define SPONSORS_H
#include "connection.h"
#include <string>
#include <iostream>
#include <QString>
#include <QVariant>
#include <QtSql/QtSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
class sponsors
{

private:
    QString matricule;
    QString nom;
    QString domaine;
    float montant;
public:
    sponsors();
    sponsors(QString matricule,QString nom,QString domaine,float montant);


      QString Getmatricule() { return matricule; }
      void Setmatricule(QString val) { matricule = val; }
      QString Getnom() { return nom; }
      void Setnom(QString val) { nom = val; }
      QString Getdomaine() { return domaine; }
      void Setdomaine(QString val) { domaine = val; }
      float Getmontant() { return montant; }
      void Setmontant(float val) { montant = val; }

      bool ajouter();
      QSqlQueryModel* afficher();
      bool supprimer(int);

      bool modifier();
          QSqlQueryModel * trie_NOM();
      private:
          float montant;
          QString   matricule, domaine, nom;
      };




};

#endif // SPONSORS_H
