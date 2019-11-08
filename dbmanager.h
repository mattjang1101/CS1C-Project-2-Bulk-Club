#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <QtSql>

class DBManager
{
public:
    DBManager();
    ~DBManager();

    /*******************************************************
    * loadEntries() -
    *  This function helps the program read the contents.
    *  from the database. This function primarily uses
    *  the query function, "select * from". The database
    *  in which it is selected from is called customer.
    *  Throughout the process, the data returned is
    *  is stored in the table created in createTable().
    *  If the database or data has trouble storing the
    *  values, it will output "error loading values to
    *  db". Returns pointer
    *******************************************************/
    QSqlQueryModel *loadEntries();

    /*******************************************************
    * loadEntriesByDate(QString date) -
    *   STORY #1
    *   This function will return a query model based
    *   on a certain date. Will return the table that
    *   displays a sales report for any given day.
    *******************************************************/
    QSqlQueryModel *loadEntriesByDate(QString date);

    double GetTotalRevenue(QString date);

private:
    QSqlDatabase m_database;
};

#endif // DBMANAGER_H
