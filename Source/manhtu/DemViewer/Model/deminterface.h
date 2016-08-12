#ifndef DEMINTERFACE_H
#define DEMINTERFACE_H

#include "gdal.h"
#include "gdal_priv.h"
#include "View/vertex.h"

class DemInterface
{
public:
    virtual void setDataSet(GDALDataset*) = 0;
    virtual GDALDataset* getDataSet() = 0;
    virtual void addVertex(Vertex ver) = 0;
    virtual float* getVertexArray() = 0;
    virtual int getNumberOfVertex() = 0;
    virtual int getCols()=0;
    virtual int getRows() = 0;
    virtual float maxHeight() = 0;
    virtual float minHeight() = 0;
    virtual float setMaxHeight(float max)=0;
    virtual float setMinHeight(float min)=0;
    virtual float heightScale(float height) = 0;
};

#endif // DEMINTERFACE_H
