#include "sponsors.h"

sponsors::sponsors()
{
    matricule="";
    nom=" ";
    domaine="";
    montant=0;

}
sponsors::sponsors(QString matricule,QString nom,QString domaine,float montant){

this->matricule=matricule;
this->nom=nom;
this->domaine=domaine;
this->montant=montant;



}
bool sponsors::ajouter(){

    QSqlQuery query;
    QString montant_string=QString::number(montant);
    query.prepare("INSERT INTO SPONSORS(matricule,nom,domaine,montant) "
                  "VALUES (:matricule,:nom,:domaine,:montant)");
    query.bindValue(":matricule", matricule);
    query.bindValue(":nom", nom);
    query.bindValue(":domaine", domaine);
    query.bindValue(":montant", montant_string);

   return query.exec();

}
QSqlQueryModel* sponsors::afficher(){
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("SELECT *FROM SPONSORS");
   model->setHeaderData(0, Qt::Horizontal, QObject::tr("matricule"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("domaine"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("montant"));

    return model;
}
bool sponsors ::Delete(QString matricule)
{
    QSqlQuery query;
          QString res =QString:: QString (matricule);
        query.prepare(" Delete from client where matricule=:matricule");
        query.bindValue(":matricule", res);

      return  query.exec();
    }
bool sponsors :: Modifier()
{
QSqlQuery query;
QString res= QString::number(montant);
query.prepare("update sponsors set matricule= :matricule, Domaine= :Domaine,nom= :nom, montant= :montant);
query.bindValue(": matricule", matricule);
query.bindValue(":Domaine",Domaine);
query.bindValue(":nom",nom );
query.bindValue(":montant",montant);

return    query.exec();
}
QSqlQueryModel * Client::trie_NOM()
{
 QSqlQueryModel * model= new QSqlQueryModel();

 model->setQuery("SELECT * FROM sponsors ORDER BY nom ");
 model->setHeaderData(0,Qt::Horizontal,QObject::tr("matricule"));
 model->setHeaderData(1,Qt::Horizontal,QObject::tr("Domaine"));
 model->setHeaderData(2,Qt::Horizontal,QObject::tr("nom"));
 model->setHeaderData(3,Qt::Horizontal,QObject::tr("montant"));

    return model;
}
