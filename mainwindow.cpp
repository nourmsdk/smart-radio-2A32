#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sponsors.h"
#include <QUrl>
#include <QWidget>
#include <QVariant>
#include <QPdfWriter>
#include <QFileDialog>
#include  <QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include "statistique.h"
#include <QtCharts/QPieSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include "windows.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tablespon->setModel(S.afficher());
   //map
    QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                        QCoreApplication::organizationName(), QCoreApplication::applicationName());

     ui->WebBrowser_2->dynamicCall("Navigate(const QString&)", "https://www.google.com/maps/place/ESPRIT/@36.9016729,10.1713215,15z");
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
    QString  matricule=ui->sup_m->text();
    bool test=S.supprimer(matricule);
            QMessageBox msgBox;

        if(test){
            //actualiser pour l'affichage
            ui->tablespon->setModel(S.afficher());
                 msgBox.setText("suppression reussit");
                    ui->tablespon->setModel(S.afficher());
                }
                else
                    msgBox.setText("echec de suppression");
                    msgBox.exec();

}



void MainWindow::on_update_clicked()
{
    QString matricule=ui->matricule_3->text();
    QString nom=ui->nom_3->text();
    QString domaine=ui->domaine_3->text();
    int montant=ui->montant_3->text().toInt();



       sponsors  S1(matricule,nom,domaine,montant);

        bool test=S1.modifier();
        if(test)
        {
            //actualiser pour l'affichage
            ui->tablespon->setModel(S1.afficher());
                    QMessageBox::information(nullptr, QObject::tr("database is open"),
                                QObject::tr("modification effectué.\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);}
        else
            QMessageBox::critical(nullptr, QObject::tr("database is open"),
                        QObject::tr("modification non effectué.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
    }



void MainWindow::on_pushButton_clicked()
{
    ui->tablespon->setModel(S.affichertriZA());
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->tablespon->setModel(S.affichertriAZ());

}

void MainWindow::on_matricule_2_textChanged(const QString &arg1)
{
    ui->tablespon->setModel(S.rechercher(arg1));

}

void MainWindow::on_matricule_4_textChanged(const QString &arg1)
{
    ui->tablespon->setModel(S.recherchernom(arg1));

}

void MainWindow::on_pushButton_4_clicked()
{
    QSqlQuery query;
          QMessageBox msgBox;
              QString id =ui->id->text(), pw=ui->pw->text(),type="";
              query.prepare("SELECT nom FROM PERSONNELS WHERE IDENTIFIANT =:id AND MOT_DE_PASSE =:pwd");
              query.bindValue(":id", id);
              query.bindValue(":pwd", pw);
              query.exec();

              while(query.next())
            {

             type=query.value(0).toString();
             }
              if (query.exec())
              {              msgBox.setText("Identifié comme  " +type);
                  msgBox.exec();

                   ui->stackedWidget->setCurrentIndex(1);
 }
              else { QMessageBox::critical(nullptr, QObject::tr("Echec d'authentification"),
                                           QObject::tr("Mot de passe ou nom d'utilisateur non-valide"), QMessageBox::Cancel);


             }



}


void MainWindow::on_PDF_clicked()
{

        QString strStream;
                                    QTextStream out(&strStream);

                                    const int rowCount = ui->tablespon->model()->rowCount();
                                    const int columnCount = ui->tablespon->model()->columnCount();

                                    out <<  "<html>\n"
                                        "<head>\n"
                                        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                                        <<  QString("<title>%1</title>\n").arg("strTitle")
                                        <<  "</head>\n"
                                        "<body bgcolor=#ffffff link=#5000A0>\n"

                                       //     "<align='right'> " << datefich << "</align>"
                                        "<center> <H1>Liste des sponsors </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

                                    // headers
                                    out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
                                    for (int column = 0; column < columnCount; column++)
                                        if (!ui->tablespon->isColumnHidden(column))
                                            out << QString("<th>%1</th>").arg(ui->tablespon->model()->headerData(column, Qt::Horizontal).toString());
                                    out << "</tr></thead>\n";

                                    // data table
                                    for (int row = 0; row < rowCount; row++) {
                                        out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                                        for (int column = 0; column < columnCount; column++) {
                                            if (!ui->tablespon->isColumnHidden(column)) {
                                                QString data = ui->tablespon->model()->data(ui->tablespon->model()->index(row, column)).toString().simplified();
                                                out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                            }
                                        }
                                        out << "</tr>\n";
                                    }
                                    out <<  "</table> </center>\n"
                                        "</body>\n"
                                        "</html>\n";

                              QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Sauvegarder en PDF", QString(), "*.pdf");
                                if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

                               QPrinter printer (QPrinter::PrinterResolution);
                                printer.setOutputFormat(QPrinter::PdfFormat);
                               printer.setPaperSize(QPrinter::A4);
                              printer.setOutputFileName(fileName);

                               QTextDocument doc;
                                doc.setHtml(strStream);
                                doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
                                doc.print(&printer);


}



void MainWindow::on_STAT_clicked()
{
    QPieSeries *series = new QPieSeries();


           QStringList list=S.listeadresses("montant");



           for (int i =0; i< list.size();i++)
           {
               series->append(list[i],S.calcul_adresses(list[i],"montant"));

           }
           QPieSlice *slice = series->slices().at(1);
           slice->setLabelVisible();
           slice->setExploded();


           QtCharts::QChart *chart =new QtCharts::QChart();
           chart->addSeries(series);
           chart->setTitle("Statistiques");
           chart->setAnimationOptions(QChart::AllAnimations);
           QChartView *chartview=new QChartView(chart);
           QGridLayout *mainLayout=new QGridLayout();
           mainLayout->addWidget(chartview,0,0);
           ui->statistiques_4->setLayout(mainLayout);
}
