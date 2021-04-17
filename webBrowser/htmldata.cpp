#include "htmldata.h"

htmldata::htmldata(htmldata::tags t, QString s, QString d)
{
    tag = t;
    contents = s;
    data = d;
}

htmldata::tags htmldata::gettag()
{
    return tag;
}

QString htmldata::getcontents(){
    return contents;
}

QString htmldata::getdata(){
    return data;
}
