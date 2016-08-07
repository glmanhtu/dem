#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "graphicscomposite.h"
#include "menu.h"
#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include "logo.h"
#include "scrollviewport.h"

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)

class Graphics : public QOpenGLWidget, protected QOpenGLFunctions, public GraphicsComposite
{
    Q_OBJECT
    friend class ScrollViewport;
private:
    const int GRAPHICS_ID = 0;
    QWidget *parent;
    DemInterface* demObject;
    void setupVertexAttribs();

    bool m_core;
    int m_xRot;
    int m_yRot;
    int m_zRot;
    QPoint m_lastPos;
    Logo m_logo;
    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer m_logoVbo;
    QOpenGLShaderProgram *m_program;
    int m_projMatrixLoc;
    int m_mvMatrixLoc;
    int m_normalMatrixLoc;
    int m_lightPosLoc;
    QMatrix4x4 m_proj;
    QMatrix4x4 m_camera;
    QMatrix4x4 m_world;
    bool m_transparent;

public slots:
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);
    void cleanup();

signals:
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);

public:
    Graphics(QWidget *parent = 0);
    QSize minimumSizeHint() const Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;
    void initial() Q_DECL_OVERRIDE;
    void setSize(int, int) Q_DECL_OVERRIDE;
    void updateGraphics() Q_DECL_OVERRIDE;
    void setDemObject(DemInterface*);
    ~Graphics();

protected:
    void initializeGL() Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;
    void resizeGL(int width, int height) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
};

#endif // GRAPHICS_H
