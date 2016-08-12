#ifndef FILEGRAPHICS_H
#define FILEGRAPHICS_H

#include "View/graphicscomposite.h"
#include "filecontroller.h"
#include "View/vertex.h"
#include "Modules/Color/colorcontroller.h"
#include "Modules/BaseSupport/basesupportcontroller.h"

class FileGraphics : public GraphicsComposite
{
private:
    const int GRAPHICS_ID = 0;
    FileController* fcontroller;
    ColorController* colorController;
    BaseSupportController* bsController;
    vector<float> data_paint;
    vector<Vertex> data_vertex;    
    float maxZ,scale;
    float getZCoordinate(float height);        

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
