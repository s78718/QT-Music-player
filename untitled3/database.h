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
    bool createConnection();  //?�ؤ@??��
    bool createTable();       //?��?�u?��
    bool insert();            //�X�J?�u
    bool queryAll();          //�d?�Ҧ��H��
    bool updateById(int id);  //��s
    bool deleteById(int id);  //?��
    bool sortById();          //�Ƨ�
};


#endif // DATABASE_H
