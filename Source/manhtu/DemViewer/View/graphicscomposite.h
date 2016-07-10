#ifndef GRAPHICSCOMPISITE_H
#define GRAPHICSCOMPISITE_H

#include <QOpenGLWidget>
#include <QtOpenGL/qgl.h>
#include <iostream>
#include "Controller/actionlistener.h"
#include "menu.h"
#include <functional>

using namespace std;
class GraphicsComposite
{
protected:
    GraphicsComposite* graphicsMain;
    vector<GraphicsComposite*> graphics;
    ActionListener actions;
    vector<Menu*> menus;
    const int GRAPHICS_ID = -1;

public:
    void setMainGraphics(GraphicsComposite*);
    void setActionPerform(ActionListener action);
    ActionInterface* getAction(QString);
    void registerGraphics(GraphicsComposite* graphic);
    int addToGraphicsComponent();
    bool addMenu(QString menuName, QAction *action);
    bool registerMenu(QMenuBar*);
    QAction* createQAction( QString name );

public:
    virtual void initial() = 0;
    virtual void initializeGL() = 0;
    virtual void paintGL() =0 ;
    virtual void resizeGL(int width, int height) = 0;
};
#endif // GRAPHICSCOMPISITE_H
