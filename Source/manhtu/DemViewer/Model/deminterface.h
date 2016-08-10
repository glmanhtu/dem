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
};

#endif // DEMINTERFACE_H
