#ifndef ROTATEGRAPHICS_H
#define ROTATEGRAPHICS_H

#include "View/graphicscomposite.h"
class RotateGraphics : public GraphicsComposite
{
private:    
    int xRot;
    int yRot;
    int zRot;
    QPoint lastPos;

public:    
    RotateGraphics();

    // GraphicsComposite interface
public:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void initial();
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
public slots:
    // slots for xyz-rotation slider
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);

};

#endif // ROTATEGRAPHICS_H
