#ifndef DEMOBJECT_H
#define DEMOBJECT_H

#include "Model/deminterface.h"

class DemObject : public DemInterface
{
private:
    GDALDataset* dataSet;
    std::vector<float> data;
public:
    DemObject();

    // DemInterface interface
public:
    void setDataSet(GDALDataset *) override;
    GDALDataset *getDataSet() override;

    // DemInterface interface
public:
    void addVertex(Vertex ver);
    float *getVertexArray();
    int getNumberOfVertex();
};

#endif // DEMOBJECT_H
