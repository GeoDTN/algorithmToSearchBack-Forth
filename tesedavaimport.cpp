#include "tesedavaimport.h"

TeseoDavaSrp::TeseoDavaSrp(/*QStringList existingOnly, QStringList dummy_30, QStringList existingOnly_30,QStringList existingAndDummy,QMap<QDate, QVector<QString>> suggested,*/QDir dir,  QObject *parent):QObject(parent)
  {
    /*
   this->_existingOnly= existingOnly;
   this->_dummy_30=dummy_30 ;
   this->_existingOnly_30= existingOnly_30;
   this->_existingAndDummy=existingAndDummy;
   this->_suggested=suggested;
   this->_count=0;
   */
   this->_dir=dir;
   //this->_date=date;


   qDebug() << "TeseoDavaSrp::TeseoDavaSrp";

}
  QDir TeseoDavaSrp:: getDir()
  {
      return  this->_dir;
  }
 int  TeseoDavaSrp:: getCount(){
     return  this->_count;
 }

 int TeseoDavaSrp::getDCount()
 {
     return  this->_existingAndDummy.length();
 }
/*QStringList*/ void  TeseoDavaSrp::generateDummyFiles(QDateTime date)
{
    //Validate the date here and do nothing if it is not valid
 /*  if(date>_ref_day)
   {
       return ;
   }
   */
   this->_date=date;

   QString _day_month_year=date.toString("dd-MMM-yyyy").toUpper();
   for(QString hr:this->_hrs)
      {
         this->_dummy_30.append(_day_month_year+".H"+hr+_concatenation_30);

       }
   /* not important only test */
     qDebug()<<"Dummy 30s";
     for(QString str:this->_dummy_30)
     {
         qDebug()<<str;
     }

}
QStringList TeseoDavaSrp:: getExistingOnly()
{
    return  this->_existingOnly;
}

QStringList TeseoDavaSrp::getExistingAndDummy()
{
     this->_existingAndDummy.sort();
     return this->_existingAndDummy;
}

QStringList TeseoDavaSrp::getExisting_30_Only()
{
    return this->_existingOnly_30;
}

QStringList TeseoDavaSrp::getDummy_30()
{
    return  this->_dummy_30;
}

QSet<QString> TeseoDavaSrp::getNonExisting_30_Only()
{
    QSet<QString> str1= this->_dummy_30.toSet();
    QSet<QString> str2=this->_existingOnly_30.toSet();
    this->_nonExisting_30=str1.subtract(str2).toList();
    return  this->_nonExisting_30.toSet();
}
QMap<QString, QString > TeseoDavaSrp:: bestMatches()
{
    return this->_bestMatches  ;
}

void TeseoDavaSrp::printMatches()
{

    qDebug()<<"bestMatches pairs :";

    foreach(QString i, this->_bestMatches.keys())
       {
           qDebug() << this->_bestMatches[i];
       }



}

QStringList TeseoDavaSrp::getHours()
{
    this->_hrs.sort();
    return this->_hrs;
}
/*QStringList*/ void  TeseoDavaSrp::getDavaFiles(QDir dir)
{
    this->_dir=dir;

    QStringList files=dir.entryList(QStringList()<<"*-LF-ZIP",QDir::Files);
    this->_count=files.length();
    files.sort();
    this->_existingOnly=files;
    this->_existingOnly_30=files.filter("-30-LF");
    for(QString str:files)
    {
       this->_existingAndDummy.append(str);//.insert(str);
    }

    for(QString str:this->getNonExisting_30_Only())

    {
       this->_existingAndDummy.append(str);
    }

}



