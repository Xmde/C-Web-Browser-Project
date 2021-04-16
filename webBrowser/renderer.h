#ifndef RENDERER_H
#define RENDERER_H

#include <QScrollArea>
#include <QVector>
#include <htmldata.h>
#include <mainwindow.h>

class renderer
{
public:
    renderer();
    void renderPage(QScrollArea* displayArea, QVector<htmldata> tags, class MainProgramWindow* window);

};

#endif // RENDERER_H
