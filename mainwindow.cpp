#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sponsors.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tablespon->setModel(S.afficher());



}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ajouter_clicked()
{
    QString matricule=ui->matricule->text();
    QString nom=ui->nom->text();
    QString domaine=ui->domaine->text();
    int montant=ui->montant->text().toInt();

  sponsors S(matricule,nom,domaine,montant);
  bool test=S.ajouter();
  if (test)
  {
      //actualiser pour l'affichage
       ui->tablespon->setModel(S.afficher());
      QMessageBox::information(nullptr, QObject::tr("OK") , QObject::tr("Ajout effectué\n"
                                                                   "Click Cancel to exit"), QMessageBox::Cancel);
  }
  else
      QMessageBox::critical(nullptr, QObject::tr("NOT OK"), QObject::tr("Ajout non effectué\n"
                                                                         "Click Cancel to exit"), QMessageBox::Cancel);

}


void MainWindow::on_delete_2_clicked()
{sponsors S;
    QString  matricule =ui->la_matricule_supp->text().toInt();
    bool test=S.supprimer(matricule);
            QMessageBox msgBox;

        if(test){
            //actualiser pour l'affichage
            ui->tab_sponsors->setModel(C.afficher());
                 msgBox.setText("suppression reussit");
                    ui->tab_sponsors->setModel(C.afficher());
                }
                else
                    msgBox.setText("echec de suppression");
                    msgBox.exec();

}



void MainWindow::on_update_clicked()
{
    QString matricule =ui->lineEdit_matricule_2->text();

        QString nom=ui->lineEdit_nom_2->text();

        QString domaine=ui->lineEdit_domaine_2->text();

       float  montant=ui->lineEdit_montant_2->text();



       sponsors  S1(matricule,nom,domaine,montant);

        bool test=S1.modifier();
        if(test)
        {
            //actualiser pour l'affichage
            ui->tab_sponsors->setModel(S.afficher());
                    QMessageBox::information(nullptr, QObject::tr("database is open"),
                                QObject::tr("modification effectué.\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);}
        else
            QMessageBox::critical(nullptr, QObject::tr("database is open"),
                        QObject::tr("modification non effectué.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
    }

}
