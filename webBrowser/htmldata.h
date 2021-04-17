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

    operator QString() const {
        return "type: " + QString::fromStdString(std::to_string(tag)) + " data: " + contents + " contence: " + data + "\n";
    }
};

#endif // HTMLDATA_H
