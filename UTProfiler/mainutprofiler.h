#ifndef MAINUTPROFILER_H
#define MAINUTPROFILER_H

#include <QMainWindow>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include <QLabel>
#include <QDebug>

namespace Ui {
class MainUTProfiler;

}

class MainUTProfiler : public QMainWindow
{
    Q_OBJECT

public :
    QSqlDatabase mydb;

    // Connexion et déconnexion à la base
    bool connectDb(){


        mydb = QSqlDatabase::addDatabase("QSQLITE");
        mydb.setDatabaseName("C:/SQlite/DataBase/UTProfiler.db");
        // mydb.setDatabaseName("F:/UTProfiler.db");
        if(!mydb.open()){

           qDebug()<<"failed";
           return false;
         }
         else
         {
            qDebug()<<"succes";
            return true;
         }
}
    void deconnect(){
        QString connection;
        connection=mydb.connectionName();
        QSqlDatabase::removeDatabase(connection);
        //mydb.close();
       // mydb.removeDatabase(QSqlDatabase::defaultConnection);

    }
protected:

public:
    ~MainUTProfiler();

private:
    Ui::MainUTProfiler *ui;
    static MainUTProfiler *utProfiler;
    explicit MainUTProfiler(QWidget *parent = 0);
    MainUTProfiler& operator=(const MainUTProfiler& ut);
    MainUTProfiler(const MainUTProfiler&);


public :
    static MainUTProfiler& getUTProfiler(){
            if(!utProfiler){
                utProfiler = new MainUTProfiler();
                return *utProfiler;
            }
            return *utProfiler;
    }
    static void deleteUTProfiler(){
        delete utProfiler;
    }


private slots:
    void on_addUV_clicked();
    void on_updateDeleteUV_clicked();

    void on_addFormation_clicked();
    void on_updateVisFormation_clicked();
    void on_addUVToFormation_clicked();
    void on_pushButton_7_clicked();

    void on_consulterDossier_clicked();
    void on_simulateState_clicked();
    void on_showUvsTable_clicked();
    void on_pushButton_clicked();
};

#endif // MAINUTPROFILER_H
