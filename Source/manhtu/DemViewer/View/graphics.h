#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "graphicscomposite.h"
#include "menu.h"
#include <QWidget>

namespace Ui {
    class Graphics;
}

class Graphics : public QOpenGLWidget, public GraphicsComposite
{
    Q_OBJECT
private:
    const int GRAPHICS_ID = 0;
    QWidget *parent;
    Ui::Graphics *ui;

public:
    explicit Graphics(QWidget *parent = 0);
    void initial() override;
    ~Graphics();
protected:
    void initializeGL() Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;
    void resizeGL(int width, int height) Q_DECL_OVERRIDE;
};

#endif // GRAPHICS_H
