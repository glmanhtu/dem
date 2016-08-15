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
    virtual int getCols()=0;
    virtual int getRows() = 0;
    virtual float maxHeight() = 0;
    virtual float minHeight() = 0;
    virtual float setMaxHeight(float max)=0;
    virtual float setMinHeight(float min)=0;
    virtual float heightScale(float height) = 0;    
    virtual int getVertexPositionIn2D(int col, int row, bool northeast)=0;
    virtual Vertex* getArrayVertexs()=0;
    virtual int countVertexs()=0;
    virtual std::vector<float> readDem()=0;
    virtual int getZoom() = 0;
};

#endif // DEMINTERFACE_H
