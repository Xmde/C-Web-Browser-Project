#include "parser.h"
#include <QRegularExpression>

parser::parser()
{

}

struct parser::tagData{
    QString tagtype;
    QString tagData;
    QString tagContence;

   friend std::ostream& operator<<(std::ostream &os, const struct tagData &str){
      //return os << "type: " + str.tagtype.toUtf8().toStdString() + " data: " + str.tagData.toUtf8().toStdString() + " contence: " + str.tagContence.toUtf8().toStdString() << std::end;
       return os;
   }

   operator QString() const {
       return "type: " + tagtype + " data: " + tagData + " contence: " + tagContence + "\n";
   }
};

QString parser::getlinkfromdata(QString data){

    //qDebug() << data;

    int indexOfHref;
    int indexOfHrefEnd;
    QString output;

    indexOfHref = data.indexOf("href=\"")+6;
    indexOfHrefEnd = data.indexOf("\"", indexOfHref);

    //qDebug() << indexOfHref;
    //qDebug() << indexOfHrefEnd;

    bool inQuotes = false;
    for(int i = indexOfHref; i < indexOfHrefEnd; i++){
        QChar c = data.at(i);
        if(c == *"\""){
            inQuotes = !inQuotes;
        }

        if(!inQuotes){
            if(c == *" "){
                break;
            }
            else{
                output.append(c);
            }
        }
        else{
            output.append(c);
        }

    }

    //qDebug() << output;

    return output;
};

QString parser::getsrcfromdata(QString data){
    //qDebug() << data;

    int indexOfSrc;
    int indexOfSrcEnd;
    QString output;

    indexOfSrc = data.indexOf("src=\"")+5;
    indexOfSrcEnd = data.indexOf("\"", indexOfSrc);

    //qDebug() << indexOfHref;
    //qDebug() << indexOfHrefEnd;

    bool inQuotes = false;
    for(int i = indexOfSrc; i < indexOfSrcEnd; i++){
        QChar c = data.at(i);
        if(c == *"\""){
            inQuotes = !inQuotes;
        }

        if(!inQuotes){
            if(c == *" "){
                break;
            }
            else{
                output.append(c);
            }
        }
        else{
            output.append(c);
        }

    }

    qDebug() << output;

    return output;
};

QString parser::getcssfromdata(QString data){
    //qDebug() << data;

    int indexOfStyle;
    int indexOfStyleEnd;
    QString output;

    indexOfStyle = data.indexOf("style=\"")+7;
    indexOfStyleEnd = data.indexOf("\"", indexOfStyle);

    //qDebug() << indexOfHref;
    //qDebug() << indexOfHrefEnd;

    for(int i = indexOfStyle; i < indexOfStyleEnd; i++){
        output.append(data.at(i));
    }

    qDebug() << output;

    return output;
};

QString parser::getCssForTagType(QString tagType){


    QString output;

    QVector<QString> convertTagtoInt = {"p", "h1", "h2", "h3", "h4", "h5", "h6", "strong", "b", "cite", "address", "i"};

    switch(convertTagtoInt.indexOf(tagType)){

    //p Tag
    case 0:
        output.append("color: black;");
        break;
    //h1 Tag
    case 1:
        output.append("font-size: 2em; font-weight: bold; color: black;");
        break;
    //h2 Tag
    case 2:
        output.append("font-size: 1.5em; font-weight: bold; color: black;");
        break;
    //h3 Tag
    case 3:
        output.append("font-size: 1.17em; font-weight: bold; color: black;");
        break;
    //h4 Tag
    case 4:
        output.append("font-weight: bold; color: black;");
        break;
    //h5 Tag
    case 5:
        output.append("font-size: 0.83em; font-weight: bold; color: black;");
        break;
    //h6 Tab
    case 6:
        output.append("font-size: 0.67em; font-weight: bold; color: black;");
        break;
    //Bold and Strong Tag
    case 7:
    case 8:
        output.append("font-weight: bold; color: black;");
        break;
    //Address and i and cite Tag
    case 9:
    case 10:
    case 11:
        output.append("font-style: italic; color: black;");
        break;
    default:
        output.append("color: black;");
        break;
    }

    return output;

}

