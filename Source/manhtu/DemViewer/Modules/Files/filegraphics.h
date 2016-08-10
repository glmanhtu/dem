#ifndef FILEGRAPHICS_H
#define FILEGRAPHICS_H

#include "View/graphicscomposite.h"
#include "filecontroller.h"
#include "View/vertex.h"

class ColorRGBA
{
public:
    float r;
    float g;
    float b;    

    ColorRGBA(){}
    ColorRGBA(float red, float green, float blue){
        r = red;
        g = green;
        b = blue;
    }

    float red(){
        return r;
    }
    float green()
    {
        return g;
    }
    float blue()
    {
        return b;
    }
};

class FileGraphics : public GraphicsComposite
{
private:
    const int GRAPHICS_ID = 0;
    FileController* fcontroller;
    vector<float> data_paint;
    vector<Vertex> data_vertex;
    GLuint VertexArrayID,vertexbuffer;
    float maxZ;
    float scale;
    vector<ColorRGBA> data_colors;
    float getZCoordinate(float height);
    void addColor(ColorRGBA color1, ColorRGBA color2, int step);
    unsigned int vbo;
    ColorRGBA getColor(float height);

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

#endif // FILEGRAPHICS_H
