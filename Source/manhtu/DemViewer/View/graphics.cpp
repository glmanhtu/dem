#include "View/graphics.h"
#include "ui_widget.h"

Graphics::Graphics(QWidget *parent) : QOpenGLWidget(parent), ui(new Ui::Graphics)
{
    ui->setupUi(this);  
    this->parent = parent;
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
    delete ui;
}
