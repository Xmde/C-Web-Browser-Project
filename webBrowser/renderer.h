#ifndef RENDERER_H
#define RENDERER_H

#include <QScrollArea>
#include <QVector>
#include <htmldata.h>
#include <mainwindow.h>
#include <QObject>

class renderer : public QObject
{
public:
    bool readyToLoadNewImage;
    bool imageLoaded;
    renderer();
    void renderPage(QScrollArea* displayArea, QVector<htmldata> tags, class MainProgramWindow* window, QString site);
    QByteArray getImage(QString urlBase, QString imgUrl);
private slots:
 void loadImage();
};

#endif // RENDERER_H
