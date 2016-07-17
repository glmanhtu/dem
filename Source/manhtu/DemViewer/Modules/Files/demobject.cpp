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
}
