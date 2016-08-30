#include "demobject.h"
#include "gdal.h"
#include "gdal_priv.h"

DemObject::DemObject()
{
    zooomStep = 1;    
}

GDALDataset* DemObject::getDataSet()
{
    return dataSet;
}

void DemObject::setDataSet(GDALDataset *ds)
{
    dataSet = ds;    
    oriCols = dataSet->GetRasterXSize();
    oriRows = dataSet->GetRasterYSize();
    readStep = oriCols/600;
    if (readStep == 0) readStep = 1;
    cols = oriCols/readStep;
    rows = oriRows/readStep;    
    if (readStep > 1) {
        cols++;
        rows++;
    }
}


void DemObject::addVertex(Vertex vertex, int position)
{
    int currentPosition = vertexs.size() - 1;
    if (position > currentPosition) {
        vertexs.push_back(vertex);        
    } else {
        vertexs[position].setNormal(QVector3D::normal(vertex.normal(), vertexs[position].normal()));
    }
    ind.push_back(position);
}


int DemObject::getCols()
{
    return cols;
}

int DemObject::getRows()
{
    return rows;
}


float DemObject::maxHeight()
{
    return maxH;
}

float DemObject::minHeight()
{
    return minH;
}

float DemObject::setMaxHeight(float max)
{
    maxH = max;
    return max;
}

float DemObject::setMinHeight(float min)
{
    minH = min;
    return min;
}


float DemObject::heightScale(float height)
{
    return height/6000;
}

Vertex *DemObject::getArrayVertexs()
{
    return vertexs.data();
}


int DemObject::countVertexs()
{
    return vertexs.size();
}


std::vector<float> DemObject::readDem()
{
    GDALRasterBand* band = dataSet->GetRasterBand(1);
    std::vector<float> band_data;
    for (int i=0; i<oriRows; i=i+readStep) {
        std::vector<float> tmpData(oriCols);
        band->RasterIO( GF_Read, 0, i,
                        oriCols, 1,
                        tmpData.data(),
                        oriCols, 1,
                        GDT_Float32,
                        0, 0);
        for (int j=0; j<oriCols;j = j+readStep) {
            band_data.push_back(tmpData[j]);
            if (maxH < tmpData[j])
                maxH = tmpData[j];
            if (minH > tmpData[j])
                minH = tmpData[j];
        }
    }    
    return band_data;
}


int DemObject::getZoom()
{
    return zooomStep;
}


void DemObject::clean()
{

}


int DemObject::getVertexPosition(int x, int y)
{
    int scaledCols = (cols - 1)/zooomStep;
    x= x/zooomStep;
    y= y/zooomStep;
    if (x == 0 && y == 0) {
        return 2;
    }

    if (y == 0 && x == 1) {
        return 0;
    }

    if (y == 1 && x == 0) {
        return 2*scaledCols + 1;
    }

    if (y == 1 && x == 1) {
        return 1;
    }

    if (y <= 1 && x > 1) {
        return 2*x - 1 + y;
    }

    if (y > 1 && x == 0) {
        return (y + 1) * scaledCols + y;
    }

    if (y > 1 && x > 0) {
        return y*scaledCols + y + x - 1;
    }
    return 0;
}


int *DemObject::getVertexIndices()
{
    return ind.data();
}


int DemObject::countIndices()
{
    return ind.size();
}


int DemObject::getVertexPosition(int x, int y, int layer, int direction)
{
    int scaledCols = (cols - 1)/zooomStep;
    int scaledRows = (rows - 1)/zooomStep;
    x= x/zooomStep;
    y= y/zooomStep;

    switch (direction) {
    case DemInterface::DIRECTION_NORTH:        
        return (scaledRows + 1)* scaledCols + scaledRows + layer + x;
        break;
    case DemInterface::DIRECTION_SOUTH:
        return  (scaledRows + 1)* scaledCols + scaledRows + layer + scaledCols + x + 1;
        break;
    case DemInterface::DIRECTION_WEST:        
        return (scaledRows + 1)* scaledCols + scaledRows + layer + 2*scaledCols + y + 1;
        break;
    case DemInterface::DIRECTION_EAST:        
        return (scaledRows + 1)* scaledCols + scaledRows + layer + 2*scaledCols + scaledRows +2 + y;
        break;
    default:
        break;
    }
    return 0;
}
