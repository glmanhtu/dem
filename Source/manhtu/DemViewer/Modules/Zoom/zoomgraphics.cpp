#include "zoomgraphics.h"
#include <QMouseEvent>

ZoomGraphics::ZoomGraphics()
{
    zoomByScale = 1.4;
}

void ZoomGraphics::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void ZoomGraphics::mouseMoveEvent(QMouseEvent*)
{    
}


void ZoomGraphics::mouseDoubleClickEvent(QMouseEvent *e)
{
    if ( e->button() == Qt::LeftButton ) {
        zoomByScale = zoomByScale/1.1;
    }
    if (e->button() == Qt::RightButton) {
        zoomByScale = zoomByScale*1.1;
    }
    setSize(getSize().width(), getSize().height());
}

void ZoomGraphics::initial()
{
}

void ZoomGraphics::initializeGL()
{
}

void ZoomGraphics::paintGL()
{    
}

void ZoomGraphics::resizeGL(int width, int height)
{    
        int side = qMin(width, height);
        glViewport(((width - side) / 2)*zoomByScale, ((height - side) / 2)*zoomByScale, side*zoomByScale, side*zoomByScale);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        float aspectRatio = (float)width/(float)height;
        glOrtho(-aspectRatio*zoomByScale, aspectRatio*zoomByScale, -1*zoomByScale, 1*zoomByScale, 1.0, 15.0);
        glMatrixMode(GL_MODELVIEW);
}

void ZoomGraphics::changeZoom()
{

}


void ZoomGraphics::wheelEvent(QWheelEvent *event)
{
    if (event->delta() > 0) {
        zoomByScale = zoomByScale*1.1;
    } else {
        zoomByScale = zoomByScale/1.1;
    }
    setSize(getSize().width(), getSize().height());
}
