#ifndef GRAPHICSCOMPISITE_H
#define GRAPHICSCOMPISITE_H

#include <QOpenGLWidget>
#include <QtOpenGL/qgl.h>
#include <iostream>
#include "Controller/actionlistener.h"
#include "menu.h"
#include <functional>
#include "vertex.h"

using namespace std;
class GraphicsComposite
{
protected:
    GraphicsComposite* graphicsMain;
    vector<GraphicsComposite*> graphics;
    ActionListener* actions;
    vector<Menu*> menus;
    const int GRAPHICS_ID = -1;
    DemInterface* demObject;

public:
    void setMainGraphics(GraphicsComposite*);
    GraphicsComposite* getMainGraphics();
    void setActionPerform(ActionListener* action);
    ActionInterface* getAction(QString);
    void registerGraphics(GraphicsComposite* graphic);
    int addToGraphicsComponent();
    bool addMenu(QString menuName, QAction *action);
    bool registerMenu(QMenuBar*);
    virtual void setSize(int width, int height);
    virtual void updateGraphics();
    virtual void updatePaintGL();
    QAction* createQAction( QString name );
    virtual void addVertex(Vertex vertex);
    void setDemObject(DemInterface* dem);
    virtual QSize getSize();
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseDoubleClickEvent(QMouseEvent *event);

public:
    virtual void initial() = 0;
    virtual void initializeGL() = 0;
    virtual void paintGL() =0 ;
    virtual void resizeGL(int width, int height) = 0;
};
#endif // GRAPHICSCOMPISITE_H
