#ifndef DATABASE_H
#define DATABASE_H

#include <QTextCodec>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTime>
#include <QSqlError>
#include <QtDebug>
#include <QSqlDriver>
#include <QSqlRecord>


class database : public QSqlDatabase
{

public:

    database();
    bool createConnection();  //?建一??接
    bool createTable();       //?建?据?表
    bool insert();            //出入?据
    bool queryAll();          //查?所有信息
    bool updateById(int id);  //更新
    bool deleteById(int id);  //?除
    bool sortById();          //排序
};


#endif // DATABASE_H
