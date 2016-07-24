#include "scrollviewport.h"
#include "glwidget.h"

ScrollViewport::ScrollViewport(QWidget * parent) : QScrollArea(parent)
{

}

ScrollViewport::~ScrollViewport()
{

}

void ScrollViewport::resizeEvent(QResizeEvent *event)
{
    GLWidget * glw = dynamic_cast<GLWidget *>(viewport());
    glw->resizeEvent(event);
}

void ScrollViewport::paintEvent(QPaintEvent *event)
{
    GLWidget * glw = dynamic_cast<GLWidget *>(viewport());
    glw->paintEvent(event);
}
