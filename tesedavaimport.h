#ifndef TESEDAVAIMPORT_H
#define TESEDAVAIMPORT_H

#include<QDateTime>
#include<QSet>
#include<QString>
#include<QStringList>
#include <QObject>
#include <QDir>
#include <QMap>
#include <QVector>
#include <QDebug>
#include <QRegularExpression>
//#include <QRegExp>

class TeseoDavaSrp:public QObject
{
    Q_OBJECT

public:
    TeseoDavaSrp(/*QStringList existingOnly,QStringList dummy_30, QStringList existingOnly_30,QStringList existingAndDummy,QMap<QDate, QVector<QString>> suggested,*/QDir dir, QObject *parent=nullptr );
   /* QStringList*/ void  generateDummyFiles(QDateTime date);
   /* QStringList */ void    getDavaFiles(QDir dir);
   /* QString*/ QMap<QString,QString>  setBestOption(QStringList non_exist_30);
    QDir getDir();
    int  getCount();
    int  getDCount();

    QStringList getExistingOnly();
    QStringList getExistingAndDummy();
    QStringList getExisting_30_Only();
    QStringList getDummy_30();
    QSet<QString> getNonExisting_30_Only();
    QMap<QString, QString > bestMatches();
    QStringList getHours();
    void printMatches();
    QString getBestMatch(QString str);
    QMap<QString,QStringList> getSuggested(QString str);

 private:
    QStringList _existingOnly;
    QStringList _dummy_30;
    QStringList _existingOnly_30;
    QStringList _nonExisting_30;

    //QStringList _existingAndDummy_30;
    QStringList _existingAndDummy;
    QMap<QDate, QVector<QString> > _suggested;
    QMap<QString, QString > _bestMatches;
    QDir _dir;
    QDateTime _date;
    QStringList _hrs={"00","01","02","03","04","05","06","07","08","09","10","11","12","13","14", "15","16","17","18","19","20","21","22","23"};
    QString _concatenation_30= "-30-LF-ZIP";
    int _count;
    int _dcount;
} ;


#endif // TESEDAVAIMPORT_H
