#include "zoomgraphics.h"
#include <QMouseEvent>

ZoomGraphics::ZoomGraphics()
{
    zoomByScale = 0.65;
}

void ZoomGraphics::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void ZoomGraphics::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::RightButton) {
        if (lastPos.x() < event->x()) {
            if (zoomByScale < 1.2) {
                zoomByScale += 0.01;
                updatePaintGL();
            }
        } else {
            if (zoomByScale > 0.65) {
                zoomByScale -= 0.01;
                updatePaintGL();
            }
        }
    }
}

void ZoomGraphics::mouseDoubleClickEvent(QMouseEvent *e)
{
    if ( e->button() == Qt::LeftButton ) {
        if (zoomByScale < 1.2) {
            zoomByScale += 0.05;
            updatePaintGL();
        }
    }
    if (e->button() == Qt::RightButton) {
        if (zoomByScale > 0.65) {
            zoomByScale -= 0.05;
            updatePaintGL();
        }
    }
}

void ZoomGraphics::initial()
{
}

void ZoomGraphics::initializeGL()
{
}

void ZoomGraphics::paintGL()
{
    glScalef(zoomByScale,zoomByScale,zoomByScale);
}

void ZoomGraphics::resizeGL(int width, int height)
{
}
