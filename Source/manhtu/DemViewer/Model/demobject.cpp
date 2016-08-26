#include "demobject.h"
#include "gdal.h"
#include "gdal_priv.h"

DemObject::DemObject()
{
    zooomStep = 2;
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
    readStep = (oriCols-1) / 1200;
    cols = oriCols/readStep;
    rows = oriRows/readStep;
}


void DemObject::addVertex(Vertex vertex, int position)
{
    int currentPosition = vertexs.size() - 1;
    if (position > currentPosition) {
        vertexs.push_back(vertex);
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
}

float DemObject::setMinHeight(float min)
{
    minH = min;
}


float DemObject::heightScale(float height)
{
    return height/6000;
}

int DemObject::getVertexPositionIn2D(int col, int row, bool northeast)
{
    col = col/zooomStep;
    row = row/zooomStep;
    int scaledCols = (cols - 1)/zooomStep;
    int scaledRows = (rows - 1)/zooomStep;
    int index = 0;
    if (!northeast) {
        if (row == scaledRows - 1) {
            index = scaledRows*scaledCols*2-scaledCols + col;
        } else {
            index = (scaledCols + 2*(col + 1) -1) + row*scaledCols*2 -1;
        }
    }
    else {
        if (row == 0) {
            index = col;
        } else {
            index = (scaledCols + 2*(col + 1) -1) + (row-1)*scaledCols*2;
        }
    }

    return index*3;
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
        if (y == 0) {
            return (scaledRows + 1)* scaledCols + scaledRows + layer + x;
        }
        break;
    case DemInterface::DIRECTION_SOUTH:
        if (y == scaledRows) {
            return  (scaledRows + 1)* scaledCols + scaledRows + layer + scaledCols + x;
        }
        break;
    case DemInterface::DIRECTION_WEST:
        if (x == 0) {
            return (scaledRows + 1)* scaledCols + scaledRows + layer + 2*scaledCols + y;
        }
        break;
    case DemInterface::DIRECTION_EAST:
        if (x == scaledCols) {
            return (scaledRows + 1)* scaledCols + scaledRows + layer + 2*scaledCols + scaledRows -2 + y;
        }
        break;
    default:
        break;
    }
}
