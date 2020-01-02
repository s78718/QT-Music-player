#include "database.h"

database::database()
{

}

//�إߤ@??�u??��
bool database::createConnection()
{
    //�H�Z�N�i�H��"sqlite1"�O?�u??��?���F
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "favor");
    db.setDatabaseName(".//qtDb.db");
    if( !db.open())
    {
        qDebug() << "�s������";
        return false;
    }

    return true;
}


//?��?�u?��
bool database::createTable()
{
    QSqlDatabase db = QSqlDatabase::database("favor"); //�إ�?�u??��
    QSqlQuery query(db);
    bool success = query.exec("create table favor_list(ID int primary key,Song_Path varchar)");
    if(success)
    {
        qDebug() << QObject::tr("sucess�I");
        return true;

    }
    else
    {
        qDebug() << QObject::tr("fail�I");
        return false;
    }
}

//�d?�Ҧ��H��
bool database::queryAll()
{
    QSqlDatabase db = QSqlDatabase::database("favor"); //�إ�?�u??��
    QSqlQuery query(db);
    query.exec("select * from favor");
    QSqlRecord rec = query.record();
    qDebug() << QObject::tr("test�G" ) << rec.count();

    while(query.next())
    {
        for(int index = 0; index < query.size(); index++)
            qDebug() << query.value(index) << " ";
        qDebug() << "\n";
    }
}


//�V?�u?�����J??

bool database::insert()
{
    QSqlDatabase db = QSqlDatabase::database("favor"); //�إ�?�u??��
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

