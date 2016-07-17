#include "scrollviewport.h"
#include "graphics.h"

ScrollViewport::ScrollViewport(QWidget * parent) : QScrollArea(parent)
{

}

ScrollViewport::~ScrollViewport()
{

}

void ScrollViewport::resizeEvent(QResizeEvent *event)
{
    Graphics * glw = dynamic_cast<Graphics *>(viewport());
    glw->resizeEvent(event);
}

void ScrollViewport::paintEvent(QPaintEvent *event)
{
    Graphics * glw = dynamic_cast<Graphics *>(viewport());
    glw->paintEvent(event);
}
