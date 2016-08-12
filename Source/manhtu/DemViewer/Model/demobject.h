#ifndef DEMOBJECT_H
#define DEMOBJECT_H

#include "Model/deminterface.h"

class DemObject : public DemInterface
{
private:
    GDALDataset* dataSet;
    std::vector<float> data;
    int cols, rows;
    float maxH, minH;
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

    // DemInterface interface
public:
    int getCols();
    int getRows();

    // DemInterface interface
public:
    float maxHeight();
    float minHeight();

    // DemInterface interface
public:
    float setMaxHeight(float max);
    float setMinHeight(float min);

    // DemInterface interface
public:
    float heightScale(float height);
};

#endif // DEMOBJECT_H
