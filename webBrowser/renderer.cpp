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

bool pageRendered;

renderer::renderer()
{
    pageRendered = false;
}


void renderer::renderPage(QScrollArea* displayArea, QVector<htmldata> taglist){

    QFrame f = QFrame();

    QBoxLayout box = QBoxLayout(QBoxLayout::TopToBottom);

    for(htmldata d : taglist){
        if(d.gettag() == htmldata::text){
            //leaky memmory time
            QLabel l = QLabel(d.getcontents());
            l.setWordWrap(true);
            //set css data
            box.addWidget(&l);
        }
        else if(d.gettag() == htmldata::link){
            QPushButton b = QPushButton();
            b.text().append(d.contents);
            //makes button load new page
            QString link = htmldata::getlinkfromdata(d.getdata());
//            QObject::connect(&b, &QPushButton::clicked, [window, link](){
//                window->loadPage(link);
//            });
            box.addWidget(&b);
        }
        else if(d.gettag() == htmldata::image){
            //figure this out
        }
        else if(d.gettag() == htmldata::other){
            //do nothing
        }
        else{
            qDebug() << "invalid tag type";
        }
    }

    f.setLayout(QVBoxLayout());
    box.setParent(&f);

    displayArea->setWidget(&f);

    displayArea->show();

    qDebug() << "shown";
    pageRendered = true;
}
