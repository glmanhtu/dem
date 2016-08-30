#ifndef ZOOMGRAPHICS_H
#define ZOOMGRAPHICS_H

#include "View/graphicscomposite.h"

class ZoomGraphics: public GraphicsComposite
{

private:
    float zoomByScale;
    QPoint lastPos;
public:
    ZoomGraphics();

    // GraphicsComposite interface
public:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void initial();
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void changeZoom();
    void wheelEvent(QWheelEvent *);
};

#endif // ZOOMGRAPHICS_H
