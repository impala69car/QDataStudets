#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QFile>
#include <QDate>
#include <QDebug>

#define DATABASE_HOSTNAME "StudentsDataBase"
#define DATABASE_NAME "DataBase.db"

#define STUDENT "StudentTable"
#define STUDENT_NAME "Studentname"
#define STUDENT_YEAR "Year"
#define STUDENT_AGE "Age"

class DataBase:public QObject
{
    Q_OBJECT
public:
    explicit DataBase(QObject *parent=0);
    ~DataBase();
    void connectToDataBase();
    bool insertIntoStudentTable(const QVariantList &data);
private:
    QSqlDatabase db;
private:
    //void openDB(bool opened);
    void closeDB();
    bool createStudentTable();
};

#endif // DATABASE_H
