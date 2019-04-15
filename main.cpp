#include <iostream>
#include "tesedavaimport.h"
using namespace std;

int main()
{
    QString path="C:/Users/tadewos.somano/Desktop/davatestFolder";

    QDir  dir(path);
    TeseoDavaSrp davasrp(dir);
    davasrp.generateDummyFiles(QDateTime ::currentDateTime());
    davasrp.getDavaFiles(davasrp.getDir());
    cout<<"The number of existing files is:  "<<davasrp.getCount()<<"\n\n\n";

    qDebug()<<"Non existing 30s are/is :";
    for(QString str:davasrp.getNonExisting_30_Only())
    {

        qDebug()<<str;
    }
     qDebug()<<"Dummy hrs are  :";
    for(QString str:davasrp.getHours())
    {
        qDebug()<<str;
    }
    cout<<"The number of existing & nonexisting files is:  "<<davasrp.getDCount()<<"\n\n";
    for(QString str:davasrp.getExistingAndDummy())
    {
        qDebug()<<str;
    }

    qDebug()<<"Begin Algorithm";
    davasrp.setBestOption(davasrp.getNonExisting_30_Only().toList());
    qDebug()<<"End Algorithm";

  /*
    qDebug()<<"Existing only is :";
    for(QString str:davasrp.getExistingOnly())
    {

        qDebug()<<str;
    }


    qDebug()<<"getExisting_30_Only :";
    for(QString str:davasrp.getExisting_30_Only())
    {

        qDebug()<<str;
    }

    qDebug()<<"getExistingAndDummy_30 :";
    for(QString str:davasrp.getDummy_30())
    {
        qDebug()<<str;
    }

    qDebug()<<"getExistingAndDummy :";
    for(QString str:davasrp.getExistingAndDummy())
    {
        qDebug()<<str;
    }
*/

    QMap<QString, QString>::const_iterator i=davasrp.bestMatches().constBegin();
    qDebug()<<"bestMatches pairs :";
    while (i != davasrp.bestMatches().constEnd()) {

        qDebug()<<"Missing 30: "<<i.key() <<"Corresponding best option: "<<i.value() ;
     }

    return 0;
}
