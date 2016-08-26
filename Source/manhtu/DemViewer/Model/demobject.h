#ifndef DEMOBJECT_H
#define DEMOBJECT_H

#include "Model/deminterface.h"

class DemObject : public DemInterface
{
private:
    GDALDataset* dataSet;    
    std::vector<Vertex> vertexs;
    std::vector<int> ind;
    int cols, rows, zooomStep, readStep, oriCols, oriRows;
    float maxH, minH;
public:
    DemObject();    

    // DemInterface interface
public:
    void setDataSet(GDALDataset *) override;
    GDALDataset *getDataSet() override;
    void addVertex(Vertex ver, int position) override;
    int getCols() override;
    int getRows() override;
    float maxHeight() override;
    float minHeight() override;
    float setMaxHeight(float max) override;
    float setMinHeight(float min) override;
    float heightScale(float height) override;
    int getVertexPositionIn2D(int col, int row, bool northeast) override;
    Vertex *getArrayVertexs() override;
    int countVertexs() override;
    std::vector<float> readDem();
    int getZoom();
    void clean();
    int getVertexPosition(int x, int y);
    int *getVertexIndices();
    int countIndices();
    int getVertexPosition(int col, int row, int layer, int direction);
};

#endif // DEMOBJECT_H
