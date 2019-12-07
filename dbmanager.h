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

    /*******************************************************
    * GetTotalRevenue(QString date) -
    *   STORY #1/3
    *   Depending on the date input, this function will
    *   obtain the total revenue from a given date from
    *   the database. If date is empty, then the total
    *   revenue will be the grand total of all the purchases
    *   from all customers. RETURNS total revenue
    *******************************************************/
    double GetTotalRevenue(QString date);

    /*******************************************************
    * loadEntriesByType(QString date, QString memberType)=
    *   This function loads all the entries from the database
    *   by membership type. date and memberType are passed
    *   in to determine whether all the entries of either the
    *   executive or regular customers will be displayed
    *   (entire week) or all the entries of either the
    *   executive or regular customers from a certain day.
    *   RETURNS QSqlQueryModel
    *******************************************************/
    QSqlQueryModel *loadEntriesByType(QString date, QString memberType);

    /*******************************************************
    *ReturnMemberTypeCount(QString date, QString memberType)-
    *   Depending on the date and memberType, this function
    *   will count either the executive or regular members
    *   from the database. If date is empty, it will count
    *   both members throughout the entire week. Otherwise,
    *   it will count the number of members based on a certain
    *   day
    *   RETURNS memberCount (int)
    *******************************************************/
    int ReturnMemberTypeCount(QString date,QString memberType);

    /*******************************************************
    * loadDateEntriesOnly()-
    *  This function returns a QSqlQueryModel consisting
    *  of only the purchaseDate entries from the
    *  dailySalesReport table in the database.
    *  This function will be called by the store manager to
    *  set the date combo box to the returned model
    *  RETURNS QSqlQueryModel
    *******************************************************/
    QSqlQueryModel *loadDateEntriesOnly();

    //---------------------STORY 2 & 3 CODE------------------------------
    /*******************************************************
    *loadTotalMemberOrItemPurchases(QString decider)-
    *   Depending on the given decider string, this function
    *   will load the total purchases from all members or
    *   total purchases of all items
    *   RETURNS model (QSqlQueryModel)
    *******************************************************/
    QSqlQueryModel *loadTotalMemberOrItemPurchases(QString decider);


    //---------------------STORY 5 CODE------------------------------
    /*******************************************************
    * loadEntriesByExpirDate(QString expirDate, QString memberType)-
    *  This function returns a QSqlQueryModel consisting
    *  of only the expiration month entries from the
    *  dailySalesReport table in the database.
    *  This function will be called by the store manager to
    *  set the expiration month combo box to the returned model
    *  RETURNS QSqlQueryModel
    *******************************************************/
    QSqlQueryModel * loadEntriesByExpirDate(QString expirDate, QString memberType);

    /*******************************************************
    *loadTotalMemberOrItemPurchases(QString decider)-
    *   Depending on the given decider string, this function
    *   will load the expiration month from all members
    *   RETURNS model (QSqlQueryModel)
    *******************************************************/
    QSqlQueryModel * loadMembersByExpirationDate();


private:
    QSqlDatabase m_database;
};

#endif // DBMANAGER_H
