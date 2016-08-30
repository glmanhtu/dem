#include "movegraphics.h"
#include <QMouseEvent>

MoveGraphics::MoveGraphics()
{
}


void MoveGraphics::mousePressEvent(QMouseEvent *event)
{    
    lastPos = event->pos();
}
void MoveGraphics::mouseReleaseEvent(QMouseEvent *event)
{
}

void MoveGraphics::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::RightButton) {
        int distanceX = event->x() - lastPos.x();
        int distanceY = event->y() - lastPos.y();
        if (abs(distanceX) < abs(distanceY)) {
            y -= distanceY * 0.0001;
        } else {
            x += distanceX * 0.0001;
        }
        updatePaintGL();
    }
}

void MoveGraphics::mouseDoubleClickEvent(QMouseEvent *)
{
}

void MoveGraphics::initial()
{
}

void MoveGraphics::initializeGL()
{
}

void MoveGraphics::paintGL()
{    
    glTranslatef(0.0+x, 0.0+y, -10.0);
}

void MoveGraphics::resizeGL(int , int )
{
}
