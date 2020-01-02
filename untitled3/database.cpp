#include "database.h"

database::database()
{

}

//建立一??据??接
bool database::createConnection()
{
    //以后就可以用"sqlite1"与?据??行?接了
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "favor");
    db.setDatabaseName(".//qtDb.db");
    if( !db.open())
    {
        qDebug() << "連接失敗";
        return false;
    }

    return true;
}


//?建?据?表
bool database::createTable()
{
    QSqlDatabase db = QSqlDatabase::database("favor"); //建立?据??接
    QSqlQuery query(db);
    bool success = query.exec("create table favor_list(ID int primary key,Song_Path varchar)");
    if(success)
    {
        qDebug() << QObject::tr("sucess！");
        return true;

    }
    else
    {
        qDebug() << QObject::tr("fail！");
        return false;
    }
}

//查?所有信息
bool database::queryAll()
{
    QSqlDatabase db = QSqlDatabase::database("favor"); //建立?据??接
    QSqlQuery query(db);
    query.exec("select * from favor");
    QSqlRecord rec = query.record();
    qDebug() << QObject::tr("test：" ) << rec.count();

    while(query.next())
    {
        for(int index = 0; index < query.size(); index++)
            qDebug() << query.value(index) << " ";
        qDebug() << "\n";
    }
}


//向?据?中插入??

bool database::insert()
{
    QSqlDatabase db = QSqlDatabase::database("favor"); //建立?据??接
    QSqlQuery query(db);
    query.prepare("insert into favor values(1,2)");

    bool success=query.exec();
    if(!success)
    {
        QSqlError lastError = query.lastError();
        qDebug() << lastError.driverText() << QString(QObject::tr("defalt"));
        return false;
    }

    return true;
}

