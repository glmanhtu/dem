#include "demobject.h"

DemObject::DemObject()
{
//    float f[] = { 0 , 2 , - 4 , 1 , 0 , 0 , - 2 , - 2 , - 4 , 0 , 1 , 0 , 2 , - 2 , - 4 , 0 , 0 , 1 } ;
//    for (int i=0; i<18; i++) {
//        data.push_back(f[i]);
//    }
}

GDALDataset* DemObject::getDataSet()
{
    return dataSet;
}

void DemObject::setDataSet(GDALDataset *ds)
{
    dataSet = ds;
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
