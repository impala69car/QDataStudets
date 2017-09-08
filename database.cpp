#include "database.h"

DataBase(QObject *parent):QObject(parent)
{
}
DataBase::~DataBase()
{
}
void DataBase::connectToDataBase()
{
    bool restore = false;
    if(!QFile("C:/stud/" DATABASE_NAME).exists())
    {
        db=QSqlDatabase::addDatabase("QSQLITE");
        db.setHostName(DATABASE_HOSTNAME);
        db.setDatabaseName("C:/stud/" DATABASE_NAME);
        if(db.open())
        {
            if(!this->createStudentTable())
            {
                restore=false;
            }
            else
            {
                   restore = true;
            }
        }
        else
        {
            restore = false;
        }
    }
    else
    {
        db=QSqlDatabase::addDatabase("QSQLITE");
        db.setHostName(DATABASE_HOSTNAME);
        db.setDatabaseName("C:/stud/" DATABASE_NAME);
        if(db.open())
        {

        }
        else
        {

        }
    }
}

bool DataBase::createStudentTable()
{
    QSqlQuery query;
    if(!query.exec("CREATE TABLE" STUDENT "("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                   STUDENT_NAME "VARCHAR(255) NOT NULL,"
                   STUDENT_YEAR "VARCHAR(100) NOT NULL,"
                   STUDENT_AGE "VARCHAR(100) NOT NULL"
                   ")"
                   ))
    {
        return false;
    }
    else
    {
        return true;
    }
    return false;
}
bool DataBase::insertIntoStudentTable(const QVariantList &data)
{
    QSqlQuery query;
    query.prepare("INSERT INTO" STUDENT "(" STUDENT_NAME ","
                  STUDENT_YEAR ","
                  STUDENT_AGE ")"
                  "VALUES(:Studentname:,Year,:Age )");
    query.bindValue("StudentsName",data[0].toString());
    query.bindValue("Year",data[1].toString());
    query.bindValue("Age",data[2].toString());
    if(!query.exec())
    {
        return false;
    }
    else
    {
        return true;
    }
    return false;
}
