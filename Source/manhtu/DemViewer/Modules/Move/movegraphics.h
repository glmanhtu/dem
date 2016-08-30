#ifndef MOVEGRAPHICS_H
#define MOVEGRAPHICS_H

#include "View/graphicscomposite.h"
#include <GLUT/glut.h>
#include <glm.h>

class MoveGraphics : public GraphicsComposite
{
private:
    QPoint lastPos;
    float mouseSpeed = 0.005f;
    float deltaAngle = 0.0f;
    float deltaMove = 0;
    // actual vector representing the camera's direction
    float lx=0.0f,lz=-1.0f;
    int xOrigin = -1;
    float angle=0.0;
    float x=0,y=0,z=0;
    // horizontal angle : toward -Z
    float horizontalAngle = 0.0f;
    // vertical angle : 0, look at the horizon
    float verticalAngle = 0.0f;

public:
    MoveGraphics();

    // GraphicsComposite interface
public:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void initial();
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void mouseReleaseEvent(QMouseEvent *);
};

#endif // MOVEGRAPHICS_H
