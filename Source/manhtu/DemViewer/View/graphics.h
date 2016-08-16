#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "graphicscomposite.h"
#include "menu.h"
#include <QOpenGLWidget>
#include "vertex.h"

class Graphics : public QOpenGLWidget, public GraphicsComposite
{
    Q_OBJECT    
private:
    const int GRAPHICS_ID = 0;
    QWidget *parent;
    unsigned int vbo, vbo2;
    float zoomByScale;

public:
    Graphics(QWidget *parent = 0);
    void initial() Q_DECL_OVERRIDE;
    void setSize(int, int) Q_DECL_OVERRIDE;
    void updateGraphics() Q_DECL_OVERRIDE;
    void addVertex(Vertex vertex) Q_DECL_OVERRIDE;
    QSize getSize() Q_DECL_OVERRIDE;
    ~Graphics();

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;

public slots:
    // slots for xyz-rotation slider
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);

signals:
    // signaling rotation from mouse movement
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);

private:
    void draw();

    int xRot;
    int yRot;
    int zRot;
    QPoint lastPos;
};

#endif // GRAPHICS_H
