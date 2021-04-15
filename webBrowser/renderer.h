#ifndef RENDERER_H
#define RENDERER_H

#include <QScrollArea>
#include <QVector>
#include <htmldata.h>

class renderer
{
public:
    renderer();
    void renderPage(QScrollArea* displayArea, QVector<htmldata> tags);

};

#endif // RENDERER_H
