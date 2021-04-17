#include "parser.h"

parser::parser()
{

}

struct parser::tagData{
    QString tagtype;
    QString tagData;
    QString tagContence;

   friend std::ostream& operator<<(std::ostream &os, const struct tagData &str){
      return os << "type: " + str.tagtype.toUtf8().toStdString() + " data: " + str.tagData.toUtf8().toStdString() + " contence: " + str.tagContence.toUtf8().toStdString() << std::endl;
       //return os;
   }

   operator QString() const {
       return "type: " + tagtype + " data: " + tagData + " contence: " + tagContence + "\n";
   }
};

QString parser::getlinkfromdata(QString data){
    return "todo";
};

QString parser::getsrcfromdata(QString data){
    return "todo";
};

QString parser::getcssfromdata(QString data){
    return "todo";
};

QString parser::getCssForTagType(QString tagType){
    return "todo";
}

//turns the html into a list of tags
//this is BAD and DUMB
QVector<parser::tagData> parser::parseTags(QString html){
    qDebug() << "parsing tags";

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
                    }
                    else if(inTagContence && !tagOver){
                        tagContence.last().append(c);
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
                }
                else if(inTagContence && !tagOver){
                    tagContence.last().append(c);
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
                    if(tagOver || (currentTag.last() == "img")){
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

                        qDebug() << "added tag of type: " + tag->tagtype;
                    }
                    else{
                        qDebug() << "tag not added";
                    }
                }

                //if not a closing for a tag add it to the data or contense
                else{
                    if(inTagContence && !tagOver){
                        tagContence.last().append(c);
                    }
                    else if(inTagData && !tagOver){
                        tagData.last().append(c);
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
                }
                else if(inTagContence && !tagOver){
                    tagContence.last().append(c);
                }
                else if(inTagData && !tagOver){
                    tagData.last().append(c);
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
            }
            else if(inTagContence && !tagOver){
                tagContence.last().append(c);
            }
            else if(inTagData && !tagOver){
                tagData.last().append(c);
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
    qDebug() << "IMPLIMENT TAG CSS ADDING";

    //IMPLIMENT THIS
    return tags;
}

//makes the raw tags into the generic tags that can be rendered
QVector<htmldata> parser::makeTagsGeneric(QVector<parser::tagData> tags){
    qDebug() << "makign tags generic";

    QVector<QString> textTags = {"p", "abbr", "adress", "b", "bdi", "bdo", "blockquote", "caption", "cite", "del", "em", "h1", "h2", "h3", "h4", "h5", "h6", "q", "rt", "s", "small", "span", "sub", "sup", "var"};
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

