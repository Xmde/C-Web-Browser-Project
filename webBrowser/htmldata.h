#ifndef HTMLDATA_H
#define HTMLDATA_H

#include <QString>

class htmldata
{
public:

    enum tags {text=0, link=1, image=2, other=99};

    tags tag;
    QString contents;
    QString data;

    htmldata(tags t, QString c, QString d);
    //tag type
    tags gettag();
    //the contence of the tag <p>contence here</p>
    QString getcontents();
    //gets the data in the tag <img [data]></img>
    QString getdata();


    //some static functions to parse out css and src from tag data
    //TOTO impliment
    static QString getlinkfromdata(QString data);

    static QString getsrcfromdata(QString data);

    static QString getcssfromdata(QString data);

    //a function to get the css data for a tag type

    QString getcssfortag(tags tag);
};

#endif // HTMLDATA_H
