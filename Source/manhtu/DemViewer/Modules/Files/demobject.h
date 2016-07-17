#ifndef DEMOBJECT_H
#define DEMOBJECT_H

#include "Model/deminterface.h"

class DemObject : public DemInterface
{
private:
    GDALDataset* dataSet;
public:
    DemObject();

    // DemInterface interface
public:
    void setDataSet(GDALDataset *) override;
    GDALDataset *getDataSet() override;
};

#endif // DEMOBJECT_H