//turns the html into a list of tags
//this is BAD and DUMB
QVector<parser::tagData> parser::parseTags(QString html){
    qDebug() << "parsing tags";

    //removes coments
    html.remove(QRegularExpression("<!-(.*)->"));

    qDebug() << "with removed comments: " << html;

    QVector<tagData> tags;

    //a list of all the tags that are open so that nested tags work
    QVector<QString> currentTag;
    currentTag.append("");

    QVector<QString> tagContence;
    tagContence.append("");

    QVector<QString> tagData;
    tagData.append("");

    bool inTagType = false;
    bool inTagData = false;
    bool inTagContence = false;
    bool tagOver = false;
    bool inQuotes = false;
    int charsAfterTagStart = 999;
    for(QChar x : html){
        const char c = x.toLatin1();
        qDebug() << c;
        if(c == *"\""){
            inQuotes = !inQuotes;
            if(inQuotes){
                qDebug() << "quotes entered";
            }
            else{
                qDebug() << "quotes exited";
            }
        }

        //disables special chars if in quotes
        if(!inQuotes){

            //checks for tag start
            if((c == *"<")){
                inTagType = true;
                qDebug() << "new tag started, incrimenting arrays";
                charsAfterTagStart = 0;
                currentTag.append("");
                tagContence.append("");
                tagData.append("");
            }

            //checks foor space
            else if(c == *" "){
                if(charsAfterTagStart < 2){
                    qDebug() << "tag starting was WRONG, reverting all";
                    inTagType = false;
                    currentTag.removeLast();
                    tagContence.removeLast();
                    tagData.removeLast();
                }
                //moves to next tag data if was reading tag type
                if(inTagType){
                    inTagType = false;
                    inTagData = true;
                    qDebug() << "now reading tag data";
                }

                //if wasent reading tag type add the space to the data or contence
                else{
                    if(inTagData && !tagOver){
                        tagData.last().append(c);
                        qDebug() << "added ' ' to data";
                    }
                    else if(inTagContence && !tagOver){
                        tagContence.last().append(c);
                        qDebug() << "added ' ' to contens";
                    }
                    else{
                        //do nothing
                    }
                }
            }

            //checks for slash
            else if(c == *"/"){

                //qDebug() << "slash";

                if(charsAfterTagStart < 2){
                    qDebug() << "tag was ending, not starting, reverting arrays";
                    currentTag.removeLast();
                    tagContence.removeLast();
                    tagData.removeLast();
                }

                //ends tag if the tag is a closing tag
                if(inTagType){
                    qDebug() << "tag ended";
                    tagOver = true;
                }

                //adds the tag to the data or contense if not in type
                else if(inTagData && !tagOver){
                    tagData.last().append(c);
                    qDebug() << "added '/' to data";
                }
                else if(inTagContence && !tagOver){
                    tagContence.last().append(c);
                    qDebug() << "added '/' to contens";
                }
                else{
                    //do nothing
                }
            }

            //checks for tag close
            else if(c == *">"){

                //stops reading tag data
                if(inTagData || inTagType){
                    inTagType = false;
                    inTagData = false;
                    inTagContence = true;

                    qDebug() << "now reading tag contence";

                    qDebug() << "checkging if tag should be added to list";
                    //many sights dont close img tags

                    //adds the tag if it just read a closing tag
                    if(tagOver || (currentTag.last() == "img") || (currentTag.last() == "hr") || (currentTag.last() == "br")){
                        //wrights the tag and its data to the tags list
                        qDebug() << "adding tag...";
                        struct tagData* tag = new struct tagData;
                        tag->tagData = tagData.last();
                        if(tagData.length() > 1){
                           tagData.removeLast();
                        }
                        else{
                            tagData.last().clear();
                        }
                        tag->tagtype = currentTag.last();
                        if(currentTag.length() > 1){
                           currentTag.removeLast();
                        }
                        else{
                            currentTag.last().clear();
                        }
                        tag->tagContence = tagContence.last();
                        if(tagContence.length() > 1){
                           tagContence.removeLast();
                        }
                        else{
                            tagContence.last().clear();
                        }
                        tags.append(*tag);
                        tagOver = false;

                        qDebug() << "added tag of type: " + tag->tagtype + " with data: " + tag->tagData + " and contens: " + tag->tagContence;
                    }
                    else{
                        qDebug() << "tag not added";
                    }
                }

                //if not a closing for a tag add it to the data or contense
                else{
                    if(inTagData && !tagOver){
                        tagData.last().append(c);
                        qDebug() << "added '>' to data";
                    }
                    else if(inTagContence && !tagOver){
                        tagContence.last().append(c);
                        qDebug() << "added '>' to contens";
                    }
                    else{
                        //do nothing
                    }
                }

            }

            //if the char is not a special charactor thaen add it to the currently reading section
            else{
                if(inTagType && !tagOver){
                    currentTag.last().append(c);
                    qDebug() << "added " << c << " to type";
                }
                else if(inTagData && !tagOver){
                    tagData.last().append(c);
                    qDebug() << "added " << c << " to data";
                }
                else if(inTagContence && !tagOver){
                    tagContence.last().append(c);
                    qDebug() << "added " << c << " to contens";
                }
                else{
                    //do nothing
                }
            }
        }

        //if we are in quotes then blindly add the char to the curently reading section
        else{
            if(inTagType && !tagOver){
                currentTag.last().append(c);
                qDebug() << "added " << c << " to type while in quotes";
            }
            else if(inTagData && !tagOver){
                tagData.last().append(c);
                qDebug() << "added " << c << " to data while in quotes";
            }
            else if(inTagContence && !tagOver){
                tagContence.last().append(c);
                qDebug() << "added " << c << " to contens while in quotes";
            }
            else{
                //do nothing
            }
        }

        charsAfterTagStart++;
    }

    qDebug() << "printing parsed tags ...";
    qDebug() << tags;
    return tags;
}

