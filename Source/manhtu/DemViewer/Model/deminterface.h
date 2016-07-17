#ifndef DEMINTERFACE_H
#define DEMINTERFACE_H

#include "gdal.h"
#include "gdal_priv.h"

class DemInterface
{
public:
    virtual void setDataSet(GDALDataset*) = 0;
    virtual GDALDataset* getDataSet() = 0;
};

#endif // DEMINTERFACE_H
