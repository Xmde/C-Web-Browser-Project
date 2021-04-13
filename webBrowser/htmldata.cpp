#include "htmldata.h"

htmldata::htmldata(htmldata::tags t, std::string s)
{
    tag = t;
    contents = s;
}

htmldata::tags htmldata::gettag()
{
    return tag;
}

std::string htmldata::getcontents(){
    return contents;
}
