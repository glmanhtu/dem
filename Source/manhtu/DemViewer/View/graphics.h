#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "graphicscomposite.h"
#include "menu.h"
#include <QWidget>
#include "scrollviewport.h"

class Graphics : public QOpenGLWidget, public GraphicsComposite
{
    Q_OBJECT
    friend class ScrollViewport;
private:
    const int GRAPHICS_ID = 0;
    QWidget *parent;

public:
    Graphics(QWidget *parent = 0);
    void initial() Q_DECL_OVERRIDE;
    void setSize(int, int) Q_DECL_OVERRIDE;
    void updateGraphics() Q_DECL_OVERRIDE;
    ~Graphics();
protected:
    void initializeGL() Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;
    void resizeGL(int width, int height) Q_DECL_OVERRIDE;
};

#endif // GRAPHICS_H