//adds the approprate css data to the tags from the css file/tag type
QVector<parser::tagData> parser::addCssToTagData(QVector<tagData> tags){
    qDebug() << "adding css to tag data";
    QVector<tagData> output = QVector<tagData>();

    for(tagData t : tags){
        //coppys old tag type and contense to new struct
        tagData newTag = parser::tagData();
        newTag.tagtype = t.tagtype;
        newTag.tagContence = t.tagContence;

        //gets the old data we care about to be used later
        QString newData = t.tagData;
        QString oldCss = getcssfromdata(newData);

        qDebug() << "origonal data: " + newData;

        //fixes broken css
        oldCss.append(";");

        //removes old css from tag
        int indexOfStyle;
        int indexOfStyleEnd;

        indexOfStyle = newData.indexOf("style=\"");
        indexOfStyleEnd = newData.indexOf("\"", indexOfStyle);

        newData.remove(indexOfStyle, (indexOfStyleEnd - indexOfStyle));

        qDebug() << "data with style removed: " + newData;

        newData.append(" style=\"" + getCssForTagType(newTag.tagtype) + " " + oldCss + "\" ");

        qDebug() << "data with improved style: " + newData;

        newTag.tagData = newData;

        output.append(newTag);
    }


    return output;
}

//makes the raw tags into the generic tags that can be rendered
QVector<htmldata> parser::makeTagsGeneric(QVector<parser::tagData> tags){
    qDebug() << "makign tags generic";

    QVector<QString> textTags = {"p", "div", "strong", "abbr", "address", "b", "i", "bdi", "bdo", "blockquote", "caption", "cite", "del", "em", "h1", "h2", "h3", "h4", "h5", "h6", "q", "rt", "s", "small", "span", "sub", "sup", "var"};
    QVector<htmldata> genericTags;

    for(struct tagData t : tags){
        if(t.tagtype == "img"){
            genericTags.append(htmldata(htmldata::image, t.tagContence, t.tagData));
        }
        else if(t.tagtype == "a"){
            genericTags.append(htmldata(htmldata::link, t.tagContence, t.tagData));
        }
        else{
            bool tagIsText = false;
            for(QString textTag : textTags){
                if(t.tagtype == textTag){
                    tagIsText = true;
                    break;
                }
            }
            if(tagIsText){
                genericTags.append(htmldata(htmldata::text, t.tagContence, t.tagData));
            }
            else{
                genericTags.append(htmldata(htmldata::other, t.tagContence, t.tagData));
            }
        }
    }

    qDebug() << genericTags;

    return genericTags;
}

//parses the html into the generic tags to render
QVector<htmldata> parser::parseHtml(QString html){
    //checks if the page contains tags
    if(html.split("<").length() < 2){
        QVector<htmldata> badPage = QVector<htmldata>();
        badPage.append(htmldata(htmldata::text, "WARNING: THE PAGE DOES NOT CONTAIN ANY TAGS", ""));
        return badPage;
    }

    return makeTagsGeneric(addCssToTagData(parseTags(html)));
    qDebug() <<"done parsing";
}

//Gets the Correct Font Size when passed in data
int parser::getFontSizeFromData(htmldata data, int defaultSize){
    QString cssData;
    QString output;
    float fout;

    int indexOfFontSize;
    int indexOfFontSizeEnd;

    cssData = getcssfromdata(data.data);

    indexOfFontSize = cssData.indexOf("font-size:") + 11;
    indexOfFontSizeEnd = cssData.indexOf("em", indexOfFontSize);

    for(int i = indexOfFontSize; i < indexOfFontSizeEnd; i++){
        output.append(cssData.at(i));
    }

    fout = output.toFloat() * defaultSize;

    qDebug() << output;

    return fout;
}

