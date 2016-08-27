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


    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    // enable color tracking
    glEnable(GL_COLOR_MATERIAL);
    // set material properties which will be assigned by glColor
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    // Create light components
    float ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    float diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f };
    float specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    float position[] = { -0.5f, 0.5f, 8.0f, 1.0f };

    // Assign created components to GL_LIGHT0
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    for(int i=0; i<graphics.size(); i++) {
        graphics[i]->initializeGL();
    }

    int numbVertex = demObject->countVertexs();
    if (numbVertex > 0) {
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*numbVertex, demObject->getArrayVertexs(), GL_STATIC_DRAW);

        glGenBuffers(1, &ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, demObject->countIndices() * sizeof(unsigned int), demObject->getVertexIndices(), GL_STATIC_DRAW);
    }    
}

void Graphics::addVertex(Vertex vertex, int col, int row)
{
    demObject->addVertex(vertex, demObject->getVertexPosition(col, row));
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
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);

        glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (void*)Vertex::positionOffset());
        glColorPointer(3, GL_FLOAT, sizeof(Vertex), (void*)Vertex::colorOffset());
        glNormalPointer(GL_FLOAT, sizeof(Vertex), (void*)Vertex::normalOffset());
        glDrawElements(GL_TRIANGLES, demObject->countIndices(), GL_UNSIGNED_INT, (void*)0);

        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
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
