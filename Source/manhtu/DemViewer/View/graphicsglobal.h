#ifndef GRAPHICSGLOBAL_H
#define GRAPHICSGLOBAL_H
#include <QWidget>
#include "graphics.h"
#include <QGridLayout>
#include <QScrollArea>

namespace Ui {
class GraphicsGlobal;
}

class GraphicsGlobal : public QWidget
{
Q_OBJECT
private:
    Graphics * graphics;
    Ui::GraphicsGlobal *ui;
public:
    explicit GraphicsGlobal(QWidget *parent = 0);
    ~GraphicsGlobal();
    Graphics* getGraphicsWidget();
};
#endif // GRAPHICSGLOBAL_H
