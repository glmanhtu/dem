#ifndef DEMINTERFACE_H
#define DEMINTERFACE_H

#include "gdal.h"
#include "gdal_priv.h"
#include <qopengl.h>
#include <QVector>
#include <QVector3D>

class DemInterface
{
public:
    virtual void setSize(int) = 0;
    virtual int count() = 0;
    virtual int vertexCount() = 0;
    virtual const GLfloat *constData() = 0;
    virtual void add(const QVector3D &v, const QVector3D &n) = 0;
    virtual void quad(QVector3D v1, QVector3D v2, QVector3D v3, QVector3D v4) = 0;
    virtual void tri(QVector3D v1, QVector3D v2, QVector3D v3) = 0;
    virtual void clean() = 0;
    virtual void setGDALDataSet(GDALDataset* dataSet) = 0;
    virtual GDALDataset* getGDALDataSet() = 0;
};

#endif // DEMINTERFACE_H
