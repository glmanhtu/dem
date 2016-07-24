#include "meshing.h"

Meshing::Meshing(GDALDataset *pData)
{
    this->pData = pData;
}

vector<float> Meshing::createVertexArray()
{
    vector<float> vertices;
    vector<float> x,y;
    double transform[6];
    pData->GetGeoTransform(transform);
    int width = pData->GetRasterXSize();
    int height = pData->GetRasterYSize();
    int totalSize = width*height;
    for (int i=0; i < width; i++) {
        float pixelX = (int)(i - transform[0])/transform[1];
        x.push_back(pixelX);
    }

    for (int i=0; i<height; i++) {
        float pixelY = (int)(i - transform[3])/transform[5];
        y.push_back(pixelY);
    }

    GDALRasterBand* band = pData->GetRasterBand(1);
//    vector<float> band_data(totalSize);

    // Read the data
//    band->RasterIO( GF_Read, 0, 0,
//                    width, height,
//                    band_data.data(),
//                    width, height,
//                    GDT_Float32,
//                    0, 0);

    int currentBandData = 0;
    for (int i =0; i< height; i++) {
        for (int j=0; j<width; j++) {
            float* dataPoint = new float[3];
            dataPoint[0] = x[j];
            dataPoint[1] = y[i];
            //dataPoint[2] = band_data[currentBandData];
            //vertices.push_back(dataPoint);
            vertices.push_back(x[j]);
            vertices.push_back(y[i]);
            float* data;
            band->RasterIO( GF_Read, x[j], y[i],
                           1, 1,
                           data,
                           1, 1,
                           GDT_Float32,
                           0, 0);
            vertices.push_back(*data);
            currentBandData++;
        }
    }

    return vertices;
}

Meshing::~Meshing()
{

}
