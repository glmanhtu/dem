#include "rotategraphics.h"
#include <QMouseEvent>

RotateGraphics::RotateGraphics()
{
    xRot = -960;
    yRot = 352;
    zRot = 0;
}


void RotateGraphics::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void RotateGraphics::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(xRot + 8 * dy);
        setYRotation(yRot + 8 * dx);
    }

    lastPos = event->pos();
}

void RotateGraphics::mouseDoubleClickEvent(QMouseEvent *event)
{
}

void RotateGraphics::initial()
{
}

void RotateGraphics::initializeGL()
{
}

void RotateGraphics::paintGL()
{
    glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
    glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
    glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);
}

void RotateGraphics::resizeGL(int width, int height)
{
}

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360)
        angle -= 360 * 16;
}

void RotateGraphics::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != xRot) {
        xRot = angle;
        updatePaintGL();
    }
}

void RotateGraphics::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        updatePaintGL();
    }
}

void RotateGraphics::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
        updatePaintGL();
    }
}
