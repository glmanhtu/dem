#include "demobject.h"
#include "gdal.h"
#include "gdal_priv.h"

DemObject::DemObject()
{
    zooomStep = 2;
}

GDALDataset* DemObject::getDataSet()
{
    return dataSet;
}

void DemObject::setDataSet(GDALDataset *ds)
{
    dataSet = ds;    
    oriCols = dataSet->GetRasterXSize();
    oriRows = dataSet->GetRasterYSize();
    readStep = (oriCols-1) / 1200;
    cols = oriCols/readStep;
    rows = oriRows/readStep;
}


void DemObject::addVertex(Vertex vertex)
{
    vertexs.push_back(vertex);
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

int DemObject::getVertexPositionIn2D(int col, int row, bool northeast)
{
    col = col/zooomStep;
    row = row/zooomStep;
    int scaledCols = (cols - 1)/zooomStep;
    int scalesRows = (rows - 1)/zooomStep;
    int index = 0;
    if (!northeast) {
        if (row == scalesRows - 1) {
            index = scalesRows*scaledCols*2-scaledCols + col;
        } else {
            index = (scaledCols + 2*(col + 1) -1) + row*scaledCols*2 -1;
        }
    }
    else {
        if (row == 0) {
            index = col;
        } else {
            index = (scaledCols + 2*(col + 1) -1) + (row-1)*scaledCols*2;
        }
    }

    return index*3;
}


Vertex *DemObject::getArrayVertexs()
{
    return vertexs.data();
}


int DemObject::countVertexs()
{
    return vertexs.size();
}


std::vector<float> DemObject::readDem()
{
    GDALRasterBand* band = dataSet->GetRasterBand(1);
    std::vector<float> band_data;
    for (int i=0; i<oriRows; i=i+readStep) {
        std::vector<float> tmpData(oriCols);
        band->RasterIO( GF_Read, 0, i,
                        oriCols, 1,
                        tmpData.data(),
                        oriCols, 1,
                        GDT_Float32,
                        0, 0);
        for (int j=0; j<oriCols;j = j+readStep) {
            band_data.push_back(tmpData[j]);
        }
    }

//    band->RasterIO( GF_Read, 0, 0,
//                    cols, rows,
//                    band_data.data(),
//                    cols, rows,
//                    GDT_Float32,
//                    0, 0);
    setMaxHeight(*std::max_element(band_data.begin(), band_data.end()));
    setMinHeight(*std::min_element(band_data.begin(), band_data.end()));
    return band_data;
}


int DemObject::getZoom()
{
    return zooomStep;
}


void DemObject::clean()
{

}
