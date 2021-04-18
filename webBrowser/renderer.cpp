#define CPPHTTPLIB_OPENSSL_SUPPORT

#include "renderer.h"
#include <htmldata.h>
#include <QBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <mainwindow.h>
#include <QObject>
#include <QWidget>
#include <QFrame>
#include <QDebug>
#include <QSpacerItem>
#include "filedownloader.h"
#include "httplib.h"

bool pageRendered;

renderer::renderer()
{
    pageRendered = false;
}

void renderer::renderPage(QScrollArea* displayArea, QVector<htmldata> taglist, class MainProgramWindow* window){

    if(pageRendered){
        //less memmory leaks?
        for(QObject* x : displayArea->children().at(0)->children()){
            delete x;
        }
    }

    QFrame* frame = new QFrame();

    frame->setFrameStyle(QFrame::Box | QFrame::Plain);
    frame->setLineWidth(2);
    frame->setStyleSheet("QFrame {background-color:white;}");

    QVBoxLayout* box = new QVBoxLayout();

    box->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    box->setSpacing(3);

//    box->minimumSize();

//    box->setSizeConstraint(QLayout::SetMinimumSize);

    for(htmldata d : taglist){
        if(d.gettag() == htmldata::text){
            //leaky memmory time
            QLabel* l = new QLabel(d.getcontents());
            l->setMinimumWidth(760);
            l->setWordWrap(true);
            //set css data
            l->setStyleSheet(parser::getcssfromdata(d.getdata()));
            box->addWidget(l);
            //box->addSpacerItem(new QSpacerItem(10, 2));
        }
        else if(d.gettag() == htmldata::link){
            QPushButton* b = new QPushButton(d.getcontents());
            b->setVisible(true);
            //makes it look like a link
            b->setStyleSheet(parser::getcssfromdata(d.getdata()) + " color:blue; border: none; text-align: left; text-decoration: underline;");
            //makes button load new page
            QString link = parser::getlinkfromdata(d.getdata());
            //the leakyest memmory
            window->ConnectButtonToLink(b, link);
            box->addWidget(b);
            //box->addSpacerItem(new QSpacerItem(10, 2));
        }
        else if(d.gettag() == htmldata::image){


        }
        else if(d.gettag() == htmldata::other){
            //do nothing
        }
        else{
            qDebug() << "WARNING: invalid tag type parsed";
        }
    }

    //qDebug() << box->children();

    frame->setLayout(box);

    //qDebug() <<frame->children();
    frame->setMinimumWidth(760);

    displayArea->setWidget(frame);
    displayArea->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    displayArea->show();

    //qDebug() << "shown";

    pageRendered = true;
}

void renderer::getImage(QString urlBase, QString imgUrl){
    //QUrl imageUrl(urlBase+imgUrl);
}
