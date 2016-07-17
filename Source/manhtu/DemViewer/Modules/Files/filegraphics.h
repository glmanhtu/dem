#ifndef FILEGRAPHICS_H
#define FILEGRAPHICS_H

#include "View/graphicscomposite.h"
#include "filecontroller.h"

class FileGraphics : public GraphicsComposite
{
private:
    const int GRAPHICS_ID = 0;
    FileController* fcontroller;
public:
    FileGraphics();
    ~FileGraphics();
    // GraphicsComposite interface
public:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

    // GraphicsComposite interface
public:
    void initial();
};

#endif // FILEGRAPHICS_H
