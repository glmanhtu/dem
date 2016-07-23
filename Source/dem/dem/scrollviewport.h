#ifndef SCROLLVIEWPORT_H
#define SCROLLVIEWPORT_H

#include <QScrollArea>
#include <QWidget>

class ScrollViewport : public QScrollArea
{
public:
    ScrollViewport(QWidget * parent);
    ~ScrollViewport();
protected:
    void resizeEvent(QResizeEvent * event) override;
    void paintEvent(QPaintEvent *event) override;
};

#endif // SCROLLVIEWPORT_H
