#include "View/graphics.h"
#include <QMouseEvent>
#include <QDebug>
#include <QOpenGLShaderProgram>

QSize Graphics::getSize()
{
    return this->size();
}

Graphics::Graphics(QWidget *parent) : QOpenGLWidget(parent)
{
    this->parent = parent;
    xRot = 0;
    yRot = 0;
    zRot = 0;
    setAutoFillBackground(false);
}

void Graphics::updateGraphics()
{
    initializeGL();
    update();
}

void Graphics::setSize(int width, int height)
{
    if (width < this->width()) {
        width = this->width();
    }
    if (height < this->height()) {
        height = this->height();
    }
    setFixedSize(width, height);
}

void Graphics::initial()
{
    QMenuBar *menu = new QMenuBar(parent);
    registerMenu(menu);
}

void Graphics::initializeGL()
{    

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    static GLfloat lightPosition[4] = { 0, 0, 10, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    for(int i=0; i<graphics.size(); i++) {
        graphics[i]->initializeGL();
    }

    int numbVertex = demObject->countVertexs();
    if (numbVertex > 0) {
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*numbVertex, demObject->getArrayVertexs(), GL_STATIC_DRAW);
    }
}

void Graphics::addVertex(Vertex vertex)
{
    demObject->addVertex(vertex);
}

void Graphics::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -10.0);
    glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
    glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
    glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);

    for(int i=0; i<graphics.size(); i++) {
        graphics[i]->paintGL();
    }            

    int numbVertex = demObject->countVertexs();

    if (numbVertex > 0) {

        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);

        glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (void*)Vertex::positionOffset());
        glColorPointer(3, GL_FLOAT, sizeof(Vertex), (void*)Vertex::colorOffset());
        glDrawArrays(GL_TRIANGLES, 0, numbVertex);

        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
    }
}

void Graphics::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

#ifdef QT_OPENGL_ES_1
    glOrthof(-1.5, +1.5, -1.5, +1.5, 1.0, 15.0);
#else
    glOrtho(-1.5, +1.5, -1.5, +1.5, 1.0, 15.0);
#endif
    glMatrixMode(GL_MODELVIEW);

    for(int i=0; i<graphics.size(); i++) {
        graphics[i]->resizeGL(width, height);
    }
}

QSize Graphics::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize Graphics::sizeHint() const
{
    return QSize(400, 400);
}

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360)
        angle -= 360 * 16;
}

void Graphics::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != xRot) {
        xRot = angle;
        emit xRotationChanged(angle);
        update();
    }
}

void Graphics::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        emit yRotationChanged(angle);
        update();
    }
}

void Graphics::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
        emit zRotationChanged(angle);
        update();
    }
}

void Graphics::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void Graphics::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(xRot + 8 * dy);
        setYRotation(yRot + 8 * dx);
    } else if (event->buttons() & Qt::RightButton) {
        setXRotation(xRot + 8 * dy);
        setZRotation(zRot + 8 * dx);
    }

    lastPos = event->pos();
}

Graphics::~Graphics()
{

}