QMap<QString,QString>  TeseoDavaSrp::setBestOption(QStringList s) //pass single at a time or non existent
{
    this->_dummy_30.sort();
    this->_hrs.sort();
    this->_existingAndDummy.sort();//Union
    QRegularExpression exp00("-00");
    QRegularExpression exp15("-15");
    QRegularExpression exp30("-30");
    QRegularExpression exp45("-45");

   //Map later the best matchs now just get them

  /*  date.toString("dd-MMM-yyyy");
   * QChar c1,c2;
   * QRegexp regex(QString(".H%1%2).arg(c1).arg(c2)
    QString i;           // current file's number
    QString total;       // number of files to process
    QString fileName;    // current file's name
 */


    if(this->_date>QDateTime::currentDateTime())
    {
      //emit someErrorMessageSignal("The selected date is not valid. Please select current date or from past dates");
        return {};
    }
    else if(this->_count<=0 ||s.length()<=0)
     {

       //emit someErrorMessageSignal("There are no files for the date selected");
        return{};
    }
    else
    {

       for(int i=0 ; i < s.length() ; i++)
         {

            QString hr=this->_hrs.at(this->_dummy_30.indexOf(s.at(i)));//s.at(i) -30 string
           // qDebug()<<"Hour: "<<hr<<"Non existing 30  :"<<s.at(i);
            int y=this->_existingAndDummy.indexOf(s.at(i));//y for h+1; x for h-1
            int x=this->_existingAndDummy.indexOf(s.at(i));
            qDebug()<<"x  :"<<x<<"  y  :"<<y;

            while(x>=0||y< this->_existingAndDummy.length())

              {
                if((y+1)<this->_existingAndDummy.length()&&QRegularExpression(hr).match(this->_existingAndDummy.at(y+1)).hasMatch()&& exp45.match(this->_existingAndDummy.at(y+1)).hasMatch() )
                 {
                   qDebug()<<"  y+1  :"<<y+1<<"Key :"<<s.at(i)<<"Value :"<<this->_existingAndDummy.at(y+1);
                    this->_bestMatches.insert(s.at(i),this->_existingAndDummy.at(y+1));
                    break;
                  }

                  else if((x-1)>=0&&QRegularExpression(hr).match(this->_existingAndDummy.at(x-1)).hasMatch()&& exp15.match(this->_existingAndDummy.at(x-1)).hasMatch())
                  {
                     qDebug()<<"  x-1  :"<<x-1<<"Key :"<<s.at(i)<<"Value :"<<this->_existingAndDummy.at(x-1);
                     this->_bestMatches.insert(s.at(i),this->_existingAndDummy.at(x-1));
                     break;
                   }

                  else if((y+2)<this->_existingAndDummy.length()&&QRegularExpression(hr).match(this->_existingAndDummy.at(y+2)).hasMatch()&& exp00.match(this->_existingAndDummy.at(y+2)).hasMatch())

                   {
                     qDebug()<<"  y+2  :"<<y+2<<"Key :"<<s.at(i)<<"Value :"<<this->_existingAndDummy.at(y+2);
                     this->_bestMatches.insert(s.at(i),this->_existingAndDummy.at(y+2));
                     break;
                    }
                  else if((x-2)>=0&&QRegularExpression(hr).match(this->_existingAndDummy.at(x-2)).hasMatch()&& exp00.match(this->_existingAndDummy.at(x-2)).hasMatch())

                    {
                       qDebug()<<"  x-2  :"<<x-2<<"Key :"<<s.at(i)<<"Value :"<<this->_existingAndDummy.at(x-2);
                       this->_bestMatches.insert(s.at(i),this->_existingAndDummy.at(x-2));
                       break;
                     }
                  else if((y+3)<this->_existingAndDummy.length()&&QRegularExpression(hr).match(this->_existingAndDummy.at(y+3)).hasMatch()&& exp15.match(this->_existingAndDummy.at(y+3)).hasMatch())
                    {
                      qDebug()<<"  y+3  :"<<y+3<<"Key :"<<s.at(i)<<"Value :"<<this->_existingAndDummy.at(y+3);
                      this->_bestMatches.insert(s.at(i),this->_existingAndDummy.at(y+3));
                      break;
                    }
                 else if((x-3)>=0&&QRegularExpression(hr).match(this->_existingAndDummy.at(x-3)).hasMatch()&& exp15.match(this->_existingAndDummy.at(x-3)).hasMatch())
                   {
                    qDebug()<<"  x-3  :"<<x-3<<"Key :"<<s.at(i)<<"Value :"<<this->_existingAndDummy.at(x-3);
                    this->_bestMatches.insert(s.at(i),this->_existingAndDummy.at(x-3));
                    break;
                   }

                 else if((y+4)<this->_existingAndDummy.length()&&QRegularExpression(hr).match(this->_existingAndDummy.at(y+4)).hasMatch()&& exp30.match(this->_existingAndDummy.at(y+4)).hasMatch()&& this->_existingOnly_30.contains(this->_existingAndDummy.at(y+4)))

                   {
                     qDebug()<<"  y+4  :"<<y+4<<"Key :"<<s.at(i)<<"Value :"<<this->_existingAndDummy.at(y+4);
                     this->_bestMatches.insert(s.at(i),this->_existingAndDummy.at(y+4));
                     break;
                   }
                else if ((x-4)>=0&&QRegularExpression(hr).match(this->_existingAndDummy.at(x-4)).hasMatch()&& exp30.match(this->_existingAndDummy.at(x-4)).hasMatch()&& this->_existingOnly_30.contains(this->_existingAndDummy.at(x-4)))  //else if
                   {
                     qDebug()<<"  x-4  :"<<x-4<<"Key :"<<s.at(i)<<"Value :"<<this->_existingAndDummy.at(x-4);
                     this->_bestMatches.insert(s.at(i),this->_existingAndDummy.at(x-4));
                     break;
                     }
               --x;++y;


          }//while

        } //for
    }//else
       return this->_bestMatches;
}
