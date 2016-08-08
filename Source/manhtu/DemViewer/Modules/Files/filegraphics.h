#ifndef FILEGRAPHICS_H
#define FILEGRAPHICS_H

#include "View/graphicscomposite.h"
#include "filecontroller.h"
#include "View/vertex.h"

class FileGraphics : public GraphicsComposite
{
private:
    const int GRAPHICS_ID = 0;
    FileController* fcontroller;
    vector<float> data_paint;
    vector<Vertex> data_vertex;
    GLuint VertexArrayID,vertexbuffer;
    unsigned int vbo;

public:
    FileGraphics();
    ~FileGraphics();
    // GraphicsComposite interface
public:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

public:
    void initial();
};

class ColorRGBA
{
public:
    float r;
    float g;
    float b;
    float a;

    ColorRGBA(){}
};

#endif // FILEGRAPHICS_H
