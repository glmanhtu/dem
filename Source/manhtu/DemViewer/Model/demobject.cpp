#include "demobject.h"

DemObject::DemObject()
{
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
    data.push_back(vertex.position().x());
    data.push_back(vertex.position().y());
    data.push_back(vertex.position().z());
    data.push_back(vertex.color().x());
    data.push_back(vertex.color().y());
    data.push_back(vertex.color().z());
}

float *DemObject::getVertexArray()
{
    return data.data();
}

int DemObject::getNumberOfVertex()
{
    return data.size();
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
