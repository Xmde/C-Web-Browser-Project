#include <htmldata.h>
#include <QVector>
#include <QString>
#include <QDebug>

#ifndef PARSER_H
#define PARSER_H

class parser
{
public:
    parser();
    struct tagData;
    static QString getlinkfromdata(QString data);
    static QString getsrcfromdata(QString data);
    static QString getcssfromdata(QString data);
    static QString getCssForTagType(QString tagType);
    static QVector<tagData> parseTags(QString html);
    static QVector<tagData> addCssToTagData(QVector<tagData> tags);
    static QVector<htmldata> makeTagsGeneric(QVector<tagData> tags);
    static QVector<htmldata> parseHtml(QString html);
    static int getFontSizeFromData(htmldata data, int defaultSize);
    void imageHandle(QString url);
};

#endif // PARSER_H
