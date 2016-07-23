#ifndef MESHING_H
#define MESHING_H

#include "gdal.h"
#include "gdal_priv.h"
#include <vector>

using namespace std;
class Meshing
{
private:
    GDALDataset* pData;
public:
    Meshing(GDALDataset* pData);
    ~Meshing();
    vector<float> createVertexArray();
};

#endif // MESHING_H
