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
    //cout<<"The number of existing files is:  "<<davasrp.getCount()<<"\n\n\n";
    //qDebug()<<"Non existing 30s are/is :";
     qDebug()<<"Number of missing ones is :"<<davasrp.setBestOption(davasrp.getNonExisting_30_Only().toList()).size();
    for(QString str:davasrp.getNonExisting_30_Only())
    {

        qDebug()<<"Key  "<<str<<"   Value  :"<<davasrp.getBestMatch(str);
        qDebug()<<"=====================================================";

    }
    qDebug()<<"Printing suggested ones for each missing";
    for(QString str:davasrp.getNonExisting_30_Only())
    {
                qDebug()<<"Key  "<<str<<"   Value  :"<<davasrp.getSuggested(str).values();
     }
    //qDebug()<<"Dummy hrs are  :";
   /* for(QString str:davasrp.getHours())
    {
        qDebug()<<str;
    }
 */
    /*
    cout<<"The number of existing & nonexisting files is:  "<<davasrp.getDCount()<<"\n\n";
    for(QString str:davasrp.getExistingAndDummy())
    {
        qDebug()<<str;
    }
 */

 /* qDebug()<<"Missing & Best Match pairs";
    foreach(QString i, davasrp.setBestOption(davasrp.getNonExisting_30_Only().toList()).keys())
        {
            qDebug() <<"Missing  :"<<i <<"Best match  :"<< davasrp.setBestOption(davasrp.getNonExisting_30_Only().toList())[i];
        }
*/
    return 0;
}
