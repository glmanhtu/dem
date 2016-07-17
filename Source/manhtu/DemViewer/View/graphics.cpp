#include "View/graphics.h"
#include <QGridLayout>
#include <QScrollArea>

Graphics::Graphics(QWidget *parent) : QOpenGLWidget(parent)
{
    this->parent = parent;
    setAutoFillBackground(false);
}

void Graphics::updateGraphics()
{
    update();
    QScrollArea* scroll = (QScrollArea*)this->parentWidget();
    scroll->update();
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
    for(int i=0; i<graphics.size(); i++) {
        graphics[i]->initializeGL();
    }
}

void Graphics::paintGL()
{
    for(int i=0; i<graphics.size(); i++) {
        graphics[i]->paintGL();
    }
}

void Graphics::resizeGL(int width, int height)
{
    for(int i=0; i<graphics.size(); i++) {
        graphics[i]->resizeGL(width, height);
    }
}

Graphics::~Graphics()
{

}
