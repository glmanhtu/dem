#ifndef DEMINTERFACE_H
#define DEMINTERFACE_H

#include "gdal.h"
#include "gdal_priv.h"
#include "View/vertex.h"

class DemInterface
{
public:
    static const int DIRECTION_NORTH = 0;
    static const int DIRECTION_WEST = 1;
    static const int DIRECTION_SOUTH = 2;
    static const int DIRECTION_EAST = 3;
    virtual void setDataSet(GDALDataset*) = 0;
    virtual GDALDataset* getDataSet() = 0;
    virtual void addVertex(Vertex ver, int position) = 0;
    virtual int getCols()=0;
    virtual int getRows() = 0;
    virtual float maxHeight() = 0;
    virtual float minHeight() = 0;
    virtual float setMaxHeight(float max)=0;
    virtual float setMinHeight(float min)=0;
    virtual float heightScale(float height) = 0;
    virtual int getVertexPositionIn2D(int col, int row, bool northeast)=0;
    virtual Vertex* getArrayVertexs()=0;
    virtual int* getVertexIndices() = 0;
    virtual int countIndices()=0;
    virtual int countVertexs()=0;
    virtual std::vector<float> readDem()=0;
    virtual int getZoom() = 0;
    virtual void clean() = 0;
    virtual int getVertexPosition(int col, int row)=0;
    virtual int getVertexPosition(int col, int row, int layer, int direction)=0;
};

#endif // DEMINTERFACE_H
