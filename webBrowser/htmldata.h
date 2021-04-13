#ifndef HTMLDATA_H
#define HTMLDATA_H

#include <string>

class htmldata
{
public:

    enum tags {text=0, links=1, images=2, other=99};

    tags tag;
    std::string contents;

    htmldata(tags t, std::string s);
    tags gettag();
    std::string getcontents();
};

#endif // HTMLDATA_H
