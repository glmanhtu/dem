#include "demobject.h"

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
    cols = dataSet->GetRasterXSize();
    rows = dataSet->GetRasterYSize();
}


void DemObject::addVertex(Vertex vertex)
{
    vertexs.push_back(vertex);    
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
    int scalesRows = (rows - 1)/zooomStep;
    int index = 0;
    if (!northeast) {
        if (row == scalesRows) {
            index = scalesRows*scaledCols*2-scaledCols + col;
        } else {
            index = (scaledCols + 2*(col + 1) -1) + row*scaledCols*2 - 1;
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
