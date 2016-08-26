#include "View/graphics.h"
#include <QMouseEvent>
#include <QDebug>
#include <QOpenGLShaderProgram>

QSize Graphics::getSize()
{
    return this->size();
}

void Graphics::updatePaintGL()
{
    update();
}

Graphics::Graphics(QWidget *parent) : QOpenGLWidget(parent)
{
    this->parent = parent;    
    setAutoFillBackground(false);
    zoomByScale = 0.65;
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
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
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
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glLoadIdentity();
    glScalef(zoomByScale,zoomByScale,zoomByScale);
    glTranslatef(0.0, 0.0, -10.0);      

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
    float aspectRatio = (float)width/(float)height;
    glOrtho(-aspectRatio, aspectRatio, -1, 1, 1.0, 15.0);
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

void Graphics::mousePressEvent(QMouseEvent *event)
{
    for(int i=0; i<graphics.size(); i++) {
        graphics[i]->mousePressEvent(event);
    }
    lastPos = event->pos();
}

void Graphics::mouseMoveEvent(QMouseEvent *event)
{
    for(int i=0; i<graphics.size(); i++) {
        graphics[i]->mouseMoveEvent(event);
    }
    if (event->buttons() & Qt::RightButton) {
        if (lastPos.x() < event->x()) {
            if (zoomByScale < 1.5) {
                zoomByScale += 0.01;
                update();
            }
        } else {
            if (zoomByScale > 0.65) {
                zoomByScale -= 0.01;
                update();
            }
        }
    }    
    lastPos = event->pos();
}

void Graphics::mouseDoubleClickEvent(QMouseEvent *e)
{
    for(int i=0; i<graphics.size(); i++) {
        graphics[i]->mouseDoubleClickEvent(e);
    }
    if ( e->button() == Qt::LeftButton ) {
        if (zoomByScale < 1.5) {
            zoomByScale += 0.05;
            update();
        }
    }
    if (e->button() == Qt::RightButton) {
        if (zoomByScale > 0.65) {
            zoomByScale -= 0.05;
            update();
        }
    }
}

Graphics::~Graphics()
{
    glDeleteBuffers(1, &vbo);
}
